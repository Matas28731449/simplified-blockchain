#ifndef USERS_H
#define USERS_H

#include "../../header.h"
#include "../transactions/transactions.h"

class User {
    public:

        User(const string &n) : name(n), public_key(""), balance(0) {
            generatePublicKey();
            generateBalance();
        }

        User(const string &n, const string &pk, const int &b) : name(n), public_key(pk), balance(b) { }

        User(const User &other) : name(other.name), public_key(other.public_key), balance(other.balance) { }

        const string &getName() {
            return name;
        }

        const string &getPublicKey() {
            return public_key;
        }

        const int &getBalance() {
            return balance;
        }

        void executeTransaction(Transaction &transaction) {
            if (transaction.getSenderKey() == public_key) {
                balance -= transaction.getAmount();
            }
            else if (transaction.getReceiverKey() == public_key) {
                balance += transaction.getAmount();
            }
        }

    private:

        string name,
               public_key;
        int    balance;

        void generatePublicKey() {
            public_key = generateHash(name);
        }

        void generateBalance() {
            balance = randomize(100, 1000000);
        }
};

#endif
