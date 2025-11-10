#include "kernel.h"

static void	save_terminal_to_screen()
{
	for (int i = 0; i < SCREEN_SIZE; i++)
	{
		terminal.screens[terminal.current_screen].buffer[i] = terminal.vidptr[i];
	}
	terminal.screens[terminal.current_screen].current_loc = terminal.current_loc;
	terminal.screens[terminal.current_screen].deletable = terminal.deletable;
}

// composite char : 8 bits for char 8bits for colour
static void load_screen_to_terminal(int screen_number)
{
	for (int i = 0; i < SCREEN_SIZE; i++)
	{
		short composite_char = terminal.screens[screen_number].buffer[i];
		if (composite_char & 0xff == '\n')
			newline_on_terminal();
		else if (composite_char & 0xff == '\t')
			tab_on_terminal((composite_char >> 8) & 0xff);
		else
			terminal.vidptr[terminal.current_loc++] = composite_char;
	}
	terminal.current_loc = terminal.screens[screen_number].current_loc;
	terminal.deletable = terminal.screens[screen_number].deletable;
	move_cursor(terminal.current_loc);
}

/**
 * Change the current visualized screen
 *
 * @param screen_number number of the screen to display
 * @return void
 */
void change_screen(int screen_number)
{
	if (screen_number < 0 || screen_number >= LIMIT_NB_SCREENS)
		return;

	save_terminal_to_screen();
	clear_terminal();

	terminal.current_loc = 0;
	terminal.current_screen = screen_number;

	load_screen_to_terminal(screen_number);

}
