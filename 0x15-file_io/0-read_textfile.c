#include "fileio.h"
#include <stdlib.h>

/*
Reads a text file and writes its contents to standard output.
Parameters:
  filename: the name of the file to read.
  letters: the maximum number of characters to read.
Returns:
  The actual number of bytes read and printed on success, or 0 on failure.
*/
ssize_t read_textfile(const char *filename, size_t letters) {
    char *buf;
    ssize_t fd;
    ssize_t w;
    ssize_t t;

    fd = open_file(filename, READ_ONLY);
    if (fd == -1) {
        return 0;
    }

    buf = malloc(sizeof(char) * letters);
    t = read_file(fd, buf, letters);
    w = write_to_stdout(buf, t);

    free(buf);
    close_file(fd);

    return w;
}

