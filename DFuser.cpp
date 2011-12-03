/* 
 * File:   DFuser.cpp
 * Author: gmc
 * 
 * Created on 03 December 2011, 11:19
 */

#include <errno.h>
#include <string.h>
#include "DFuser.h"

DFuser::DFuser(Repository *r,Logger *l) {
    repo = r;
    log = l;
}

DFuser::DFuser(const DFuser& orig) {
}

DFuser::~DFuser() {
}

int DFuser::getattr(const char *path, struct stat *stbuf) {
    int res=0;
    Attributes attr;
    
    log->notice("getattr %s\n",path);
    memset(stbuf, 0, sizeof(struct stat));
    
    if(repo->getAttributes(path,&attr)) {
        return errno;
    } else {
        stbuf->st_mode = attr.attr.st_mode;
        stbuf->st_nlink = attr.attr.st_nlink;
    }
    /*else if(strcmp(path, dfuser_path) == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(dfuser_str);
    }*/
    /*else
        res = -ENOENT;*/
    
    return res;
}

int DFuser::readdir(const char *path, void *buf, fuse_fill_dir_t filler,
        off_t offset, struct fuse_file_info *fi) {
    log->notice("readdir %s\n",path);
    return -ENOENT;
}

int DFuser::open(const char *path, struct fuse_file_info *fi) {
    log->notice("open %s\n",path);
    return -ENOENT;
}

int DFuser::read(const char *path, char *buf, size_t size, off_t offset,
        struct fuse_file_info *fi) {
    log->notice("read %s\n",path);
    return -ENOENT;
}

int DFuser::write(const char *path, const char *buf, size_t size,
        off_t offset, struct fuse_file_info *fi) {
    log->notice("write %s\n",path);
    return -ENOENT;
}
