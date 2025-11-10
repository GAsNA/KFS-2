#include "kernel.h"

/**
 * Print the arguments given for printk
 *
 * @param c the character that represents the type of value to display
 * @param arg variadic argument to fetch to process the flag
 * @param colour the colour to use to print
 * @return void
 */
static void print_arg(char c, void **arg, char colour)
{
	if (c == 'c')
		print_short_on_terminal(((char)*(char *)(arg)) | (colour << 8));
	else if (c == 's')
		print_on_terminal(*(char **)(arg), colour);
	else if (c == 'p')
		putaddr((unsigned int)*(char **)(arg), colour);
	else if (c == 'i' || c == 'd')
		print_on_terminal(itoa((int)*(int **)(arg)), colour);
	else if (c == 'u')
		print_on_terminal(itoa((unsigned int)*(int **)(arg)), colour);
	else if (c == 'x')
		puthexa_small((int)*(int **)(arg), colour);
	else if (c == 'X')
		puthexa_capital((int)*(int **)(arg), colour);
	else if (c == '%')
		print_short_on_terminal('%' | (colour << 8));
}

/**
 * Print messages with a log level to the kernel
 *
 * @param fmt format string to print
 * @param ... variadic argument matching the format flags
 * @return void
 */
void printk(char *fmt, ...)
{
	int i = 0;
	int colour = LIGHT_GRAY;
	void **args = (void **) &fmt;
	args++;

	if (!fmt)
		return;

	// Print the header and choose colour
	if (strncmp(fmt, KERN_EMERG, 3) == 0)
	{
		colour = RED;
		print_on_terminal("<emerg> ", colour);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_ALERT, 3) == 0)
	{
		colour = RED;
		print_on_terminal("<alert> ", colour);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_CRIT, 3) == 0)
	{
		colour = RED;
		print_on_terminal("<crit> ", colour);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_ERR, 3) == 0)
	{
		colour = RED;
		print_on_terminal("<err> ", colour);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_WARNING, 3) == 0)
	{
		colour = YELLOW;
		print_on_terminal("<warn> ", colour);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_NOTICE, 3) == 0)
	{
		colour = MAGENTA;
		print_on_terminal("<notice> ", colour);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_INFO, 3) == 0)
	{
		colour = LIGHT_GRAY;
		print_on_terminal("<info> ", colour);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_DEBUG, 3) == 0)
	{
		colour = LIGHT_GRAY;
		print_on_terminal("<debug> ", colour);
		fmt = fmt + 3;
	}
	else if (strncmp(fmt, KERN_CONT, 3) == 0)
	{
		colour = LIGHT_GRAY;
		print_on_terminal("<cont> ", colour);
		fmt = fmt + 3;
	}
	else
	{
		colour = LIGHT_GRAY;
		print_on_terminal("<default> ", colour);
	}

	// Interpret the string
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			print_arg(fmt[i], args, colour);
			args++;
		}
		else
			print_short_on_terminal(fmt[i] | (colour << 8));
		i++;
	}
}
