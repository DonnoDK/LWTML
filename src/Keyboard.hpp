#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
class Keyboard{
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
    enum ArrowKeys{
        UP = 65,
        RIGHT,
        LEFT,
        DOWN
    };
};
#endif
