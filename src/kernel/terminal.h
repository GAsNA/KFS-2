#ifndef TERMINAL_H
# define TERMINAL_H

void init_terminal(void);

void clear_line(int line_number);
void clear_terminal(void);
void newline_on_terminal(void);
void delete_on_terminal(void);
void tab_on_terminal(char colour);

void move_buffer_terminal_to_left(void);

void print_short_on_terminal(short composite_char);
void print_on_terminal(char *str, char colour);

#endif
