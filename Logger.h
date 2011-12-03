/* 
 * File:   Logger.h
 * Author: gmc
 *
 * Created on 03 December 2011, 11:40
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

#ifndef LOGGER_H
#define	LOGGER_H

#include <stdarg.h>
#include <syslog.h>

class Logger {
public:
    Logger();
    Logger(const Logger& orig);
    virtual ~Logger();
    void notice(const char *format, ...);
    void warning(const char *format, ...);
    void error(const char *format, ...);
private:

};

#endif	/* LOGGER_H */

