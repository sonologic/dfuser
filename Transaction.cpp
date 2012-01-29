/* 
 * File:   Transaction.cpp
 * Author: koenmartens
 * 
 * Created on January 29, 2012, 7:42 PM
 */

#include <stdlib.h>
#include <string.h>
#include "sha1.h"
#include "Transaction.h"

Transaction::Transaction(const char *p) {
    path=strdup(p);
//    repo=r;
//    r->getHash(p,hash);
}

Transaction::Transaction(const Transaction& orig) {
}

Transaction::~Transaction() {
    free(path);
}

