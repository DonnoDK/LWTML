#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
class Keyboard{
private:
    void disable_echo_and_carriage_return_on_input();
    void reset_terminal_settings();
    bool did_receive_input();
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
    bool is_key_down(char key) const;
    bool is_arrow_key_down(ArrowKeys arrowKey) const;
};
#endif
