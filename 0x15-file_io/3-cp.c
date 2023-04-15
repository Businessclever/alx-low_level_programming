#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void close_file(int fd, char *filename) {
    if (close(fd) == -1) {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
        dprintf(STDERR_FILENO, "Error: Can't close file %s\n", filename);
        exit(100);
    }
}

int main(int argc, char *argv[]) {
    int file_from, file_to, read_return_value, write_return_value;
    char buffer[1024];

    if (argc != 3) {
        dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
        exit(97);
    }

    file_from = open(argv[1], O_RDONLY);
    if (file_from == -1) {
        dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
        exit(98);
    }

    file_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (file_to == -1) {
        dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
        exit(99);
    }

    while ((read_return_value = read(file_from, buffer, 1024)) > 0) {
        write_return_value = write(file_to, buffer, read_return_value);
        if (write_return_value != read_return_value) {
            dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
            exit(99);
        }
    }

    if (read_return_value == -1) {
        dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
        exit(98);
    }

    if (close(file_from) == -1) {
        close_file(file_from, argv[1]);
    }

    if (close(file_to) == -1) {
        close_file(file_to, argv[2]);
    }

    return 0;
}

