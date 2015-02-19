#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include "IService.hpp"
class Keyboard : public IService{
private:
    void disableEchoAndCarriageReturnOnInput();
    void resetTerminalSettings();
    bool didReceiveInput();
    unsigned int _keys;
public:
    Keyboard();
    ~Keyboard();
    void update();
    bool isKeyDown(char key) const;
    bool isArrowKeyDown(char arrowKey) const;
    unsigned int type() const;
    enum ArrowKeys{
        UP = 65,
        RIGHT,
        LEFT,
        DOWN
    };
};
#endif
