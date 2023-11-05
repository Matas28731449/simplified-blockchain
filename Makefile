main: users transactions
	g++ -std=c++11 -o blockchain/main blockchain/main.cpp
	cd blockchain && clear && ./main

users:
	g++ -std=c++11 -o generators/users/users generators/users/users.cpp
	cd generators/users && clear && ./users

transactions:
	g++ -std=c++11 -o generators/transactions/transactions generators/transactions/transactions.cpp
	cd generators/transactions && clear && ./transactions

clean:
	rm -f generators/transactions/*.o generators/transactions/transactions
	rm -f generators/users/*.o generators/users/users
	rm -f blockchain/*.o blockchain/main
