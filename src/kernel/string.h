#ifndef STRING_H
# define STRING_H

# define NOFILL 0
# define FILL 1 // pad a hex value to be printed as an address
int strlen(char *str);
void putchar(char c);
void putchar_colour(char c, char colour);
char *itoa(int n);
void *memcpy(void *dest, const void *src, int n);
int strncmp(char *s1, char *s2, unsigned int n);
void putaddr(int num, char colour, int filling);
void puthexa_small(int nb, char colour);
void puthexa_capital(int nb, char colour);
void puthex_byte(unsigned char c);

#endif
