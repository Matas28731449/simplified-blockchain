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

    vector<Transaction> candidate_1,
                        candidate_2,
                        candidate_3,
                        candidate_4,
                        candidate_5;
    vector<vector<Transaction>> candidates = {
        candidate_1,
        candidate_2,
        candidate_3,
        candidate_4,
        candidate_5
    };

    void compose(vector<User> &users, vector<Transaction> &transactions) {
        int attempt_duration = 5; // in seconds
        int max_hash_attempts = 100000;

        while (!transactions.empty()) {
            vector<vector<Transaction>> candidates;
            // Select transactions for 5 candidate blocks
            for (int i = 0; i < 5; ++i) {
                vector<Transaction> candidate_transactions = selectTransactions(100, transactions);
                if (!candidate_transactions.empty()) {
                    candidates.push_back(candidate_transactions);
                }
            }

            while (!candidates.empty()) {
                // Randomly select one of the candidate blocks
                int candidate_index = randomize(0, candidates.size() - 1);
                vector<Transaction> candidate_block = candidates[candidate_index];
                // Remove the selected candidate from the list of candidates
                candidates.erase(candidates.begin() + candidate_index);

                // Try to mine the selected candidate block
                if (tryMineBlock(users, candidate_block, attempt_duration, max_hash_attempts)) break; // If mined successfully, break out of the loop
            }

            // Increase limits if no blocks were mined
            while (chain.size() == 0 || chain.back().transactions.size() == 0) {
                attempt_duration *= 2; // adjust this factor as needed
                max_hash_attempts *= 2; // adjust this factor as needed
            }
        }
    }



    vector<Transaction> selectTransactions(int transaction_amount, vector<Transaction> &transactions) {
        vector<Transaction> selected_transactions;

        for (int i = 0; i < transaction_amount && !transactions.empty(); ++i) {
            int index = randomize(0, transactions.size() - 1);
            selected_transactions.push_back(transactions[index]);
            transactions.erase(transactions.begin() + index); // Remove the selected transaction
        }
        
        return selected_transactions;
    }

    bool tryMineBlock(vector<User> &users, vector<Transaction> &candidate_block, int attempt_duration, int max_hash_attempts) {
        int index = chain.size();
        const string &previous_hash = chain.back().hash;

        // Attempt to mine the block with the given transactions
        Block block(index, previous_hash, candidate_block, attempt_duration, max_hash_attempts);

        // Check if mining was successful
        if (block.hash != "0") {
            // Add block to the chain and update users' balances
            chain.push_back(block);
            for (Transaction &t : candidate_block) {
                for (User &u : users) {
                    if (u.getPublicKey() == t.getSenderKey()) {
                        u.executeTransaction(t);
                        break;
                    }
                }
            }
            return true;
        }
        return false;
    }

    void printTransactionById(const string &transactionId) {
        for (const Block &block : chain) {
            for (const Transaction &transaction : block.transactions) {
                if (transaction.getTransactionId() == transactionId) {
                    cout << "\n---------------------------------------------------------------------------------\n";
                    cout << "Block index: " << block.index << "\n";
                    cout << "Block hash: " << block.hash << "\n";
                    cout << "Transaction ID: " << transaction.getTransactionId() << "\n";
                    cout << "Sender key: " << transaction.getSenderKey() << "\n";
                    cout << "Receiver key: " << transaction.getReceiverKey() << "\n";
                    cout << "Amount: " << transaction.getAmount() << "\n";
                    cout << "---------------------------------------------------------------------------------\n";
                    return;
                }
            }
        }
        cout << "Transaction " << transactionId << " does not exist in the blockchain.\n";
    }

    void printAllTransactionsId() {
        std::ofstream out("outputs/transactions.txt");

        for (const Block &block : chain) {
            block.index == 0 ? out << "--------------------------GENESIS-BLOCK--------------------------\n" : block.index < 10 ? out << "----------------------------BLOCK-0" << block.index << "-----------------------------\n" : 
            out << "----------------------------BLOCK-" << block.index << "-----------------------------\n";
            for (const Transaction &transaction : block.transactions) {
                out << transaction.getTransactionId() << "\n";
            }
        }

        out.close();
    }

    void printSelectedBlock(int blockIndex) {
        if (blockIndex >= 0 && blockIndex < chain.size()) {
            chain[blockIndex].printBlock();
        } else {
            cout << "\nINVALID BLOCK INDEX: " << chain.size() - 1 << " blocks mined\n";
        }
    }

    void printBlockchain() {
        for (Block &b : chain) {
            b.printBlock();
        }
    }

private:
    vector<Block> chain;
    bool successful = true;

    Block createFirstBlock() {
        return Block(0, "0", vector<Transaction>(), 0, 0);
    }
};

#endif
