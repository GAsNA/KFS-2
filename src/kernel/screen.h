#ifndef SCREEN_H
# define SCREEN_H

t_screen init_screen(void);

void add_char_to_screen_buffer(char c, int colour, int nb_screen);
void add_str_to_screen_buffer(char *c, int colour, int nb_screen);
void add_char_to_current_screen_buffer(char c, int colour);
void add_str_to_current_screen_buffer(char *c, int colour);

void change_screen(int screen_number);

void delete_on_screen(int nb_screen);
void move_buffer_screen_to_left(int screen_number);

#endif
