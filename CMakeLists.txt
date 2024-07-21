cmake_minimum_required(VERSION 3.28)
project(IPChain C)

set(CMAKE_C_STANDARD 11)

add_executable(IPChain main.c
        ipchain.h
        create_genesis_block.c
        calculate_hash_with_nonce.c
        add_block.c
        add_file_metadata.c
        verify_blockchain.c
        print.c
        edit_file.c)

# Find OpenSSL library
find_package(OpenSSL REQUIRED)

# Include directories for OpenSSL
include_directories(${OPENSSL_INCLUDE_DIR})

# Link OpenSSL libraries
target_link_libraries(IPChain ${OPENSSL_LIBRARIES})