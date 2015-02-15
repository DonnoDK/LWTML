#include "Terminal.hpp"
#include <sys/ioctl.h>
#include <cstdio>

void Terminal::clearScreen(){
    printf("\033[2J");
}

void Terminal::hideCursor(){
    printf("\033[?25l");
}

void Terminal::showCursor(){
    printf("\033[?25h");
}

void Terminal::setChar(unsigned char c, unsigned int x, unsigned int y, unsigned char bgcolor, unsigned char fgcolor){
    printf("\033[%i;%iH\033[38;5;%im\033[48;5;%im%c", y + 1, x + 1, fgcolor, bgcolor, c);
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
