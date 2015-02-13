#include <cstdio>
#include "Renderer.hpp"
#include "Bitmap.hpp"
Renderer::Renderer(unsigned int width, unsigned int height){
    _width = width;
    _height = height;
    this->clearScreen();
    this->hideCursor();
}

void Renderer::clearScreen() const{
    printf("\033[2J");
}

void Renderer::hideCursor() const{
    printf("\033[?25l");
}

void Renderer::setPixel(unsigned int x, unsigned int y, unsigned char color) const{
    printf("\033[%i;%iH\033[48;5;%im ", y + 1, x + 1, color);
}

void Renderer::blit(Bitmap* bitmap) const{
    for(unsigned int y = 0; y < bitmap->height(); y++){
        for(unsigned int x = 0; x < bitmap->width(); x++){
            unsigned char color = bitmap->pixel(x, y);
            this->setPixel(x, y, color);
        }
    }
}

void Renderer::clearBuffer(unsigned char color) const{
    for(unsigned int y = 0; y < _width; y++){
        for(unsigned int x = 0; x < _height; x++){
            this->setPixel(x, y, color);
        }
    }
}

unsigned int Renderer::width() const{
    return _width;
}

unsigned int Renderer::height() const{
    return _height;
}

Bitmap* Renderer::standardBitmap() const{
    return new Bitmap(_width, _height);
}
