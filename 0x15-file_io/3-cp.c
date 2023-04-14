#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

void error(const char *msg);
void close_file(int fd);
int copy_file(const char *src, const char *dest);

int main(int argc, char *argv[])
{
    if (argc != 3) {
        error("Usage: cp file_from file_to");
    }

    int ret = copy_file(argv[1], argv[2]);
    if (ret != 0) {
        exit(ret);
    }

    return 0;
}

void error(const char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

void close_file(int fd)
{
    if (close(fd) == -1) {
        error("Can't close file");
    }
}

int copy_file(const char *src, const char *dest)
{
    int fd_src = open(src, O_RDONLY);
    if (fd_src == -1) {
        error("Can't read from source file");
    }

    int fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd_dest == -1) {
        close_file(fd_src);
        error("Can't write to destination file");
    }

    char buffer[BUFFER_SIZE];
    ssize_t nread;

    while ((nread = read(fd_src, buffer, BUFFER_SIZE)) > 0) {
        ssize_t nwritten = write(fd_dest, buffer, nread);
        if (nwritten != nread) {
            close_file(fd_src);
            close_file(fd_dest);
            error("Error while copying file");
        }
    }

    close_file(fd_src);
    close_file(fd_dest);

    return 0;
}

