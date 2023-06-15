#include "hash_tables.h"

int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
    if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
        return (0);

    unsigned long int index = key_index((const unsigned char *)key, ht->size);
    hash_node_t *new = malloc(sizeof(hash_node_t));
    if (new == NULL)
        return (0);

    char *value_copy = strdup(value);
    if (value_copy == NULL)
    {
        free(new);
        return (0);
    }

    new->key = strdup(key);
    if (new->key == NULL)
    {
        free(new);
        free(value_copy);
        return (0);
    }

    new->value = value_copy;
    new->next = ht->array[index];
    ht->array[index] = new;

    for (unsigned long int i = index; ht->array[i]; i++)
    {
        if (strcmp(ht->array[i]->key, key) == 0)
        {
            free(ht->array[i]->value);
            ht->array[i]->value = value_copy;
            return (1);
        }
    }

    return (1);
}

