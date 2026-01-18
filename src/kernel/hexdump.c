# include "hexdump.h"

void hexdump(char *address, unsigned int size) 
{
	for (unsigned int i = 0; i < size; i += 8)
	{
		if (i % 8 == 0)
		{
			putchar('\n');
			putaddr(address + i, LIGHT_GRAY, FILL);
		}
		putchar(' ');
		for (unsigned int j = 0;j < 8 && i + j < size; j++)
		{
			if (j % 2 == 0)
				putchar(' ');
			puthex_byte(address[i + j], (LIGHT_GRAY << 8));
			j++;
		}
	}
}
