#include "../include/Color.hpp"
unsigned char Color::colorFromRGB(unsigned char r, unsigned char g, unsigned b){
    unsigned char r_corrected = r / 51;
    unsigned char g_corrected = g / 51;
    unsigned char b_corrected = b / 51;
    return 16 + r_corrected * 36 + g_corrected * 6 + b_corrected;
}
