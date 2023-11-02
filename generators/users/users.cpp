#include "../header.h"
#include "users.h"
#include <iostream>

int main() {
    vector<User> users;

    for (int i = 0; i < 1000; i ++) {
        users.push_back(User("Name" + to_string(i)));
    }

    ofstream out("../data/users.txt");

    // for (User &u : users) {
    //     out << u.getName() << " " << u.getPublicKey() << " " << u.getBalance() << "\n";
    // }

    out.close();

    return 0;
}