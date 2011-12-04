#!/bin/bash
# 
# File:   test.bash
# Author: gmc
#
# Created on 03-Dec-2011, 01:30:44
#
#     This file is part of dfuser.
# 
#     Dfuser is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
# 
#     Dfuser is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
# 
#     You should have received a copy of the GNU General Public License
#     along with dfuser.  If not, see <http://www.gnu.org/licenses/>.
#

fusermount -u ~/mnt/aux
$1 -o repo=/home/gmc/.dfuser/repo,uid=502,gid=501 ~/mnt/aux