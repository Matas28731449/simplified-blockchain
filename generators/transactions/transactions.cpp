#include "../header.h"
#include "../users/users.h"
#include "transactions.h"
#include <iostream>

int main() {
    vector<User> users;

    string name,
           public_key;
    int    balance;

    ifstream in("../data/users.txt");

    if (in.is_open()) {
        while (in >> name >> public_key >> balance) {
            users.emplace_back(name, public_key, balance);
        }
        in.close();
    }

    // for (User &u : users) {
    //     cout << u.getName() << " " << u.getPublicKey() << " " << u.getBalance() << "\n";
    // }

    vector<Transaction> transactions;

    random_device rd;
    mt19937 generate(rd());
    uniform_int_distribution<int> distribute(100, 100000);

    for (int i = 0; i < 10000; i ++) {
        int tmp_sender = uniform_int_distribution<int>(0, users.size() - 1)(generate),
            tmp_receiver = uniform_int_distribution<int>(0, users.size() - 1)(generate),
            amount = distribute(generate);
        if (amount <= users[tmp_sender].getBalance()) {
            transactions.emplace_back(users[tmp_sender].getPublicKey(), users[tmp_receiver].getPublicKey(), amount);
        }
    }

    ofstream out("../data/transactions.txt");

    for (Transaction &t : transactions) {
        out << t.getTransactionId() << " " << t.getSenderKey() << " " << t.getReceiverKey() << " " << t.getAmount() << "\n";
    }

    return 0;
}