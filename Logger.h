/* 
 * File:   Logger.h
 * Author: gmc
 *
 * Created on 03 December 2011, 11:40
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

