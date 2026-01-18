# include "hexdump.h"

void hexdump(uint32_t *upper_address, uint32_t *lower_address)
{
	printk("upper: %P\n", upper_address);
	printk("lower : %P\n", lower_address);
	if (upper_address < lower_address)
	{
		uint32_t *tmp;

		printk("entered\n");
		tmp = upper_address;
		upper_address = lower_address;
		lower_address = tmp;
	}
	printk("upper: %P\n", upper_address);
	printk("lower : %P\n", lower_address);

	//force upper_address align
	upper_address = (uint32_t *)((uint32_t)upper_address & ~0x0f);
	// Printing routine
	for (int i = 0; lower_address + i < upper_address;)
	{
		printk("%P %x%x %x%x %x%x %x%x\n",
			       	lower_address + i,
				lower_address[++i],
				lower_address[++i],
				lower_address[++i],
				lower_address[++i],
				lower_address[++i],
				lower_address[++i],
				lower_address[++i],
				lower_address[++i]);
	}
}
