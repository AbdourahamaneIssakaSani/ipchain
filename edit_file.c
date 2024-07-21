//
// Created by abissa on 7/21/24.
//

#include  "ipchain.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/**
 * edit_file - Edit a file by appending a tamper message
 * @file_path: The path to the file to edit
 * Return: 1 on success, 0 on failure
 */
int edit_file(const char *file_path) {
    // Attempt to open the file for writing and appending
    int fd = open(file_path, O_WRONLY | O_APPEND);
    if (fd == -1) {
        fprintf(stderr, "Error opening file '%s': %s\n", file_path,
                strerror(errno));
        return 0;
    }

    // Define the tamper message to append
    const char *tamper_message = " (Tampered)";
    ssize_t bytes_written = write(fd, tamper_message, strlen(tamper_message));
    if (bytes_written == -1) {
        fprintf(stderr, "Error writing to file '%s': %s\n", file_path,
                strerror(errno));
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);
    return 1;
}
