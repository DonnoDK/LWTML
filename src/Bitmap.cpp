#include "../include/Bitmap.hpp"
#include <cstring>
Bitmap::Bitmap(unsigned int width, unsigned int height, unsigned char colorkey){
    _width = width;
    _height = height;
    _colorkey = colorkey;
    _pixels = new unsigned char[_width * _height];
}

Bitmap::~Bitmap(){
    delete[] _pixels;
}

void Bitmap::set_pixel(unsigned int x, unsigned int y, unsigned char color){
    if(x >= _width || y >= _height){
        /* TODO: handle error */
        return;
    }
    _pixels[x + y * _width] = color;
}

void Bitmap::blit_at_offset(Bitmap* bitmap, unsigned int xOffset, unsigned int yOffset){
    unsigned char colorkey = bitmap->colorkey();
    for(unsigned int y = 0; y < bitmap->height(); y++){
        for(unsigned int x = 0; x < bitmap->width(); x++){
            unsigned char pixel = bitmap->pixel(x, y);
            if(pixel != colorkey){
                set_pixel(xOffset + x, yOffset + y, pixel);
            }
        }
    }
}

void Bitmap::clear_with_color(unsigned char color){
    memset(_pixels, color, _width * _height);
}

unsigned char Bitmap::pixel(unsigned int x, unsigned int y) const{
    if(x >= _width || y >= _height){
        /* TODO: handle error */
        return 0;
    }
    return _pixels[x + y * _width];
}

unsigned char Bitmap::colorkey() const{
    return _colorkey;
}

unsigned int Bitmap::height() const{
    return _height;
}

unsigned int Bitmap::width() const{
    return _width;
}

