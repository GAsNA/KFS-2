#include "kernel.h"

extern char _stack_space;
extern char _stack_space_end;

void reboot(void)
{
	uint8_t good = 0x02;
	while (good & 0x02)
		good = inb(0x64);
	outb(0x64, 0xFE);
	asm volatile ("hlt");
}

void shutdown(void)
{
	outw(0x2000, 0x604);
}

void clear(void)
{
	clear_terminal();

	terminal.current_loc = 0;
	terminal.deletable = 0;
	move_cursor(0);
}

void help(void)
{
	putchar('\n');
	printk("%s: %s\n", "help", "shows this message");
	printk("%s: %s\n", "shutdown", "turns off the system");
	printk("%s: %s\n", "reboot", "restarts the system");
	printk("%s: %s\n", "clear", "clean the current terminal window");
	printk("%s: %s\n", "gdt", "prints the content of the gdt");
	printk("%s: %s\n", "hexdump", "prints the stack");
}

int exec_cmd(void)
{
	int current_line;
	char cmd[NB_COLUMNS];

	current_line = terminal.current_loc / NB_COLUMNS;
	for (int i = 0; i < NB_COLUMNS;i++)
		cmd[i] = (char)(terminal.vidptr[(current_line * NB_COLUMNS) + i] & 0xff);
	if (strncmp(cmd, "reboot", 7) == 0)
		reboot();
	else if (strncmp(cmd, "shutdown", 9) == 0)
		shutdown();
	else if (strncmp(cmd, "clear", 6) == 0)
	{
		clear();
		return NO_NEWLINE;
	}
	else if (strncmp(cmd, "hexdump", 8) == 0)
	{
		hexdump(&_stack_space, &_stack_space_end - &_stack_space);
		printk("&stack: %P\n", &_stack_space);
		printk("&stack_end: %P\n", &_stack_space_end);
	}
	else if (strncmp(cmd, "gdt", 4) == 0)
		hexdump(0x00000800, 56);
	else if (strncmp(cmd, "help", 5) == 0)
		help();
	return NEWLINE;
}
