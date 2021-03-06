/* 
 * File:   DFuser.h
 * Author: gmc
 *
 * Created on 03 December 2011, 11:19
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

#ifndef DFUSER_H
#define	DFUSER_H

//#ifdef _x86_64_
#define _FILE_OFFSET_BITS 64
//#endif
#define FUSE_USE_VERSION 25

#include <fuse.h>
#include <stdio.h>
#ifdef __gnu_linux__
#include <malloc.h>
#endif
#include "Repository.h"
#include "Logger.h"

class FuseOps {
public:
    FuseOps(Repository *,Logger *);
    FuseOps(const FuseOps& orig);
    virtual ~FuseOps();
    int getattr(const char *path, struct stat *stbuf);
    int readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi);
    int open(const char *path, struct fuse_file_info *fi);
    int release(const char *path, struct fuse_file_info *fi);
    int readFile(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi);
    int writeFile(const char *path, const char *buf, size_t size,
                        off_t offset, struct fuse_file_info *fi);
    int create(const char *path,mode_t mode,struct fuse_file_info *fi);
    int unlink(const char *path);
    int chmod(const char *path,mode_t mode);
    int chown(const char *path,uid_t uid,gid_t gid);
    int mkdir(const char *path,mode_t mode);
private:
    Repository *repo;
    Logger *log;
};

#endif	/* DFUSER_H */

