#ifndef GDT_H
# define GDT_H

# include "stdint.h"

# define LIMIT	0xFFFFFFFF
# define GRAN	0xCF

struct gdt_entry_struct
{
	uint16_t	limit;
	uint16_t	base_low;
	uint8_t		base_middle;
	uint8_t		access;
	uint8_t		flags;
	uint8_t		base_high;
} __attribute__((packed));

struct gdt_ptr_struct
{
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed));

void init_gdt();
void set_gdt_gate(int num, int base, int limit, int access, int gran);

#endif
