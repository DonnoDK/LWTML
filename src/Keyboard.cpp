#include "Keyboard.hpp"
#include <termios.h>
#include <cstdio>
#include <sys/select.h>

static struct termios _term;
static struct termios _term_orig;
static struct timeval tv;
static fd_set fds;

Keyboard::Keyboard(){
    this->disableEchoAndCarriageReturnOnInput();
    _keys = 0;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
}

Keyboard::~Keyboard(){
    resetTerminalSettings();
}

void Keyboard::disableEchoAndCarriageReturnOnInput(){
    tcgetattr(fileno(stdin), &_term);
    _term_orig = _term;
    _term.c_lflag &= ~(ECHO | ICANON);
    _term.c_cc[VMIN] = 1;
    tcsetattr(fileno(stdin), TCSANOW, &_term);
}

void Keyboard::resetTerminalSettings(){
    tcsetattr(fileno(stdin), TCSANOW, &_term_orig);
}

void Keyboard::update(){
    _keys = 0;
    if(didReceiveInput()){
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

bool Keyboard::isKeyDown(char key) const{
    if(key < 97 || key > 122){
        return false;
    }
    return _keys & (1 << (key - 97));
}

bool Keyboard::isArrowKeyDown(char arrowKey) const{
    if(arrowKey < UP || arrowKey > DOWN){
        return false;
    }
    return _keys & (1 << (arrowKey - 39));
}

bool Keyboard::didReceiveInput(){
    FD_ZERO(&fds);
    FD_SET(fileno(stdin), &fds);
    select(fileno(stdin) + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(fileno(stdin), &fds);
}
