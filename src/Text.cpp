#include "../include/Text.hpp"

Text::Text(std::string value, unsigned char bgColor, unsigned char textColor){
    _value = value;
    _bgColor = bgColor;
    _textColor = textColor;
}

void Text::setBackgroundColor(unsigned char bgColor){
    _bgColor = bgColor;
}

void Text::setTextColor(unsigned char textColor){
    _textColor = textColor;
}

unsigned char Text::backgroundColor() const{
    return _bgColor;
}

unsigned char Text::textColor() const{
    return _textColor;
}

unsigned int Text::length() const{
    return _value.length();
}

const std::string& Text::value() const{
    return _value;
}
