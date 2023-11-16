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
    cout << "Blockchain successfully composed\n";

    string opt = "";
    int    num = 0;
    do {
        cout << "\n'end' to exit\n'otx' to print selected transaction\n'txn' to print all transactions\n'one' to print selected block\n'all' to print entire blockchain\n\nType your choice: "; cin >> opt; 
        while (cin.fail() or (opt != "all" && opt != "one" && opt != "txn" && opt != "otx" && opt != "end")) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Incorrect form. Try again: "; cin >> opt;
        }
        if (opt == "all") {
            cout << "Printing blockchain...\n";
            blockchain.printBlockchain();
        }
        else if (opt == "one") {
            cout << "Enter desired block index: "; cin >> num;
            blockchain.printSelectedBlock(num);
            cout << "\n";
        }
        else if (opt == "txn") {
            blockchain.printAllTransactionsId();
            cout << "Transactions written to file: outputs/transactions.txt\n";
        }
        else if (opt == "otx") {
            cout << "Enter transaction ID: "; cin >> opt;
            blockchain.printTransactionById(opt);
            opt = "";
        }
    } while (opt != "end");

    // CHECK THE USER'S BALANCE AFTER CARRYING OUT THE TRANSACTION
    // for (User &u : users) {
    //     cout << u.getName() << " " << u.getPublicKey() << " " << u.getBalance() << "\n";
    // }
    
    return 0;
}