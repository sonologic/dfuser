/* 
 * File:   Attributes.h
 * Author: gmc
 *
 * Created on 03 December 2011, 12:19
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

#ifndef ATTRIBUTES_H
#define	ATTRIBUTES_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class Attributes {
public:
    Attributes();
    Attributes(const Attributes& orig);
    virtual ~Attributes();
    struct stat attr;
private:

};

#endif	/* ATTRIBUTES_H */

