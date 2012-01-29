/* 
 * File:   repo.cpp
 * Author: gmc
 * 
 * Created on 03 December 2011, 01:48
 * 
 *     This file is part of dfuser.
 * 
 *     Dfuser is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     Dfuser is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with dfuser.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <dirent.h>
#include "Repository.h"

Repository::Repository(const char * p /* = 0 */) {
    checkPath(p);
    checkPath(p, "/fs");
    checkPath(p, "/meta");
    path = strdup(p);
}

Repository::Repository(const Repository& orig) {
}

Repository::~Repository() {
    free(path);
}

void Repository::setLogger(Logger *l) {
    log = l;
}

char *Repository::prependFsPath(const char *p) {
    char *newpath;
    size_t size;

    size = strlen(path) + strlen(p)+((p[0] == '/') ? 0 : 1) + 3;

    newpath = (char*) malloc(size);

    if (newpath != NULL) {
        strcpy(newpath, path);
        strcat(newpath, "/fs");
        if (p[0] != '/') strcat(newpath, "/");
        strcat(newpath, p);
    }

    return newpath;
}

int Repository::checkPath(const char *path) {
    struct stat info;

    if (stat(path, &info)) {
        // stat failed
        if (errno != ENOENT) {
            fprintf(stderr, "Unable to open repository: %s\n", strerror(errno));
            throw errno;
        }
        if (mkdir(path, 0700)) {
            fprintf(stderr, "Unable to create repository dir: %s\n", strerror(errno));
            throw errno;
        }
    }
    return 0;
}

int Repository::checkPath(const char *root, const char *sub) {
    char *path;

    path = (char*) malloc(strlen(root) + strlen(sub));

    strcpy(path, root);
    strcat(path, sub);

    int ec = checkPath(path);

    free(path);

    return ec;
}

int Repository::getAttributes(const char *p, Attributes *attr) {
    char *fsp;
    int ec = 0;

    fsp = prependFsPath(p);
    log->notice("getAttributes %s\n", fsp);

    if (stat(fsp, &attr->attr)) {
        ec = -errno;
    }

    free(fsp);

    return ec;
}

int Repository::createDir(const char *path,mode_t mode) {
    int rv=0;
    char *fspath=prependFsPath(path);
    
    log->notice("mkdir %s w/ mode %o\n",fspath,mode);
    if(mkdir(fspath,mode)) {
        log->notice("mkdir failed %s\n",strerror(errno));
        rv=-errno;
    } else if(chmod(fspath,mode)) {
        log->notice("mkdir failed %s\n",strerror(errno));
        rv=-errno;        
    }
    free(fspath);
    return rv;
}

repodir Repository::openDir(const char *p) {
    char *fspath;
    DIR *dirh;

    fspath = prependFsPath(p);

    if (fspath == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    dirh = opendir(fspath);

    free(fspath);

    return (repodir) dirh;
}

char *Repository::readDir(repodir dir) {
    DIR *dirh = (DIR *) dir;
    struct dirent *entry;
    char *name = NULL;

    entry = readdir(dirh);

    if (entry != NULL) {
        name = strdup(entry->d_name);
    }

    return name;
}

void Repository::closeDir(repodir dir) {
    closedir((DIR *) dir);
}

int Repository::openFile(const char *path,int flags) {
    char *rpath;
    int rv;
    int fd;
    
    rpath=prependFsPath(path);
            
    log->notice("open %s\n",rpath);
    // @todo check permissions
    fd=open(rpath,flags);
    
    free(rpath);
    
    if(fd>0) return fd;
    
    return -errno;
}

int Repository::writeFile(const char *path, const char *buf, size_t size,off_t offset,int fd) {
    ssize_t totalWritten=0;
    ssize_t written;
    
    log->notice("write %i bytes to %i, fd=%i\n",size,offset,fd);
    if(lseek(fd,offset,SEEK_SET)==-1) {
        log->notice("lseek failed: %s\n",strerror(errno));
        return -errno;
    }
    while(totalWritten<size) {
        written=write(fd,buf+totalWritten,size-totalWritten);
        if(written==-1) {
            log->notice("write error %s\n",strerror(errno));
            return -errno;
        }
        totalWritten+=written;
    }
    return totalWritten;
}

int Repository::readFile(const char *path, char *buf, size_t size, off_t offset, int fd) {
    ssize_t totalRead=0;
    ssize_t bread;
    
    log->notice("read %i bytes from %i, fd=%i\n",size,offset,fd);
    if(lseek(fd,offset,SEEK_SET)==-1) {
        log->notice("lseek failed: %s\n",strerror(errno));
        return -errno;
    }
    bread=-1;
    while(totalRead<size) {
        bread=read(fd,buf+totalRead,size-totalRead);
        if(bread==-1) {
            log->notice("read error %s\n",strerror(errno));
            return -errno;
        }
        if(bread==0) {
            log->notice("eof on fd %i\n",fd);
            return totalRead;
        }
        totalRead+=bread;
        log->notice("read %i bytes (%i total)\n",bread,totalRead);
    }
    return totalRead;
    
}

int Repository::closeFile(const char *path,int fd) {
    if(close(fd)) {
        return -errno;
    }
    return 0;
}

int Repository::create(const char *path,mode_t mode) {
    char *fspath=prependFsPath(path);
    int rv;
    int fd;
    
    if(S_ISDIR(mode)) {
        log->notice("create: directory\n");
        if(mkdir(fspath,mode&0x1ff)) {
            log->notice("create: mkdir failed (%s)\n",strerror(errno));
            rv=-errno;
        } else if(chmod(fspath,mode)) {
            log->notice("create: chmod failed (%s)\n",strerror(errno));
            rv=-errno;
        } else {
            log->notice("create: ok\n");
            rv=0;
        }
    } else if(S_ISREG(mode)) {
        log->notice("create: file %s\n",fspath);
        fd=open(fspath,O_RDWR|O_CREAT|O_EXCL);
        log->notice("fd: %i\n",fd);
                
        if(fd==-1) {
            log->notice("create: error opening file (%s)\n",strerror(errno));
            rv=-errno;
        } else if(chmod(fspath,mode)) {
            log->notice("create: chmod failed (%s)\n",strerror(errno));
            rv=-errno;
        } else {
            return fd;
        }
        rv=-ENOTSUP;
    } else {
        rv=-ENOTSUP;
    }
    free(fspath);
    return rv;
}

int Repository::unlinkPath(const char *path) {
    int rv=0;
    char *fspath=prependFsPath(path);
    
    log->notice("unlink %s\n",fspath);
    if(unlink(fspath)==-1) {
        log->notice("unlink failed: %s\n",strerror(errno));
        rv=-errno;
    }
    
    return rv;
}

int Repository::chmodPath(const char *path,mode_t mode) {
    int rv=0;
    char *fspath=prependFsPath(path);
    
    log->notice("chmod %s to %o\n",fspath,mode);
    if(chmod(fspath,mode)) {
        log->notice("chmod failed: %s\n",strerror(errno));
        rv=-errno;
    }
    free(fspath);
    return rv;
}

int Repository::chownPath(const char *path,uid_t uid,gid_t gid) {
    int rv=0;
    char *fspath=prependFsPath(path);
    
    log->notice("chown %s to %i:%i\n",fspath,uid,gid);
    if(chown(fspath,uid,gid)) {
        log->notice("chown failed: %s\n",strerror(errno));
        rv=-errno;
    }
    free(fspath);
    return rv;
}