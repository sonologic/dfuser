/* 
 * File:   TransactionLog.h
 * Author: koenmartens
 *
 * Created on January 29, 2012, 7:47 PM
 */

#ifndef TRANSACTIONLOG_H
#define	TRANSACTIONLOG_H

#include <vector>

#include "Transaction.h"

using namespace std;

class TransactionLog {
public:
    TransactionLog();
    TransactionLog(const TransactionLog& orig);
    virtual ~TransactionLog();
    Transaction *startTransaction(const char *path);
private:
    vector<Transaction *> log;
};

#endif	/* TRANSACTIONLOG_H */

