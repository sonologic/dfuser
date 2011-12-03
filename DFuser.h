/* 
 * File:   DFuser.h
 * Author: gmc
 *
 * Created on 03 December 2011, 11:19
 */

#ifndef DFUSER_H
#define	DFUSER_H

#include <fuse.h>
#include <stdio.h>
#include "Repository.h"
#include "Logger.h"

class DFuser {
public:
    DFuser(Repository *,Logger *);
    DFuser(const DFuser& orig);
    virtual ~DFuser();
    int getattr(const char *path, struct stat *stbuf);
    int readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi);
    int open(const char *path, struct fuse_file_info *fi);
    int read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi);
    int write(const char *path, const char *buf, size_t size,
                        off_t offset, struct fuse_file_info *fi);
private:
    Repository *repo;
    Logger *log;
};

#endif	/* DFUSER_H */

