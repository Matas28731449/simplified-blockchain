#include "transactions.h"
#include "../users/users.h"

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

    for (int i = 0; i < 10000; i ++) {
        int tmp_sender = uniform_int_distribution<int>(0, users.size() - 1)(generate),
            tmp_receiver = uniform_int_distribution<int>(0, users.size() - 1)(generate),
            amount;
            do {
                amount = randomize(100, 100000);
            } while (amount > users[tmp_sender].getBalance());
            transactions.emplace_back(users[tmp_sender].getPublicKey(), users[tmp_receiver].getPublicKey(), amount);
    }

    ofstream out("../data/transactions.txt");

    for (Transaction &t : transactions) {
        out << t.getTransactionId() << " " << t.getSenderKey() << " " << t.getReceiverKey() << " " << t.getAmount() << "\n";
    }

    cout << "Transactions generated\n";

    return 0;
}