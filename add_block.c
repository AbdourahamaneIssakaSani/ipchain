//
// Created by abissa on 7/21/24.
//

#include "ipchain.h"

/**
 * add_block - Add a new block to the blockchain
 * @blockchain: The blockchain to add the block to
 * @data: The data to store in the block
 */
void add_block(blockchain_t *blockchain, const char *data) {
    block_t *new_block = malloc(sizeof(block_t));
    if (!new_block) {
        fprintf(stderr, "Failed to allocate memory for new block\n");
        return;
    }

    block_t *last_block = &blockchain->blocks[blockchain->size - 1];
    memset(new_block, 0, sizeof(block_t));
    new_block->info.index = last_block->info.index + 1;
    new_block->info.timestamp = time(NULL);
    new_block->info.difficulty = DIFFICULTY;
    memcpy(new_block->info.prev_hash, last_block->hash, SHA256_DIGEST_LENGTH);
    strncpy((char *) new_block->data.buffer, data, BLOCKCHAIN_DATA_MAX);
    new_block->data.len = strlen((char *) new_block->data.buffer);

    calculate_hash_with_nonce(new_block);

    blockchain->blocks = realloc(blockchain->blocks,
                                 (blockchain->size + 1) * sizeof(block_t));
    blockchain->blocks[blockchain->size] = *new_block;
    blockchain->size++;
    free(new_block);
}
