#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void print_error_and_exit(const char *error_message, int exit_code);
void copy_file(const char *file_from, const char *file_to);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_error_and_exit("Usage: cp file_from file_to\n", 97);
    }

    const char *file_from = argv[1];
    const char *file_to = argv[2];

    copy_file(file_from, file_to);

    return 0;
}

void print_error_and_exit(const char *error_message, int exit_code) {
    fprintf(stderr, "%s", error_message);
    exit(exit_code);
}

void copy_file(const char *file_from, const char *file_to) {
    FILE *fp_from = fopen(file_from, "r");
    if (fp_from == NULL) {
        print_error_and_exit("Error: Can't read from file %s\n", 98);
    }

    FILE *fp_to = fopen(file_to, "w");
    if (fp_to == NULL) {
        fclose(fp_from);
        print_error_and_exit("Error: Can't write to %s\n", 99);
    }

    char buffer[BUFFER_SIZE];
    size_t num_bytes_read;

    while ((num_bytes_read = fread(buffer, 1, BUFFER_SIZE, fp_from)) > 0) {
        if (fwrite(buffer, 1, num_bytes_read, fp_to) != num_bytes_read) {
            fclose(fp_from);
            fclose(fp_to);
            print_error_and_exit("Error: Can't write to %s\n", 99);
        }
    }

    fclose(fp_from);
    fclose(fp_to);
}

