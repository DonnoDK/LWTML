#ifndef TERMINAL_HPP
#define TERMINAL_HPP
namespace Terminal{
    void clearScreen();
    void hideCursor();
    void showCursor();
    void setChar(unsigned char c, unsigned int x, unsigned int y, unsigned char bgcolor, unsigned char fgcolor);
    unsigned short width();
    unsigned short height();
};
#endif
