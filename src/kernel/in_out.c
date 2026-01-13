#include "kernel.h"

/**
 * Allows to read a byte of the content of an input/output port
 *
 * Function from the sys/io.h file
 *
 * @param __port port on which data is read
 * @return char of data read
 */
unsigned char inb (unsigned short int __port)
{
	unsigned char _v;

	__asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (__port));
	return _v;
}

/**
 * Allows to write a 16 bit short word to a 16 bit I/O port, using the I/O address space instead of the memory address space.
 *
 * Function from the sys/io.h file
 *
 * @param __value value to write
 * @param __port port on which data is write
 */
void outw (unsigned short int __value, unsigned short int __port)
{
	__asm__ __volatile__ ("outw %w0, %w1": : "a" (__value), "Nd" (__port));
}
