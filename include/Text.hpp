#ifndef TEXT_HPP
#define TEXT_HPP
#include <string>
class Text{
private:
    std::string _value;
    unsigned char _bgColor;
    unsigned char _textColor;
public:
    Text(std::string value, unsigned char bgColor, unsigned char textColor);
    void set_bg_color(unsigned char bfColor);
    void set_text_color(unsigned char textColor);
    unsigned char bg_color() const;
    unsigned char text_color() const;
    unsigned int length() const;
    const std::string& value() const;
};
#endif
