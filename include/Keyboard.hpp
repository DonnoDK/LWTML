#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
class Keyboard{
private:
    void disableEchoAndCarriageReturnOnInput();
    void resetTerminalSettings();
    bool didReceiveInput();
    unsigned int _keys;
    static Keyboard* _instance;
public:
    enum ArrowKeys{
        UP = 65,
        RIGHT,
        LEFT,
        DOWN
    };
    static Keyboard* shared_keyboard();
    Keyboard();
    ~Keyboard();
    void update();
    bool isKeyDown(char key) const;
    bool isArrowKeyDown(ArrowKeys arrowKey) const;
    unsigned int type() const;
};
#endif
