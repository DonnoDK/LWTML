#include "../include/Text.hpp"

Text::Text(std::string value, unsigned char bgColor, unsigned char textColor){
    _value = value;
    _bgColor = bgColor;
    _textColor = textColor;
}

void Text::set_bg_color(unsigned char bgColor){
    _bgColor = bgColor;
}

void Text::set_text_color(unsigned char textColor){
    _textColor = textColor;
}

unsigned char Text::bg_color() const{
    return _bgColor;
}

unsigned char Text::text_color() const{
    return _textColor;
}

unsigned int Text::length() const{
    return _value.length();
}

const std::string& Text::value() const{
    return _value;
}
