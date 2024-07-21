#include "ipchain.h"

int main(int argc, char *argv[]) {
    blockchain_t blockchain = {NULL, 0};

    block_t *genesis_block = create_genesis_block();
    if (!genesis_block) {
        return EXIT_FAILURE;
    }

    blockchain.blocks = malloc(sizeof(block_t));
    if (!blockchain.blocks) {
        fprintf(stderr, "Failed to allocate memory for blockchain\n");
        free(genesis_block);
        return EXIT_FAILURE;
    }

    blockchain.blocks[0] = *genesis_block;
    blockchain.size = 1;
    free(genesis_block);

    char command[256];
    while (1) {
        printf(">> ");
        if (!fgets(command, sizeof(command), stdin)) {
            perror("fgets");
            break;
        }

        // Remove newline character from command
        command[strcspn(command, "\n")] = '\0';

        // Process command
        if (strncmp(command, "init ", 4) == 0) {
            if (blockchain.size > 3) {
                printf("Blockchain already initialized\n");
            } else {
                block_t *genesis_block = create_genesis_block();
                if (!genesis_block) {
                    break;
                }

                blockchain.blocks = malloc(sizeof(block_t));
                if (!blockchain.blocks) {
                    fprintf(
                        stderr, "Failed to allocate memory for blockchain\n");
                    free(genesis_block);
                    break;
                }

                blockchain.blocks[0] = *genesis_block;
                blockchain.size = 1;
                free(genesis_block);

                // put file name path in array

                char *file_paths[] = {
                    "./example.txt",
                    "./example1.txt",
                    "./example2.txt",
                    "./example3.txt",
                    "./example4.txt",
                    "./another_file.txt",
                    "./another_file1.txt"
                };
                size_t file_count = sizeof(file_paths) / sizeof(file_paths[0]);

                for (size_t i = 0; i < file_count; i++) {
                    add_file_metadata(&blockchain, file_paths[i]);
                }

                printf("Blockchain initialized\n");
            }
        } else if (strncmp(command, "add_file ", 9) == 0) {
            add_file_metadata(&blockchain, command + 9);
        } else if (strcmp(command, "verify") == 0) {
            verify_blockchain(&blockchain);
        } else if (strcmp(command, "quit") == 0) {
            break;
        } else if (strcmp(command, "help") == 0) {
            print_usage();
        } else if (strcmp(command, "print") == 0) {
            print_blockchain(&blockchain);
        } else {
            printf("Unknown command. Use 'h' for help.\n");
        }
    }

    free(blockchain.blocks);
    return EXIT_SUCCESS;
}
