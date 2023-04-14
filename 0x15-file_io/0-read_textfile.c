#include "main.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


/**

 * read_textfile- Read text file print to STDOUT.

 * @filename: text file being read

 * @letters: number of letters to be read

 * Return: w- actual number of bytes read and printed

 *        0 when function fails or filename is NULL.

 */

ssize_t read_textfile(const char *filename, size_t letters)
{
        char buf[1024];
        ssize_t fd, nread, nwritten = 0;

        if (!filename)
                return (0);

        fd = open(filename, O_RDONLY);
        if (fd == -1)
                return (0);

        while ((nread = read(fd, buf, sizeof(buf))) > 0) {
                if (nwritten + nread > letters)
                        nread = letters - nwritten;
                if (write(STDOUT_FILENO, buf, nread) != nread) {
                        close(fd);
                        return (0);
                }
                nwritten += nread;
                if (nwritten == letters)
                        break;
        }

        close(fd);

        return (nwritten);
}

