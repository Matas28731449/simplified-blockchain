#ifndef USERS_H
#define USERS_H

#include "../../header.h"

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

    private:

        string name,
               public_key;
        int    balance;

        void generatePublicKey() {
            uint32_t hash[8];
            memcpy(hash, HASH_CODE, sizeof(HASH_CODE));
            for (char c : name) {
                for (int i = 0; i < 8; ++i) {
                    hash[i] = mixHash(hash[i], hash[(i + 1) % 8], static_cast<uint32_t>(c));
                }
            }

            char result[65];
            snprintf(result, sizeof(result),
                     "%08x%08x%08x%08x%08x%08x%08x%08x",
                     hash[0], hash[1], hash[2], hash[3],
                     hash[4], hash[5], hash[6], hash[7]);
            public_key = result;
        }

        void generateBalance() {
            balance = randomize(100, 1000000);
        }
};

#endif
