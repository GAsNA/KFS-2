#include "kernel.h"
#include "string.h"

/**
 * Scroll handler
 * 
 * @return void
*/
void	scroll_handler()
{
	if (terminal.current_loc >= SCREEN_SIZE)
		scroll_down();
}

//TODO: Fix scroll not copying last line as expected
void	scroll_down(void)
{
	memcpy(terminal.vidptr,terminal.vidptr + NB_COLUMNS, sizeof(short) * (NB_COLUMNS * (NB_LINES - 1)));
	clear_line(NB_LINES - 1);
	terminal.current_loc -= NB_COLUMNS;
	terminal.deletable -= NB_COLUMNS;
	move_cursor(terminal.current_loc);
}
