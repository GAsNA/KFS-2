#ifndef PRINTK_H
# define PRINTK_H

# define KERN_EMERG "<0>"	// RED
# define KERN_ALERT "<1>"	// RED
# define KERN_CRIT "<2>"	// RED
# define KERN_ERR "<3>"		// RED
# define KERN_WARNING "<4>"	// YELLOW
# define KERN_NOTICE "<5>"	// MAGENTA
# define KERN_INFO "<6>"	// LIGHT_GRAY
# define KERN_DEBUG "<7>"	// LIGHT_GRAY
# define KERN_DEFAULT ""	// LIGHT_GRAY
# define KERN_CONT "<c>"	// LIGHT_GRAY

void printk(char *fmt, ...);

#endif
