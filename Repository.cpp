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
        ec = -1;
    }

    free(fsp);

    return ec;
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