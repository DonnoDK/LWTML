#include "Renderer.hpp"
#include "Bitmap.hpp"
#include "Color.hpp"
#include "Terminal.hpp"
#include "Text.hpp"
#include <iostream>

Renderer::Renderer(unsigned int width, unsigned int height){
    if(width > Terminal::width()){
        std::cerr << "[Warning] render window width is greater than terminal emulator width" << std::endl;
        std::cerr << "terminal emulator width: " << Terminal::width() << ", requested width: " << width << std::endl;
    }
    if(height > Terminal::height()){
        std::cerr << "[Warning] render window height is greater than terminal emulator height" << std::endl;
        std::cerr << "terminal emulator height: " << Terminal::height() << ", requested height: " << height << std::endl;
    }
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
    unsigned int terminal_offset_x = Terminal::width() / 2.0f - _width / 2.0f + x;
    unsigned int terminal_offset_y = Terminal::height() / 2.0f - _height / 2.0f + y;
    Terminal::setChar(' ', terminal_offset_x, terminal_offset_y, color, 0);
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

void Renderer::renderText(Text* text, unsigned int x, unsigned int y) const{
    unsigned int str_len = text->value().length();
    if(x + str_len > _width){
        return;
    }
    Terminal::writeString(text->value().c_str(), x, y, text->backgroundColor(), text->textColor());
    //void writeString(const char* string, unsigned int x, unsigned int y, unsigned bgcolor, unsigned char fgcolor);
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
