/* 
 * File:   Journal.h
 * Author: gmc
 *
 * Created on 05 December 2011, 10:29
 */

#ifndef JOURNAL_H
#define	JOURNAL_H

#include "Attributes.h"

class Journal {
public:
    Journal();
    Journal(const Journal& orig);
    virtual ~Journal();
    int write(const char *path,size_t ofs,size_t len,void *buf);
    int truncate(const char *path);
    int create(const char *path,int mode);
    int unlink(const char *path);
    int chattr(const char *path,Attributes *attr);    
private:

};

#endif	/* JOURNAL_H */

