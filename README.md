# Protecting files and Intellectual Property Theft Detection using Blockchain

## Prerequisites
- OpenSSL (version 1.1.1)
- GCC

## Build
```sh
gcc -o IPChain main.c add_block.c add_file_metadata.c calculate_hash_with_nonce.c create_genesis_block.c print.c verify_blockchain.c -lssl -lcrypto -I/usr/include/openssl -L/usr/lib
```

## Run
```sh
./IPChain
```

## Commands
- `init`: Initialize the blockchain with a genesis block and 7 files located in the same directory as the program.
- `add_file <file>`: Add a file to the blockchain. 
- `verify`: Verify the blockchain
- `print`: Print the blockchain
- `quit`: Exit the program
- `help`: Display the help menu


