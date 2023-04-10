#include "main.h"

/**
 * print_binary - prints the binary representation of a number
 * @n: the number to be printed in binary
 *
 * Return: void
 */
void print_binary(unsigned long int n)
{
	unsigned long int mask = 1;
	int bit_count = 0;

	mask = mask << ((sizeof(unsigned long int) * 8) - 1);

	while (mask > 0)
	{
		if ((n & mask) == 0)
		{
			if (bit_count != 0)
				_putchar('0');
		}
		else
		{
			_putchar('1');
			bit_count++;
		}
		mask = mask >> 1;
	}
	if (bit_count == 0)
		_putchar('0');
}

