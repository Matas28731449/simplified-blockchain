#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "../../header.h"
#include "../users/users.h"

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

    private:

        string transaction_id,
               sender_key,
               receiver_key;
        int    amount;

        void generateTransactionId() {
            uint32_t hash[8];
            memcpy(hash, HASH_CODE, sizeof(HASH_CODE));
            string compressed_data = sender_key + receiver_key + to_string(amount);
            for (char c : compressed_data) {
                for (int i = 0; i < 8; ++i) {
                    hash[i] = mixHash(hash[i], hash[(i + 1) % 8], static_cast<uint32_t>(c));
                }
            }

            char result[65];
            snprintf(result, sizeof(result),
                    "%08x%08x%08x%08x%08x%08x%08x%08x",
                    hash[0], hash[1], hash[2], hash[3],
                    hash[4], hash[5], hash[6], hash[7]);
            transaction_id = result;
        }
};

#endif
