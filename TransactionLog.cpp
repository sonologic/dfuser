/* 
 * File:   TransactionLog.cpp
 * Author: koenmartens
 * 
 * Created on January 29, 2012, 7:47 PM
 */

#include "Transaction.h"
#include "TransactionLog.h"

TransactionLog::TransactionLog() {
}

TransactionLog::TransactionLog(const TransactionLog& orig) {
}

TransactionLog::~TransactionLog() {
}

Transaction *TransactionLog::startTransaction(const char *path) {
    Transaction *t=new Transaction(path);
    
    log.resize(log.size()+1);
   
    log.at(log.size()-1)=t;
    
    return t;
}