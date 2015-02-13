#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
class Keyboard{
private:
    void disableEchoAndCarriageReturnOnInput();
    void resetTerminalSettings();
public:
    Keyboard();
    ~Keyboard();
    void update();
    bool isKeyDown();
};
#endif
