/* 
 * File:   fuser.h
 * Author: gmc
 *
 * Created on 03 December 2011, 02:25
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
int dfuser_release(const char *path, struct fuse_file_info *fi);
int dfuser_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi);
int dfuser_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
int dfuser_create(const char *path,mode_t mode,struct fuse_file_info *fi);
int dfuser_unlink(const char *path);
int dfuser_chmod(const char *patch,mode_t mode);
int dfuser_chown(const char *path,uid_t uid,gid_t gid);
int dfuser_mkdir(const char *path,mode_t mode);

#ifdef	__cplusplus
}
#endif

#endif	/* FUSER_H */

