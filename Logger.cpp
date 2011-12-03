/* 
 * File:   Logger.cpp
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

#include <stdio.h>
#include <stdarg.h>
#include "Logger.h"

Logger::Logger() {
    openlog("dfuser",LOG_PERROR|LOG_PID,LOG_DAEMON);
    error("DFuser logger started");
}

Logger::Logger(const Logger& orig) {
}

Logger::~Logger() {
    closelog();
}

void Logger::notice(const char *format, ...) {
    va_list args;
    char message[2048];
    va_start(args,format);
    vsnprintf(message,2048,format,args);
    syslog(LOG_NOTICE,message);
    va_end(args);
}

void Logger::warning(const char *format, ...) {
    va_list args;
    char message[2048];
    va_start(args,format);
    vsnprintf(message,2048,format,args);
    syslog(LOG_WARNING,message);
    va_end(args);
}

void Logger::error(const char *format, ...) {
    va_list args;
    char message[2048];
    va_start(args,format);
    vsnprintf(message,2048,format,args);
    syslog(LOG_ERR,message);
    va_end(args);
}
