#include "blockchain.h"

int main() {
    Blockchain blockchain;
    
    vector<User> users;
    vector<Transaction> transactions;
    
    cout << "Reading users.txt...\n";
    readUsers(users, "../generators/data/users.txt");

    cout << "Reading transactions.txt...\n";
    readTransactions(transactions, "../generators/data/transactions.txt");

    // CHECK THE USER'S BALANCE BEFORE CARRYING OUT THE TRANSACTION
    // for (User &u : users) {
    //     cout << u.getName() << " " << u.getPublicKey() << " " << u.getBalance() << "\n";
    // }

    cout << "Composing blockchain...\n";
    blockchain.compose(users, transactions);

    // CHECK THE USER'S BALANCE AFTER CARRYING OUT THE TRANSACTION
    // for (User &u : users) {
    //     cout << u.getName() << " " << u.getPublicKey() << " " << u.getBalance() << "\n";
    // }

    cout << "Printing blockchain...\n";
    blockchain.printBlockchain();
    
    return 0;
}