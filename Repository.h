/* 
 * File:   repo.h
 * Author: gmc
 *
 * Created on 03 December 2011, 01:48
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

