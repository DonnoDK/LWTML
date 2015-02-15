#include "Renderer.hpp"
#include "Bitmap.hpp"
#include "Color.hpp"
#include "Terminal.hpp"
Renderer::Renderer(unsigned int width, unsigned int height){
    _width = width;
    _height = height;
    Terminal::clearScreen();
    Terminal::hideCursor();
}

Renderer::Renderer(){
    _width = Terminal::width();
    _height = Terminal::height();
    Terminal::clearScreen();
    Terminal::hideCursor();
}

Renderer::~Renderer(){
    Terminal::showCursor();
    clearBuffer(0);
    Terminal::clearScreen();
}

void Renderer::setPixel(unsigned int x, unsigned int y, unsigned char color) const{
    Terminal::setChar(' ', x, y, color, 0);
}

void Renderer::blit(Bitmap* bitmap) const{
    unsigned char colorkey = bitmap->colorkey();
    for(unsigned int y = 0; y < bitmap->height(); y++){
        for(unsigned int x = 0; x < bitmap->width(); x++){
            unsigned char color = bitmap->pixel(x, y);
            if(color != colorkey){
                this->setPixel(x, y, color);
            }
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

/* TODO: Bitmap* Renderer::standardBitmap(unsigned char colorkey) const */
Bitmap* Renderer::standardBitmap() const{
    /* TODO: change to a more sane colorkey */
    /* TODO: or pass in trough parameter */
    return new Bitmap(_width, _height, Color::colorFromRGB(255,0,255));
}
