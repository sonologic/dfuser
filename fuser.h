/* 
 * File:   fuser.h
 * Author: gmc
 *
 * Created on 03 December 2011, 02:25
 */

#ifndef FUSER_H
#define	FUSER_H

#ifdef	__cplusplus
extern "C" {
#endif

int dfuser_main(const char*);    
int dfuser_getattr(const char *path, struct stat *stbuf);
int dfuser_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi);
int dfuser_open(const char *path, struct fuse_file_info *fi);
int dfuser_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi);
int dfuser_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);

#ifdef	__cplusplus
}
#endif

#endif	/* FUSER_H */

