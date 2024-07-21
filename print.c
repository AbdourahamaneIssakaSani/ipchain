//
// Created by abissa on 7/21/24.
//

#include "ipchain.h"

/**
 * print_usage - Print the usage message
 */
void print_usage() {
    printf("Commands:\n");
    printf("  init: Initialize a new blockchain with some files\n");
    printf("  add_file: Add a file to the blockchain\n");
    printf("  verify: Verify the blockchain\n");
    printf("  print: Print the blockchain\n");
    printf("  help: Display this help message\n");
    printf("  quit: Exit the program\n");
}

/**
 * print_block - Print the contents of a block
 * @param block: The block to print
 */
void print_block(const block_t *block) {
    printf("Block Info:\n");
    printf("  Index: %u\n", block->info.index);
    printf("  Difficulty: %u\n", block->info.difficulty);
    printf("  Timestamp: %lu\n", block->info.timestamp);
    printf("  Nonce: %lu\n", block->info.nonce);
    printf("  Prev Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", block->info.prev_hash[i]);
    }
    printf("\n");
    printf("Block Data: %.*s\n", block->data.len, block->data.buffer);
    printf("Block Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", block->hash[i]);
    }
    printf("\n \n");
}

/**
 * print_blockchain - Print the contents of a blockchain
 * @param blockchain: The blockchain to print
 */
void print_blockchain(const blockchain_t *blockchain) {
    printf("Blockchain:\n");
    for (size_t i = 0; i < blockchain->size; i++) {
        printf("Block %lu:\n", i);
        print_block(&blockchain->blocks[i]);
    }
}
