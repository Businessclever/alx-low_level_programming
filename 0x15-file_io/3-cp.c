#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

void print_error(char *msg, int exit_code);
void close_file(int fd);
void copy_file(char *src_file, char *dest_file);

int main(int argc, char **argv) {
    if (argc != 3) {
        print_error("Usage: cp source_file destination_file\n", 97);
    }

    copy_file(argv[1], argv[2]);

    return 0;
}

void copy_file(char *src_file, char *dest_file) {
    char buffer[BUFSIZE];
    int src_fd, dest_fd, bytes_read, bytes_written;

    src_fd = open(src_file, O_RDONLY);
    if (src_fd < 0) {
        print_error("Error: Cannot open source file.\n", 98);
    }

    dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd < 0) {
        print_error("Error: Cannot create destination file.\n", 99);
    }

    while ((bytes_read = read(src_fd, buffer, BUFSIZE))) {
        if (bytes_read < 0) {
            print_error("Error: Cannot read from source file.\n", 98);
        }

        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written < 0) {
            print_error("Error: Cannot write to destination file.\n", 99);
        }
    }

    close_file(src_fd);
    close_file(dest_fd);
}

void close_file(int fd) {
    if (close(fd) < 0) {
        print_error("Error: Cannot close file descriptor.\n", 100);
    }
}

void print_error(char *msg, int exit_code) {
    fprintf(stderr, "%s", msg);
    exit(exit_code);
}

