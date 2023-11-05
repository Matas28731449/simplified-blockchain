# simplified-blockchain

## Installation process & Console commands

Clone my GitHub repository: `git clone https://github.com/Matas28731449/simplified-blockchain.git` ;

Navigate to cloned repository: `cd {folder name}/simplified-blockchain/` ;

Choose the v0.1 branch: `git checkout v0.1` ;

Compile the files and run the program via Makefile: `make main` ;

- To create new users.txt, execute: `make users` ;

- To generate new transactions.txt, execute: `make transactions` ;

- To perform all the above commands simultaneously, simply run: `make` ;

- To clear run files, execute: `make clean` ;

Follow the instructions, happy using!

## How does blockchain v0.1 work?

The program creates 1000 users, generates 10000 transactions, and then randomly selects 100 transactions for each block ;

These selected transactions are removed from the transaction pool ;

The program proceeds to mine the block until the necessary hash requirements are met ;

Once the block is mined, the selected transactions are executed, updating user balances ;

The newly mined block is subsequently appended to the blockchain ;

The program continues to iterate through this process until the transaction pool becomes empty .