#ifndef BLOCK_H
#define BLOCK_H

#include "../../header.h"
#include "../../generators/users/users.h"
#include "../../generators/transactions/transactions.h"

class Block {
public:
    int index;
    int nonce;
    time_t timestamp;
    string hash;
    string previous_hash;
    vector<User> users;
    vector<Transaction> transactions;

    Block(int index, const string &previous_hash, const vector<Transaction> &transactions)
        : index(index), previous_hash(previous_hash), transactions(transactions) {
        timestamp = static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        nonce = 0;
        hash = mineBlock();
    }

    void printBlock() {
        index == 0 ? cout << "\n-------------------------------------GENESIS-BLOCK-------------------------------------" :
        index < 10 ? cout << "\n---------------------------------------BLOCK-0" << index << "----------------------------------------" : 
        cout << "\n---------------------------------------BLOCK-" << index << "----------------------------------------";
        cout << "\nBlock index: " << index
             << "\nBlock hash: " << hash
             << "\nPrevious block hash: " << previous_hash
             << "\nMined on: " << ctime(&timestamp)
             << "Transactions: " << transactions.size()
             << "\nNonce: " << nonce
             << "\n---------------------------------------------------------------------------------------";
    }

private:
    string mineBlock() {
        string compressed_data = to_string(index) + previous_hash + to_string(timestamp) + to_string(nonce);
        string difficulty_target(DIFFICULTY_TARGET, '0');
        string hash;

        for (Transaction &t : transactions) {
            compressed_data += t.getTransactionId();
        }

        do {
            nonce++;
            compressed_data += to_string(nonce);
            hash = generateHash(compressed_data);
        } while (hash.substr(0, difficulty_target.size()) != difficulty_target);

        return hash;
    }
};

#endif
