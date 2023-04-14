#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * read_textfile - Read text file and print to STDOUT.
 * @filename: Text file being read.
 * @letters: Number of letters to be read.
 * Return: Actual number of bytes read and printed.
 *         0 when function fails or filename is NULL.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
    int fd;
    ssize_t num_read = 0, num_written = 0;
    char *buf = NULL;

    if (filename == NULL)
        return (0);

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);

    buf = malloc(sizeof(char) * letters);
    if (buf == NULL)
    {
        close(fd);
        return (0);
    }

    num_read = read(fd, buf, letters);
    if (num_read == -1)
    {
        free(buf);
        close(fd);
        return (0);
    }

    num_written = write(STDOUT_FILENO, buf, num_read);
    if (num_written == -1)
    {
        free(buf);
        close(fd);
        return (0);
    }

    free(buf);
    close(fd);

    return (num_written);
}

