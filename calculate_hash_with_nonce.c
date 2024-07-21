//
// Created by abissa on 7/21/24.
//

#include "ipchain.h"

/**
 * calculate_hash_with_nonce - Calculate the hash of a block with a nonce
 * @block: The block to calculate the hash for
 */
void calculate_hash_with_nonce(block_t *block) {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    int found = 0;
    uint64_t nonce = 0;

    while (!found) {
        block->info.nonce = nonce;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, block, sizeof(block_info_t) + block->data.len);
        SHA256_Final(hash, &sha256);

        // Check if the hash has the required number of leading zeros
        found = 1;
        for (int i = 0; i < block->info.difficulty; i++) {
            if (hash[i] != 0) {
                found = 0;
                break;
            }
        }

        if (found) {
            memcpy(block->hash, hash, SHA256_DIGEST_LENGTH);
        } else {
            nonce++;
        }
    }
}
