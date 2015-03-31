#include "../include/Keyboard.hpp"
#include <termios.h>
#include <cstdio>
#include <sys/select.h>

static struct termios _term;
static struct termios _term_orig;
static struct timeval tv;
static fd_set fds;

Keyboard* Keyboard::_instance = NULL;

Keyboard* Keyboard::shared_keyboard(){
    if(_instance == NULL){
        _instance = new Keyboard();
    }
    return _instance;
}

Keyboard::Keyboard(){
    this->disable_echo_and_carriage_return_on_input();
    _keys = 0;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
}

Keyboard::~Keyboard(){
    reset_terminal_settings();
}

void Keyboard::disable_echo_and_carriage_return_on_input(){
    tcgetattr(fileno(stdin), &_term);
    _term_orig = _term;
    _term.c_lflag &= ~(ECHO | ICANON);
    _term.c_cc[VMIN] = 1;
    tcsetattr(fileno(stdin), TCSANOW, &_term);
}

void Keyboard::reset_terminal_settings(){
    tcsetattr(fileno(stdin), TCSANOW, &_term_orig);
}

void Keyboard::update(){
    _keys = 0;
    if(did_receive_input()){
        char c = getchar();
        if(c != '\033'){
            if(c >= 'a' && c <= 'z'){
                _keys = 1 << (c - 'a');
            }
        }else{
            c = getchar();
            if(c == '['){
                c = getchar();
                if(c >= 'A' && c <= 'D'){
                    _keys = 1 << (c - 39);
                }
            }
        }
    }
}

bool Keyboard::is_key_down(char key) const{
    if(key < 97 || key > 122){
        return false;
    }
    return _keys & (1 << (key - 97));
}

bool Keyboard::is_arrow_key_down(Keyboard::ArrowKeys arrowKey) const{
    if(arrowKey < UP || arrowKey > DOWN){
        return false;
    }
    return _keys & (1 << (arrowKey - 39));
}

bool Keyboard::did_receive_input(){
    FD_ZERO(&fds);
    FD_SET(fileno(stdin), &fds);
    select(fileno(stdin) + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(fileno(stdin), &fds);
}
