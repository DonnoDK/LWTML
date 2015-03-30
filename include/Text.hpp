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
    void setBackgroundColor(unsigned char bfColor);
    void setTextColor(unsigned char textColor);
    unsigned char backgroundColor() const;
    unsigned char textColor() const;
    unsigned int length() const;
    const std::string& value() const;
};
#endif
