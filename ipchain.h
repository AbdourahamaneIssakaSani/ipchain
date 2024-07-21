//
// Created by abissa on 7/21/24.
//

#ifndef IPCHAIN_H
#define IPCHAIN_H
#include <stdint.h>
#include <openssl/sha.h>
#include <time.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>

#define BLOCKCHAIN_DATA_MAX 1024
#define DIFFICULTY 2

/**
 * struct block_info_s - Block info structure
 *
 * @index:	  Index of the Block in the Blockchain
 * @difficulty: Difficulty of proof of work (hash leading zero bits)
 * @timestamp:  Time the Block was created at (UNIX timestamp)
 * @nonce:	  Salt value used to alter the Block hash
 * @prev_hash:  Hash of the previous Block in the Blockchain
 */
typedef struct block_info_s {
    uint32_t index;
    uint32_t difficulty;
    uint64_t timestamp;
    uint64_t nonce;
    uint8_t prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;

/**
 * struct block_data_s - Block data
 *
 * @buffer: Data buffer
 * @len:	Data size (in bytes)
 */
typedef struct block_data_s {
    int8_t buffer[BLOCKCHAIN_DATA_MAX];
    uint32_t len;
} block_data_t;

/**
 * struct block_s - Block structure
 *
 * @info: Block info
 * @data: Block data
 * @transactions: linked list of transaction ids (not used in this example)
 * @hash: 256-bit digest of the Block, to ensure authenticity
 */
typedef struct block_s {
    block_info_t info; /* This must stay first */
    block_data_t data; /* This must stay second */
    uint8_t hash[SHA256_DIGEST_LENGTH];
} block_t;

/**
 * struct blockchain_s - Blockchain structure
 *
 * @blocks: Array of blocks
 * @size: Number of blocks in the blockchain
 */
typedef struct blockchain_s {
    block_t *blocks;
    size_t size;
} blockchain_t;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

block_t *create_genesis_block();

void calculate_hash_with_nonce(block_t *block);

void add_block(blockchain_t *blockchain, const char *data);

void add_file_metadata(blockchain_t *blockchain, const char *file_path);

int verify_blockchain(blockchain_t *blockchain);

void print_usage();

void print_block(const block_t *block);

void print_blockchain(const blockchain_t *blockchain);
#endif //IPCHAIN_H
