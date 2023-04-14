#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * read_textfile - reads a text file and prints it to POSIX standard output
 * @filename: name of the file to read
 * @letters: number of letters to read and print
 * Return: the actual number of letters read and printed, or 0 if failed
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd, read_count, write_count;
	char *buf;

	if (filename == NULL)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	buf = malloc(sizeof(char) * (letters + 1));
	if (buf == NULL)
		return (0);

	read_count = read(fd, buf, letters);
	if (read_count == -1)
	{
		free(buf);
		close(fd);
		return (0);
	}

	buf[read_count] = '\0';

	write_count = write(STDOUT_FILENO, buf, read_count);
	if (write_count == -1 || read_count != write_count)
	{
		free(buf);
		close(fd);
		return (0);
	}

	free(buf);
	close(fd);

	return (write_count);
}

