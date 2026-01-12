#include "kernel.h"

/**
 * Initialize the main terminal
 *
 * @return void
 */
void init_terminal(void)
{
	terminal.vidptr = (short*)BEGIN_VGA;
	terminal.current_screen = 0;

	int i = 0;

	terminal.current_loc = 0;
	terminal.deletable = 0;
	terminal.shift = 0;
	terminal.capslock = 0;
	terminal.numslock = 1;
	terminal.to_escape = 0;
	init_screens();
}

/**
 * Blank the entire terminal
 *
 * @return void
 */
void clear_terminal(void)
{
	for (int i = 0; i < NB_LINES; i++)
	{
		clear_line(i);
	}
}

/**
 * Blank one line
 *
 * @return void
 */
void	clear_line(int line_number)
{
	for (int i = 0;i < NB_COLUMNS; i++)
	{
		terminal.vidptr[line_number * NB_COLUMNS + i] = 0 | (LIGHT_GRAY << 8);
	}
}

/**
 * Add a newline on the terminal ('\n')
 *
 * @return void
 */
void newline_on_terminal(void)
{
	if (terminal.current_loc / NB_COLUMNS == NB_LINES - 1)
		scroll_down();
	int filling = NB_COLUMNS - (terminal.current_loc % NB_COLUMNS);
	if ((terminal.vidptr[terminal.current_loc] & 0xff) != '\0')
	{
		memcpy(&terminal.vidptr[terminal.current_loc + filling],
			&terminal.vidptr[terminal.current_loc],
			(SCREEN_SIZE - terminal.current_loc - filling) * sizeof(short));
	}
	for (int i = 0; i < filling; i++)
		terminal.vidptr[terminal.current_loc + i] = ' ' | (LIGHT_GRAY << 8);
	terminal.current_loc += filling;
	terminal.deletable = terminal.current_loc;
	move_cursor(terminal.current_loc);
}

/**
 * Delete a char on the terminal ('\b')
 *
 * @return void
 */
void delete_on_terminal(void)
{
	if (terminal.current_loc <= terminal.deletable)
		return;
	if (terminal.current_loc > 0 && terminal.current_loc <= SCREEN_SIZE)
	{
		memcpy(&terminal.vidptr[terminal.current_loc - 1],
			&terminal.vidptr[terminal.current_loc],
			sizeof(short) * (SCREEN_SIZE - terminal.current_loc - 1));
		terminal.current_loc--;
		move_cursor(terminal.current_loc);
	}
}

/**
 * Add a tab on the terminal ('\t')
 *
 * @return void
 */
void tab_on_terminal(char colour)
{
	int i = 0;
	short space = ' ' | (colour << 8);
	if (terminal.current_loc + TAB_SIZE >= SCREEN_SIZE)
		scroll_down();
	for (int i = 0; i < TAB_SIZE; i++)
		print_short_on_terminal(space);
}

/**
 * Print a char on the terminal
 *
 * @param c (8 bits for colour | 8 bits for char)
 * @return void
 */
void print_short_on_terminal(short c)
{
	if ((c & 0xff) == '\b')
	{
		delete_on_terminal();
		return;
	}
	if ((c & 0xff) == '\n')
	{
		newline_on_terminal();
		return;
	}
	if ((c & 0xff) == '\t')
	{
		tab_on_terminal((c >> 8) & 0xff);
		return;
	}
	/* You are an ugly child but we still love you */
	if (terminal.vidptr[SCREEN_SIZE - 1] & 0xff != '\0')
		scroll_down();
	if ((terminal.vidptr[terminal.current_loc] & 0xff) != '\0'
		&& terminal.current_loc <= SCREEN_SIZE)
	{
		memcpy(&terminal.vidptr[terminal.current_loc + 1],
			&terminal.vidptr[terminal.current_loc],
			sizeof(short) * (SCREEN_SIZE - terminal.current_loc - 1));
	}
	terminal.vidptr[terminal.current_loc++] = c;
	scroll_handler();
	move_cursor(terminal.current_loc);
}

/**
 * Print a string on the terminal
 *
 * @param str string to display
 * @param colour colour of the str to display
 * @return void
 */
void print_on_terminal(char *str, char colour)
{
	unsigned int i = 0;

	// this loop writes the string to video memory
	for (int i = 0; str[i] ; i++)
	{
		short composite_char = (colour << 8) | str[i];
		print_short_on_terminal(composite_char);
	}
}
