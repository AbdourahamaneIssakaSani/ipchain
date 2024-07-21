//
// Created by abissa on 7/21/24.
//
#include "ipchain.h"

/**
 * create_genesis_block - Create the genesis block
 * Return: A pointer to the genesis block
 */
block_t *create_genesis_block() {
    block_t *block = malloc(sizeof(block_t));
    if (!block) {
        fprintf(stderr, "Failed to allocate memory for genesis block\n");
        return NULL;
    }

    memset(block, 0, sizeof(block_t));
    block->info.index = 0;
    block->info.timestamp = time(NULL);
    strcpy((char *) block->data.buffer, "Genesis Block");
    block->data.len = strlen((char *) block->data.buffer);

    // Compute the hash
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, block, sizeof(block_info_t) + block->data.len);
    SHA256_Final(block->hash, &sha256);

    return block;
}
