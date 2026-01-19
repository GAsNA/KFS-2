#include "kernel.h"

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
		hexdump(cmd, 128);
	return NEWLINE;
}
