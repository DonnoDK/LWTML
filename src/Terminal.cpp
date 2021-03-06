#include "../include/Terminal.hpp"
#include <sys/ioctl.h>
#include <cstdio>

void Terminal::clear_screen(){
    printf("\033[39;49m");
    printf("\033[0m");
    printf("\033[2J\n");
}

void Terminal::hide_cursor(){
    printf("\033[?25l");
}

void Terminal::show_cursor(){
    printf("\033[?25h");
}

void Terminal::set_char(unsigned char c, unsigned int x, unsigned int y, unsigned char bgcolor, unsigned char fgcolor){
    printf("\033[%i;%iH\033[38;5;%im\033[48;5;%im%c", y + 1, x + 1, fgcolor, bgcolor, c);
}

void Terminal::write_string(const char* string, unsigned int x, unsigned int y, unsigned bgcolor, unsigned char fgcolor){
    printf("\033[%i;%iH\033[38;5;%im\033[48;5;%im%s\n", y + 1, x + 1, fgcolor, bgcolor, string);
}

static struct winsize ws;
unsigned short Terminal::width(){
    ioctl(0, TIOCGWINSZ, &ws);
    return ws.ws_col;
}

unsigned short Terminal::height(){
    ioctl(0, TIOCGWINSZ, &ws);
    return ws.ws_row;
}
