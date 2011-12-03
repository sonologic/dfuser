/* 
 * File:   repo.h
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

#ifndef REPO_H
#define	REPO_H

#include "Attributes.h"

class Repository {
public:
    Repository(const char * path /* = 0 */);
    Repository(const Repository& orig);
    virtual ~Repository();
    int getAttributes(const char *path,Attributes *attr);
    int openPath(const char *path,int mode);
    int closePath(const char *path);
private:
    int checkPath(const char *path);
    int checkPath(const char *path,const char *sub);
};

#endif	/* REPO_H */

