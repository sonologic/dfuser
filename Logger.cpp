/* 
 * File:   Logger.cpp
 * Author: gmc
 * 
 * Created on 03 December 2011, 11:40
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
