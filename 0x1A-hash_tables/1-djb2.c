#include "hash_tables.h"

/**
 * hash_djb2 - Computes the hash of a string using the djb2 algorithm
 * @str: String to hash
 *
 * Return: Value of the 64-bit hash
 */
unsigned long int hash_djb2(const unsigned char *str)
{
    unsigned long int hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

