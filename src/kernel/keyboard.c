#include "kernel.h"
#include "keyboard_map.h"

/**
 * Allows to read a byte of the content of an input/output port
 *
 * Function from the sys/io.h file
 *
 * @param __port port on which data is read
 * @return char of data read
 */
static __inline unsigned char inb (unsigned short int __port)
{
	unsigned char _v;

	__asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (__port));
	return _v;
}

/**
 * Return true (1) if a byte is read from port 0x64
 *
 * @return true or false
 */
int is_key_available(void)
{
	return (inb(KEYBOARD_STATUS_PORT) & 1) == 1;
}

/**
 * If a byte is read on the keyboard port, process the information
 *
 * @return void
 */
void simulate_keyboard_interrupt(void)
{
	if (is_key_available())
		keyboard_handler();
}

/**
 * Check if the keycode corresponds to a shortcut or escaped character
 *
 * @return true if the keycode corresponds to one of this shortcut or escaped character
 */
static int check_for_shortcut_and_escaped_keycode(unsigned char keycode)
{
	int is_checked = 0;

	// TODO escaped altgr and ctrlright?

	if (keycode == CAPSLOCK)
	{
		terminal.capslock = !terminal.capslock;
		is_checked = 1;
	}
	else if (keycode == NUMSLOCK)
	{
		terminal.numslock = !terminal.numslock;
		is_checked = 1;
	}
	else if (keycode == F1)
	{
		change_screen(terminal.current_screen - 1);
		is_checked = 1;
	}
	else if (keycode == F2)
	{
		change_screen(terminal.current_screen + 1);
		is_checked = 1;
	}
	// If is left arrow or keypad 4 with no numslock, move cursor to left
	else if (keycode == KEYPAD4 && (terminal.to_escape == 1 || terminal.numslock == 0))
	{
		int new_pos = terminal.current_loc - 1;
		if (new_pos < terminal.deletable)
			return (is_checked = 1);
		terminal.current_loc = new_pos;
		move_cursor(terminal.current_loc);
		is_checked = 1;
	}
	// If is right arrow or keypad 6 with no numslock, move cursor to right
	else if (keycode == KEYPAD6 && (terminal.to_escape == 1 || terminal.numslock == 0))
	{
		if ((terminal.vidptr[terminal.current_loc] & 0xff) == '\0')
			return (is_checked = 1);
		terminal.current_loc++;
		move_cursor(terminal.current_loc);
		is_checked = 1;
	}
	// If is up arrow or keypad 8 with no numslock, move cursor up
	else if (keycode == KEYPAD8 && (terminal.to_escape == 1 || terminal.numslock == 0))
	{
		int new_pos = terminal.current_loc - NB_COLUMNS;
		if (new_pos <= terminal.deletable || new_pos < 0)
			return (is_checked = 1);
		terminal.current_loc = new_pos;
		move_cursor(terminal.current_loc);
		is_checked = 1;
	}
	// If is down arrow or keypad 2 with no numslock, move cursor down
	else if (keycode == KEYPAD2 && (terminal.to_escape == 1 || terminal.numslock == 0))
	{
		int new_pos = terminal.current_loc + NB_COLUMNS;
		if (new_pos >= SCREEN_SIZE)
			return (is_checked = 1);
		if ((terminal.vidptr[new_pos] & 0xff) == '\0')
		{
			for (;(terminal.vidptr[terminal.current_loc] & 0xff);terminal.current_loc++);
			move_cursor(terminal.current_loc);
			return (is_checked = 1);
		}
		terminal.current_loc = new_pos;
		move_cursor(terminal.current_loc);
		is_checked = 1;
	}
	// If is inser key (keypad0 code with escape code or no numslock)
	else if (keycode == KEYPAD0 && (terminal.to_escape == 1 || terminal.numslock == 0))
	{
		// TODO insert
		is_checked = 1;
	}
	// If is supp key (keypadpoint code with escape code or no numslock)
	else if (keycode == KEYPADPOINT && (terminal.to_escape == 1 || terminal.numslock == 0))
	{
		// TODO delete to right
		// perhaps use move right 1 then delete to left ?
		is_checked = 1;
	}
	// If is '/' numpad key (slash code with escape code) and no numslock, then do nothing 
	else if (keycode == SLASH && terminal.to_escape == 1 && terminal.numslock == 0)
	{
		is_checked = 1;
	}
	// If is enter numpad key (enter code with escape code) and no numslock, then do nothing 
	else if (keycode == ENTER && terminal.to_escape == 1 && terminal.numslock == 0)
	{
		is_checked = 1;
	}

	// All escaped keys have been checked
	terminal.to_escape = 0;

	return is_checked;
}

/**
 * Get a keycode from the port 0x60 and print on terminal the associated char
 *
 * @return void
 */
void keyboard_handler(void) {
	unsigned char status;
	unsigned char keycode;

	t_key selected_key;
	short selected_char;

	int is_pressed = 1;

	/* write EOI */
	write_port(0x20, 0x20);

	keycode = read_port(KEYBOARD_DATA_PORT);

	if (keycode < 0)
		return;

	/* Check if this is a key to escaped */
	/* 0xe0 code is sent before the actual code if it's a key that can be escaped */
	if (keycode == ESCAPED_KEY_CODE)
	{
		terminal.to_escape = 1;
		return;
	}

	/* Check if key is pressed or not */
	/* 0x80 is add to the actual code when the key is released/not pressed anymore */
	if (keycode >= RELEASED_KEY_CODE)
		is_pressed = 0;
	if (!is_pressed)
		keycode -= RELEASED_KEY_CODE;

	/* If not pressed and is escaped, then is not escaped */
	if (!is_pressed && terminal.to_escape)
		terminal.to_escape = 0;

	/* Check if keycode is shift */
	if (keycode == LSHIFT || keycode == RSHIFT)
	{
		if (is_pressed)
			terminal.shift = 1;
		else
			terminal.shift = 0;
		return;
	}

	/* If key is not pressed, do not write on terminal and return */
	if (!is_pressed)
		return;

//	if (terminal.to_escape == 1)
//	{
//		print_on_terminal("<escape:", MAGENTA);
//		print_on_terminal(itoa(keycode), MAGENTA);
//		print_on_terminal("> ", MAGENTA);
//	}

	/* Check the keycode for non-printable char */
	if (check_for_shortcut_and_escaped_keycode(keycode))
		return;

	/* Selected the char given by inputs */
	selected_key = keyboard_map[keycode];

	if (terminal.numslock && selected_key.numslock != 0)
	{
		if (!terminal.shift)
			selected_char = selected_key.numslock;
		else
			return;
	}
	else if (terminal.capslock && selected_key.capital != 0)
		selected_char = terminal.shift ? selected_key.small : selected_key.capital;
	else if (selected_key.small != 0)
		selected_char = terminal.shift ? selected_key.capital : selected_key.small;
	else
		return;

	/* Write on terminal the selected char */
	print_short_on_terminal(selected_char | (LIGHT_GRAY << 8));
}
