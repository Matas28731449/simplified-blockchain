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

    Block(int idx, const string &prev_hash, const vector<Transaction> &txs, int attempt_duration, int max_hash_attempts)
        : index(idx), previous_hash(prev_hash), transactions(txs) {
        
        timestamp = static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count());
        nonce = 0;
        
        // Now mineBlock() needs these two new parameters
        hash = mineBlock(attempt_duration, max_hash_attempts);
    }

    void printBlock() {
        index == 0 ? cout << "\n-------------------------------------GENESIS-BLOCK-------------------------------------" :
        index < 10 ? cout << "---------------------------------------BLOCK-0" << index << "----------------------------------------" : 
        cout << "---------------------------------------BLOCK-" << index << "----------------------------------------";
        cout << "\nBlock index: " << index
             << "\nBlock hash: " << hash
             << "\nPrevious block hash: " << previous_hash
             << "\nMined on: " << ctime(&timestamp)
             << "Transactions: " << transactions.size()
             << "\nNonce: " << nonce
             << "\n---------------------------------------------------------------------------------------\n";
    }

    string mineBlock(int attempt_duration, int max_hash_attempts) {
        string compressed_data = to_string(index) + previous_hash + to_string(timestamp) + to_string(nonce);
        string difficulty_target(DIFFICULTY_TARGET, '0');
        string hash;

        // Merkle tree

        vector<string> hashed_transactions;

        for (Transaction &t : transactions) {
            // Transaction hash validation
            string transaction_id = t.getSenderKey() + t.getReceiverKey() + to_string(t.getAmount());
            if (t.getTransactionId() == generateHash(transaction_id)) {
                string tmp_transaction_data = t.getTransactionId() + t.getSenderKey() + t.getReceiverKey() + to_string(t.getAmount());
                hashed_transactions.push_back(generateHash(tmp_transaction_data));
            } else {
                cout << "Transaction " << t.getTransactionId() << " invalid\n";
            }
        }

        while (hashed_transactions.size() > 1) {
            vector<string> merkle_tree;

            for (size_t i = 0; i < hashed_transactions.size(); i += 2) {
                if (i + 1 < hashed_transactions.size()) {
                    string compressed_hashes = hashed_transactions[i] + hashed_transactions[i + 1]; // if even, then two different hashes
                    merkle_tree.push_back(generateHash(compressed_hashes));
                } else {
                    string compressed_hash = hashed_transactions[i] + hashed_transactions[i]; // if odd, then same hash
                    merkle_tree.push_back(generateHash(compressed_hash));
                }
            }

            hashed_transactions = merkle_tree;
        }

        // Bypass the Genesis block

        if (!hashed_transactions.empty()) {
            compressed_data += hashed_transactions[0];
        }

        // Mining

        auto start_time = std::chrono::high_resolution_clock::now();
        int attempts = 0;

        do {
            nonce++;
            compressed_data += to_string(nonce);
            hash = generateHash(compressed_data);

            // Check if we have a valid hash or if we've reached the maximum attempts
            if (hash.substr(0, difficulty_target.size()) == difficulty_target || attempts >= max_hash_attempts) {
                break;
            }

            attempts++;

            // Check if we've exceeded the time limit
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
            if (duration.count() >= attempt_duration) {
                break;
            }

        } while (true);

        return hash.substr(0, difficulty_target.size()) != difficulty_target ? "0" : hash;
    }   
};

#endif
