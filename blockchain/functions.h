#include "blockchain.h"

vector<Transaction> selectTransactions(int transaction_amount, vector<Transaction> &selected_transactions, vector<Transaction> &transactions) {
    if (transactions.size() <= transaction_amount) {
        selected_transactions = transactions;
        transactions.clear();
    } else {
        for (int i = 0; i < transaction_amount; i ++) {
            int index = randomize(0, transactions.size() - 1);
            selected_transactions.push_back(transactions[index]);
            transactions.erase(transactions.begin() + index);
        }
    }

    return selected_transactions;
}

void readTransactions(vector<Transaction> &transactions, const string &file) {
    ifstream in(file);

    if (in.is_open()) {
        string row,
               transaction_id,
               sender_key,
               receiver_key;
        double amount;

        while (getline(in, row)) {
            istringstream iss(row);

            iss >> transaction_id >> sender_key >> receiver_key >> amount;

            transactions.emplace_back(transaction_id, sender_key, receiver_key, amount);
        }

        in.close();
    }
}

void readUsers(vector<User> &users, const string &file) {
    ifstream in(file);

    if (in.is_open()) {
        string row,
               name,
               public_key;
        double balance;

        while (getline(in, row)) {
            istringstream iss(row);

            iss >> name >> public_key >> balance;

            users.emplace_back(name, public_key, balance);
        }

        in.close();
    }
}