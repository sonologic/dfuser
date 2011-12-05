/* 
 * File:   FileHandle.cpp
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

#include <errno.h>
#include "FileHandle.h"

FileHandle::FileHandle(Journal *journal,const char *path,const char *mode) {
    fp=fopen(path,mode);
    
    if(fp==NULL) throw errno;
}

FileHandle::FileHandle(const FileHandle& orig) {
}

FileHandle::~FileHandle() {
}

int FileHandle::read(size_t ofs, size_t len, void *buf) {
    return -1;
}

int FileHandle::write(size_t ofs, size_t len, void *buf) {
    return -1;
}

int FileHandle::truncate() {
    return -1;
}