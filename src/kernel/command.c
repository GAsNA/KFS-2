#include "kernel.h"

void reboot(void)
{
	uint8_t good = 0x02;
	while (good & 0x02)
		good = inb(0x64);
	outb(0x64, 0xFE);
	asm volatile ("hlt");
}

void exec_cmd(void)
{
	char cmd_rev[SCREEN_SIZE];

	// Get command
	for (int i = 1; terminal.current_loc - i >= terminal.deletable; i++)
	{
		cmd_rev[i - 1] = terminal.vidptr[terminal.current_loc - i];
	}

	int len = strlen(cmd_rev);
	int j = len - 1;
	char cmd[len + 1];

	for (int i = 0; i < len; i++)
	{
		cmd[i] = cmd_rev[j];
		j--;
	}
	cmd[len] = '\0';

	// Execute command
	if (strncmp(cmd, "reboot", 7) == 0)
		reboot();
	
	// Reinitialize cmd
	for (int i = 0; i < SCREEN_SIZE; i++)
		cmd[i] = '\0';
}
