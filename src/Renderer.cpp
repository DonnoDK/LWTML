#include "../include/Renderer.hpp"
#include "../include/Bitmap.hpp"
#include "../include/Color.hpp"
#include "../include/Terminal.hpp"
#include "../include/Text.hpp"
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
    Terminal::clear_screen();
    Terminal::hide_cursor();
}

Renderer::Renderer(){
    _width = Terminal::width();
    _height = Terminal::height();
    Terminal::clear_screen();
    Terminal::hide_cursor();
}

Renderer::~Renderer(){
    Terminal::show_cursor();
    clear_buffer(0);
    Terminal::clear_screen();
}

void Renderer::set_pixel(unsigned int x, unsigned int y, unsigned char color) const{
    unsigned int terminal_offset_x = Terminal::width() / 2.0f - _width / 2.0f + x;
    unsigned int terminal_offset_y = Terminal::height() / 2.0f - _height / 2.0f + y;
    Terminal::set_char(' ', terminal_offset_x, terminal_offset_y, color, 0);
}

void Renderer::blit(Bitmap* bitmap) const{
    unsigned char colorkey = bitmap->colorkey();
    for(unsigned int y = 0; y < bitmap->height(); y++){
        for(unsigned int x = 0; x < bitmap->width(); x++){
            unsigned char color = bitmap->pixel(x, y);
            if(color != colorkey){
                this->set_pixel(x, y, color);
            }
        }
    }
}

void Renderer::clear_buffer(unsigned char color) const{
    for(unsigned int y = 0; y < _width; y++){
        for(unsigned int x = 0; x < _height; x++){
            this->set_pixel(x, y, color);
        }
    }
}

void Renderer::render_text(Text* text, unsigned int x, unsigned int y) const{
    unsigned int str_len = text->value().length();
    if(x + str_len > _width){
        return;
    }
    Terminal::write_string(text->value().c_str(), x, y, text->bg_color(), text->text_color());
}

unsigned int Renderer::width() const{
    return _width;
}

unsigned int Renderer::height() const{
    return _height;
}

/* TODO: Bitmap* Renderer::standardBitmap(unsigned char colorkey) const */
Bitmap* Renderer::standard_bitmap() const{
    /* TODO: change to a more sane colorkey */
    /* TODO: or pass in trough parameter */
    return new Bitmap(_width, _height, Color::color_from_rgb(255,0,255));
}
