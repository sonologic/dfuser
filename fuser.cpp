/* 
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
 */
   
#define FUSE_USE_VERSION 25
#define _FILE_OFFSET_BITS 64

#include <fuse.h>
#include <fuse/fuse_opt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include "fuser.h"
#include "FuseOps.h"
#include "TransactionLog.h"

static const char *dfuser_str = "Distributed FUSE replicator\n";
static const char *dfuser_path = "/dfuser";

static FuseOps *dfuser;

int dfuser_main(const char *path) {
    static Repository *repo;
    static Logger *logger;    
    static TransactionLog *transactionLog;
    
    repo=new Repository(path,transactionLog);
    repo->setLogger(logger);
    
    dfuser=new FuseOps(repo,logger);
    
    return 0;
}

int dfuser_getattr(const char *path, struct stat *stbuf)
{
    return dfuser->getattr(path,stbuf);
    int res = 0;

    memset(stbuf, 0, sizeof(struct stat));
    if(strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    }
    else if(strcmp(path, dfuser_path) == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(dfuser_str);
    }
    else
        res = -ENOENT;

    return res;
}

int dfuser_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi)
{
    return dfuser->readdir(path,buf,filler,offset,fi);
    (void) offset;
    (void) fi;

    if(strcmp(path, "/") != 0)
        return -ENOENT;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, dfuser_path + 1, NULL, 0);

    return 0;
}

int dfuser_open(const char *path, struct fuse_file_info *fi)
{
    return dfuser->open(path,fi);
    if(strcmp(path, dfuser_path) != 0)
        return -ENOENT;

    if((fi->flags & 3) != O_RDONLY)
        return -EACCES;

    return 0;
}

int dfuser_release(const char *path, struct fuse_file_info *fi) {
    return dfuser->release(path,fi);
}

int dfuser_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi)
{
    return dfuser->readFile(path,buf,size,offset,fi);
    size_t len;
    (void) fi;
    if(strcmp(path, dfuser_path) != 0)
        return -ENOENT;

    len = strlen(dfuser_str);
    if (offset < len) {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, dfuser_str + offset, size);
    } else
        size = 0;

    return size;
}

int dfuser_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    return dfuser->writeFile(path,buf,size,offset,fi);
}

int dfuser_create(const char *path,mode_t mode,struct fuse_file_info *fi) {
    return dfuser->create(path,mode,fi);
}

int dfuser_unlink(const char *path) {
    return dfuser->unlink(path);
}

int dfuser_chmod(const char *path,mode_t mode) {
    return dfuser->chmod(path,mode);
}

int dfuser_chown(const char *path,uid_t uid,gid_t gid) {
    return dfuser->chown(path,uid,gid);
}

int dfuser_mkdir(const char *path,mode_t mode) {
    return dfuser->mkdir(path,mode);
}