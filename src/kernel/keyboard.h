#ifndef KEYBOARD_H
# define KEYBOARD_H

extern char	read_port(unsigned short port);
extern void	write_port(unsigned short port, unsigned char data);

# define KEYBOARD_DATA_PORT 0x60
# define KEYBOARD_STATUS_PORT 0x64

# define ESCAPED_KEY_CODE 0xe0
# define RELEASED_KEY_CODE 0x80

int is_key_available();
void simulate_keyboard_interrupt();

void keyboard_handler(void);

#endif
