#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "../header.h"
#include "block/block.h"
#include "functions.h"

class Blockchain {
public:
    Blockchain() {
        chain.push_back(createFirstBlock());
    }

    void compose(vector<User> &users, vector<Transaction> &transactions) {
        vector<Transaction> selected_transactions;

        while (!transactions.empty()) {
            selectTransactions(1000, selected_transactions, transactions);
            addBlock(users, selected_transactions);
            selected_transactions.clear();
        }
    }

    void printBlockchain() {
        for (Block &b : chain) {
            b.printBlock();
        }
    }

private:
    vector<Block> chain;

    Block createFirstBlock() {
        return Block(0, "0", vector<Transaction>());
    }

    void addBlock(vector<User> &users, vector<Transaction> &selected_transactions) {
        int index = chain.size();
        const string &previous_hash = chain.back().hash;
        
        vector<Transaction> tmp_valid_transactions;

        // int counter = 0;

        for (Transaction &t : selected_transactions) {
            bool valid = false;

            for (User &u : users) {
                if (u.getPublicKey() == t.getSenderKey() && u.getBalance() >= t.getAmount()) {
                    tmp_valid_transactions.push_back(t);
                    u.executeTransaction(t);
                    valid = true;
                    break;
                }
            }

            if (!valid) {
                // cout << "Transaction " << t.getTransactionId() << " unsuccessful\n";
                // counter ++;
            }
        }   

        chain.push_back(Block(index, previous_hash, tmp_valid_transactions));
        // cout << counter << " transactions invalid\n";
    }
};

#endif
