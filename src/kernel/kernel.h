#ifndef KERNEL_H
# define KERNEL_H

# define BEGIN_VGA 0xb8000

# define NB_LINES 25
# define NB_COLUMNS 80
# define SCREEN_SIZE (NB_COLUMNS * NB_LINES)

//TODO: Add safety on defines, if line_size = 0 division by zero might occur
# define TAB_SIZE 4

# define LIMIT_NB_SCREENS 5

typedef struct s_screen
{
	short	buffer[SCREEN_SIZE];
	int		current_loc;
	int		deletable;
} t_screen;

typedef struct s_terminal
{
	short		*vidptr;
	int		current_screen;
	t_screen	screens[LIMIT_NB_SCREENS];
	int		current_loc;
	int		deletable;
	int		shift;
	int		capslock;
	int		numslock;
	int		to_escape;
} t_terminal;

extern t_terminal terminal;

# include "colour.h"
# include "keyboard.h"
# include "terminal.h"
# include "screen.h"
# include "string.h"
# include "printk.h"
# include "cursor.h"
# include "scroll.h"

#endif
