//
// Created by abissa on 7/21/24.
//

#include "ipchain.h"

/**
 * add_file_metadata - Add metadata about a file to the blockchain
 * @blockchain: The blockchain to add the metadata to
 * @file_path: The path to the file to add metadata for
 */
void add_file_metadata(blockchain_t *blockchain, const char *file_path) {
    struct stat file_stat;
    // resolve file from current directory
    if (stat(file_path, &file_stat) == -1) {
        fprintf(stderr, "Failed to read file metadata\n");
        return;
    }

    // if (stat(file_path, &file_stat) == -1) {
    //     perror("stat");
    //     return;
    // }


    char metadata[BLOCKCHAIN_DATA_MAX];
    snprintf(metadata, BLOCKCHAIN_DATA_MAX,
             "File: %s, Size: %ld bytes, Created: %ld", file_path,
             file_stat.st_size, file_stat.st_ctime);
    add_block(blockchain, metadata);
}
