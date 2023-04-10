/**
 * binary_to_uint - converts a binary number to an unsigned int
 * @b: string containing the binary number
 *
 * Return: the converted number, or 0 if there is an invalid character in b or b is NULL
 */
unsigned int binary_to_uint(const char *b)
{
    if (!b)
        return 0;

    unsigned int result = 0;
    for (const char *c = b; *c; ++c)
    {
        if (*c != '0' && *c != '1')
            return 0;

        result <<= 1;
        result |= *c - '0';
    }

    return result;
}

