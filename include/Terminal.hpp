#ifndef TERMINAL_HPP
#define TERMINAL_HPP
namespace Terminal{
    void clear_screen();
    void hide_cursor();
    void show_cursor();
    void set_char(unsigned char c, unsigned int x, unsigned int y, unsigned char bgcolor, unsigned char fgcolor);
    void write_string(const char* string, unsigned int x, unsigned int y, unsigned bgcolor, unsigned char fgcolor);
    unsigned short width();
    unsigned short height();
};
#endif
