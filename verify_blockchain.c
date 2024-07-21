//
// Created by abissa on 7/21/24.
//

#include "ipchain.h"

/**
 * hash_matches_difficulty - Check if the hash matches the difficulty
 * @hash: The hash to check
 * @difficulty: The difficulty level
 * Return: 1 if the hash matches the difficulty, 0 otherwise
 */
int hash_matches_difficulty(const uint8_t *hash, uint32_t difficulty) {
    for (int i = 0; i < difficulty; i++) {
        if (hash[i] != 0) {
            return 0;
        }
    }
    return 1;
}


/**
 * calculate_hash_with_nonce - Calculate the hash of a block with a nonce
 * @block: The block to calculate the hash for
 */
int verify_blockchain(blockchain_t *blockchain) {
    for (size_t i = 1; i < blockchain->size; i++) {
        block_t *current = &blockchain->blocks[i];
        block_t *previous = &blockchain->blocks[i - 1];

        // Recompute the hash of the previous block
        uint8_t hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, previous,
                      sizeof(block_info_t) + previous->data.len);
        SHA256_Final(hash, &sha256);

        // Compare the recomputed hash with the stored previous hash
        if (memcmp(current->info.prev_hash, hash, SHA256_DIGEST_LENGTH) != 0) {
            printf("Block %lu has been tampered with!\n", i);
            return 0;
        }

        // Recompute the current block's hash to verify its integrity and difficulty
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, current,
                      sizeof(block_info_t) + current->data.len);
        SHA256_Final(hash, &sha256);

        // Check if the recomputed hash matches the stored hash
        if (memcmp(current->hash, hash, SHA256_DIGEST_LENGTH) != 0) {
            printf("Block %lu hash does not match the stored hash!\n", i);
            return 0;
        }

        // Check if the hash matches the difficulty
        if (!hash_matches_difficulty(hash, current->info.difficulty)) {
            printf("Block %lu hash does not meet the difficulty requirement!\n",
                   i);
            return 0;
        }

        // Extract metadata from the block
        char *data = (char *) current->data.buffer;
        char file_path[256];
        long file_size;
        time_t file_ctime;

        // Assuming the metadata is stored in the format: "File: <file>, Size: <size> bytes, Created: <ctime>"
        if (sscanf(data, "File: %255[^,], Size: %ld bytes, Created: %ld",
                   file_path, &file_size, &file_ctime) != 3) {
            printf("Block %lu metadata is corrupted!\n", i);
            return 0;
        }

        // Verify file metadata
        struct stat file_stat;
        if (stat(file_path, &file_stat) == -1) {
            perror("stat");
            printf("Block %lu file metadata verification failed: %s\n", i,
                   file_path);
            return 0;
        }

        if (file_stat.st_size != file_size || file_stat.st_ctime !=
            file_ctime) {
            printf("Block %lu file metadata does not match: %s\n", i,
                   file_path);
            return 0;
        }
    }

    printf("Blockchain is valid\n");
    return 1;
}
