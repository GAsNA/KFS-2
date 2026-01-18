#include "kernel.h"
#include <stddef.h>
#include <stdarg.h>

/**
 * Calcul the len of a string
 *
 * @param str the string
 * @return number of char in this str
 */
int strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;

	return len;
}

/**
 * Calcul the number of digits in a number
 *
 * @param n the number
 * @return number of digits
 */
static int nbrlen(int n)
{
	long	nb = n;
	int	len = 0;

	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

void putchar(char c)
{
	print_short_on_terminal(c | (LIGHT_GRAY << 8));
}

void putchar_colour(char c, char colour)
{
	print_short_on_terminal(c | (colour << 8));
}
/**
 * Transform an int to a string
 *
 * @param n the number to transform
 * @return the string of the number
 */
char *itoa(int n)
{
	long	nb = n;
	int	len = nbrlen(nb), i;
	static char	str[5];

	if (!str)
		return (0);
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	i = len;
	while (nb > 0)
	{
		str[--i] = (nb % 10) + '0';
		nb /= 10;
	}
	str[len] = '\0';
	return (str);
}

/**
 * Copy n bytes from src memory to dest memory
 *
 * @param dest memory to which the bytes are copied
 * @param src memory from which the bytes are copied
 * @param n number of bytes to copy
 * @return pointer to dest memory
 */
void *memcpy(void *dest, const void *src, int n)
{
	int i;

	if (!dest && !src)
		return 0;

	i = -1;
	if (dest > src)
	{
		while (n--)
			((unsigned char *) dest)[n] = ((unsigned char *) src)[n];
		return dest;
	}
	while (++i < n)
		((unsigned char *) dest)[i] = ((unsigned char *) src)[i];

	return dest;
}

/**
 * Compare n bytes from two strings
 *
 * @param s1 first string to compare
 * @param s2 second string to compare
 * @param n the number of bytes to compare
 * @return the difference between the first different characters
 */
int strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * Print a memory address in hexa
 *
 * @param num the value to which the address belongs
 * @param colour the colour to use to print
 * @return void
 */
void putaddr(int num, char colour, int fill_address)
{
	char str[8];
	int character_count;

	character_count = 0;
	do
	{
		str[character_count++] = ("0123456789abcdef"[num % 16]);
		num = num / 16;
	} while (num > 0);
	character_count--;
	print_on_terminal("0x", colour);
	if (fill_address)
	{
		for (int filling = 8 - character_count; filling > 0; filling--)
			putchar_colour('0', colour);
	}
	while (character_count >= 0)
	{
		putchar_colour(str[character_count], colour);
		character_count--;
	}
}

/**
 * Print a value in hexa in small characters
 *
 * @param nb the value to convert and print
 * @param colour the colour to use to print
 * @return void
 */
void puthexa_small(int nb, char colour)
{
	char *hexa = "0123456789abcdef";
	long	n;

	n = nb;
	if (n < 0)
		n += 4294967296;
	if (n >= 16)
	{
		puthexa_small(n / 16, colour);
		print_short_on_terminal(hexa[n % 16] | (colour << 8));
	}
	else
		print_short_on_terminal(hexa[n] | (colour << 8));
}

/**
 * Print a value in hexa in capital characters
 *
 * @param nb the value to convert and print
 * @param colour the colour to use to print
 * @return void
 */
void puthexa_capital(int nb, char colour)
{
	char *hexa = "0123456789ABCDEF";
	long	n;

	n = nb;
	if (n < 0)
		n += 4294967296;
	if (n >= 16)
	{
		puthexa_capital(n / 16, colour);
		print_short_on_terminal(hexa[n % 16] | (colour << 8));
	}
	else
		print_short_on_terminal(hexa[n] | (colour << 8));
}

void puthex_byte(char c)
{
	char *hexa = "0123456789ABCDEF";
	putchar(hexa[c / 16]);
	putchar(hexa[c % 16]);
}
