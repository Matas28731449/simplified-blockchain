# simplified-blockchain

## Installation process & Console commands

Clone my GitHub repository: `git clone https://github.com/Matas28731449/simplified-blockchain.git` ;

Navigate to cloned repository: `cd {folder name}/simplified-blockchain/` ;

Choose the desired branch: `git checkout v0.2 (or v0.1)` ;

Compile the files and run the program via Makefile: `make main` ;

- To create new users.txt, execute: `make users` ;

- To generate new transactions.txt, execute: `make transactions` ;

- To perform all the above commands simultaneously, simply run: `make` ;

- To clear run files, execute: `make clean` ;

Follow the instructions, happy using!

## How does blockchain v0.2 work?

<img width="1710" alt="Screenshot 2023-11-08 at 23 54 08" src="https://github.com/Matas28731449/simplified-blockchain/assets/116190079/144d4d75-4f98-4e6c-839b-fe2b8ff11b63">

<img width="1710" alt="Screenshot 2023-11-08 at 23 54 12" src="https://github.com/Matas28731449/simplified-blockchain/assets/116190079/b6dc01b2-2f7a-48c1-a97f-59707f2170a2">

The program **creates** 1000 users, **generates** 10000 transactions, and then randomly **selects 100 transactions** for each block, **removing** them from the transaction pool. It proceeds to mine the block until the **necessary hash requirements** are met. Once the block is mined, the **selected transactions are executed**, updating user balances. The newly mined block is subsequently **appended** to the blockchain. The program **continues to iterate** through this process until the transaction pool **becomes empty** .