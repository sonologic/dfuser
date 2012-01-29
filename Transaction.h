/* 
 * File:   Transaction.h
 * Author: koenmartens
 *
 * Created on January 29, 2012, 7:42 PM
 */

#ifndef TRANSACTION_H
#define	TRANSACTION_H

class Transaction {
public:
    Transaction(const char *path);
    Transaction(const Transaction& orig);
    virtual ~Transaction();
private:
    char hash[41];
    char *buf;
    char *path;
    //Repository *repo;
    int op;
};

#endif	/* TRANSACTION_H */

