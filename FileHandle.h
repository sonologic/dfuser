/* 
 * File:   FileHandle.h
 * Author: gmc
 *
 * Created on 04 December 2011, 23:53
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

#ifndef FILEHANDLE_H
#define	FILEHANDLE_H

class FileHandle {
public:
    FileHandle();
    FileHandle(const FileHandle& orig);
    virtual ~FileHandle();
    int read(size_t ofs,size_t len,void *buf);
    int write(size_t ofs,size_t len,void *buf);
    int truncate();
private:
    uint64_t fh;        // fuse handle
    FILE *fp;           // pointer to underlying file
};

#endif	/* FILEHANDLE_H */

