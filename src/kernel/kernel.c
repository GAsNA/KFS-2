#include "kernel.h"

t_terminal terminal;

void main(void)
{
	init_terminal();

	clear_terminal();

	print_on_terminal("42 - rleseur\n\n", LIGHT_BLUE);

	printk(KERN_ERR "This is a printk ERR test.\n");
	printk(KERN_DEFAULT "This a printk DEFAULT test.\n");
	printk(KERN_WARNING "This is a printk WARNING test.\n\n");

	print_on_terminal("You can write now:\n", GREEN);

	while(1)
		simulate_keyboard_interrupt();

	return;
}
