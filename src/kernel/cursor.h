#ifndef CURSOR_H
#define CURSOR_H

/* The I/O ports */
# define COMMAND_PORT 0x3D4
# define DATA_PORT 0x3D5

/* The I/O port commands */
# define HIGH_BYTE_COMMAND 14
# define LOW_BYTE_COMMAND 15

/**
 * Sends the given data to the given I/O port
 *
 * @param port The I/O port to send the data to
 * @param data The data to send to the I/O port
 */
extern void outb(unsigned short port, unsigned char data);

void move_cursor(unsigned short pos);

#endif
