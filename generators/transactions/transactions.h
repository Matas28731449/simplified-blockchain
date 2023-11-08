#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "../../header.h"

class Transaction {
    public:

        Transaction(const string &sk, const string &rk, const int &a) : sender_key(sk), receiver_key(rk), amount(a) {
            generateTransactionId();
        }

        Transaction(const string &tid, const string &sk, const string &rk, const int &a)
        : transaction_id(tid), sender_key(sk), receiver_key(rk), amount(a) { }

        const string &getTransactionId() {
            return transaction_id;
        }

        const string &getSenderKey() {
            return sender_key;
        }

        const string &getReceiverKey() {
            return receiver_key;
        }

        const int &getAmount() {
            return amount;
        }

        bool operator==(const Transaction &other) const {
            return transaction_id == other.transaction_id &&
                sender_key == other.sender_key &&
                receiver_key == other.receiver_key &&
                amount == other.amount;
        }

    private:

        string transaction_id,
               sender_key,
               receiver_key;
        int    amount;

        void generateTransactionId() {
            string compressed_data = sender_key + receiver_key + to_string(amount);
            transaction_id = generateHash(compressed_data);
        }
};

#endif
