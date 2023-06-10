#include <stdlib.h>
#include <stdio.h>
#include "hash_tables.h"

int main(void)
{
    hash_table_t *ht;

    ht = hash_table_create(1024);
    if (ht == NULL)
    {
        fprintf(stderr, "Failed to create the hash table.\n");
        return EXIT_FAILURE;
    }

    printf("Hash table created at address: %p\n", (void *)ht);

    return EXIT_SUCCESS;
}

