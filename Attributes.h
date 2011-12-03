/* 
 * File:   Attributes.h
 * Author: gmc
 *
 * Created on 03 December 2011, 12:19
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

