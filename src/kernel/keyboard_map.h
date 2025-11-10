#ifndef KEYBOARD_MAP_H
# define KEYBOARD_MAP_H

enum Keycode {
	ERROR,
	ESCAPE,
	ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, DASH, EQUAL, BACKSPACE,
	TAB, Q, W, E, R, T, Y, U, I, O, P, LBRACKET, RBRACKET,
	ENTER,
	LCTRL,
	A, S, D, F, G, H, J, K, L, SEMICOLON, SINGLEQUOTE,
	GRAVEACCENT,
	LSHIFT,
	BACKSLASH,
	Z, X, C, V, B, N, M, COMMA, POINT, SLASH, RSHIFT,
	ASTERISK,
	LALT, SPACEBAR,
	CAPSLOCK,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
	NUMSLOCK,
	SCROLLLOCK,
	KEYPAD7, KEYPAD8, KEYPAD9,
	MINUS,
	KEYPAD4, KEYPAD5, KEYPAD6, PLUS,
	KEYPAD1, KEYPAD2, KEYPAD3,
	KEYPAD0, KEYPADPOINT,
	IGNORE1, IGNORE2, IGNORE3,
	F11, F12,
	UNDEFINED,
};

typedef struct s_key
{
	int	small;
	int	capital;
	int numslock;
} t_key;

t_key keyboard_map[128] =
{
	{ .small = 0, .capital = 0, .numslock = 0 },		/* ERROR */
	{ .small = 27, .capital = 27, .numslock = 0 },		/* ESCAPE */
	{ .small = '1', .capital = '!', .numslock = 0 },
	{ .small = '2', .capital = '@', .numslock = 0 },
	{ .small = '3', .capital = '#', .numslock = 0 },
	{ .small = '4', .capital = '$', .numslock = 0 },
	{ .small = '5', .capital = '%', .numslock = 0 },
	{ .small = '6', .capital = '^', .numslock = 0 },
	{ .small = '7', .capital = '&', .numslock = 0 },
	{ .small = '8', .capital = '*', .numslock = 0 },
	{ .small = '9', .capital = '(', .numslock = 0 },
	{ .small = '0', .capital =')', .numslock = 0 },
	{ .small = '-', .capital = '_', .numslock = 0 },
	{ .small = '=', .capital = '+', .numslock = 0 },
	{ .small = '\b', .capital = '\b', .numslock = 0 },	/* BACKSPACE */
	{ .small = '\t', .capital = '\t', .numslock = 0 },	/* TAB */
	{ .small = 'q', .capital = 'Q', .numslock = 0 },
	{ .small = 'w', .capital = 'W', .numslock = 0 },
	{ .small = 'e', .capital = 'E', .numslock = 0 },
	{ .small = 'r', .capital = 'R', .numslock = 0 },
	{ .small = 't', .capital = 'T', .numslock = 0 },
	{ .small = 'y', .capital = 'Y', .numslock = 0 },
	{ .small = 'u', .capital = 'U', .numslock = 0 },
	{ .small = 'i', .capital = 'I', .numslock = 0 },
	{ .small = 'o', .capital = 'O', .numslock = 0 },
	{ .small = 'p', .capital = 'P', .numslock = 0 },
	{ .small = '[', .capital = '{', .numslock = 0 },
	{ .small = ']', .capital = '}', .numslock = 0 },
	{ .small = '\n', .capital = '\n', .numslock = 0 },	/* ENTER */
	{ .small = 0, .capital = 0, .numslock = 0 },		/* LCRTL */
	{ .small = 'a', .capital = 'A', .numslock = 0 },
	{ .small = 's', .capital = 'S', .numslock = 0 },
	{ .small = 'd', .capital = 'D', .numslock = 0 },
	{ .small = 'f', .capital = 'F', .numslock = 0 },
	{ .small = 'g', .capital = 'G', .numslock = 0 },
	{ .small = 'h', .capital = 'H', .numslock = 0 },
	{ .small = 'j', .capital = 'J', .numslock = 0 },
	{ .small = 'k', .capital = 'K', .numslock = 0 },
	{ .small = 'l', .capital = 'L', .numslock = 0 },
	{ .small = ';', .capital = ':', .numslock = 0 },
	{ .small = '\'', .capital = '\"', .numslock = 0 },
	{ .small = '`', .capital = '~', .numslock = 0 },
	{ .small = 0, .capital = 0 , .numslock = 0},		/* LSHIFT */
	{ .small = '\\', .capital = '|', .numslock = 0 },
	{ .small = 'z', .capital = 'Z', .numslock = 0 },
	{ .small = 'x', .capital = 'X', .numslock = 0 },
	{ .small = 'c', .capital = 'C', .numslock = 0 },
	{ .small = 'v', .capital = 'V', .numslock = 0 },
	{ .small = 'b', .capital = 'B', .numslock = 0 },
	{ .small = 'n', .capital = 'N', .numslock = 0 },
	{ .small = 'm', .capital = 'M', .numslock = 0 },
	{ .small = ',', .capital = '<', .numslock = 0 },
	{ .small = '.', .capital = '>', .numslock = 0 },
	{ .small = '/', .capital = '?', .numslock = 0 },
	{ .small = 0, .capital = 0, .numslock = 0 },		/* RSHIFT */
	{ .small = 0, .capital = 0, .numslock = '*' },
	{ .small = 0, .capital = 0, .numslock = 0 },		/* LALT */
	{ .small = ' ', .capital = ' ', .numslock = 0 },
	{ .small = 0, .capital = 0, .numslock = 0 },		/* CAPSLOCK */
	{ .small = 0, .capital = 0, .numslock = 0 },		/* F1... */
	{ .small = 0, .capital = 0, .numslock = 0 },
	{ .small = 0, .capital = 0, .numslock = 0 },
	{ .small = 0, .capital = 0, .numslock = 0 },
	{ .small = 0, .capital = 0, .numslock = 0 },
	{ .small = 0, .capital = 0, .numslock = 0 },
	{ .small = 0, .capital = 0, .numslock = 0 },
	{ .small = 0, .capital = 0, .numslock = 0 },
	{ .small = 0, .capital = 0, .numslock = 0 },
	{ .small = 0, .capital = 0, .numslock = 0 },		/* F10... */
	{ .small = 0, .capital = 0, .numslock = 0 },		/* NUMSLOCK */
	{ .small = 0, .capital = 0, .numslock = 0 },		/* SCROLLLOCK */
	{ .small = 0, .capital = 0, .numslock = '7' },		/* KEYPAD7 */
	{ .small = 0, .capital = 0, .numslock = '8' },		/* KEYPAD8 */
	{ .small = 0, .capital = 0, .numslock = '9' },		/* KEYPAD9 */
	{ .small = 0, .capital = 0, .numslock = '-' },		/* MINUS */
	{ .small = 0, .capital = 0, .numslock = '4' },		/* KEYPAD4 */
	{ .small = 0, .capital = 0, .numslock = '5' },		/* KEYPAD5 */
	{ .small = 0, .capital = 0, .numslock = '6' },		/* KEYPAD6 */
	{ .small = 0, .capital = 0, .numslock = '+' },		/* PLUS */
	{ .small = 0, .capital = 0, .numslock = '1' },		/* KEYPAD1 */
	{ .small = 0, .capital = 0, .numslock = '2' },		/* KEYPAD2 */
	{ .small = 0, .capital = 0, .numslock = '3' },		/* KEYPAD3 */
	{ .small = 0, .capital = 0, .numslock = '0' },		/* KEYPAD0 */
	{ .small = 0, .capital = 0, .numslock = '.' },		/* KEYPADPOINT */
	{ .small = 0, .capital = 0, .numslock = 0 },		/* IGNORE1 */
	{ .small = 0, .capital = 0, .numslock = 0 },		/* IGNORE2 */
	{ .small = 0, .capital = 0, .numslock = 0 },		/* IGNORE3 */
	{ .small = 0, .capital = 0, .numslock = 0 },		/* F11 */
	{ .small = 0, .capital = 0, .numslock = 0 },		/* F12 */
	{ .small = 0, .capital = 0, .numslock = 0 },		/* UNDEFINED */
};

#endif
