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
#include "Logger.h"
#include "TransactionLog.h"

typedef void *repodir;

class Repository {
public:
    // meta ops
    Repository(const char * path, TransactionLog *log);
    Repository(const Repository& orig);
    virtual ~Repository();
    void setLogger(Logger *l);
    // repo functions
    int getHash(const char *path,char *hash);
    // fs ops
    int getAttributes(const char *path,Attributes *attr);
    int createDir(const char *path,mode_t mode);
    int openPath(const char *path,int mode);
    int closePath(const char *path);
    repodir openDir(const char *path);
    char *readDir(repodir dir);
    void closeDir(repodir dir);
    int create(const char *path,mode_t mode);
    int openFile(const char *path,int flags);
    int writeFile(const char *path, const char *buf, size_t size,
        off_t offset,int fd);
    int readFile(const char *path, char *buf, size_t size,
        off_t offset, int fd);
    int closeFile(const char *path,int fd);
    int unlinkPath(const char *path);
    int chmodPath(const char *path,mode_t mode);
    int chownPath(const char *path,uid_t uid,gid_t gid);
private:
    int checkPath(const char *path);
    int checkPath(const char *path,const char *sub);
    char *prependFsPath(const char *path);
    Transaction *openTransaction(const char *path);
    //
    char *path;
    Logger *log;
    TransactionLog *transactionLog;
    
};

#endif	/* REPO_H */

