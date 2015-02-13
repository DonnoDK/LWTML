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
    tv.tv_sec = 0;
    tv.tv_usec = 0;
}

Keyboard::~Keyboard(){
    resetTerminalSettings();
}

void Keyboard::disableEchoAndCarriageReturnOnInput(){
    tcgetattr(fileno(stdin), &_term);
    _term_orig = _term;
    _term.c_cflag &= ~(ECHO | ICANON);
    _term.c_cc[VMIN] = 1;
    tcsetattr(fileno(stdin), TCSANOW, &_term);
}

void Keyboard::resetTerminalSettings(){
    tcsetattr(fileno(stdin), TCSANOW, &_term_orig);
}

void Keyboard::update(){
    if(isKeyDown()){
        char c = getchar();
        if(c == '\033'){
            c = getchar();
            if(c == '['){
                c = getchar();
                if(c == 'A'){
                    fprintf(stderr,"UP\n");
                }else if(c == 'B'){
                    fprintf(stderr,"DOWN\n");
                }else if(c == 'C'){
                    fprintf(stderr,"RIGHT\n");
                }else if(c == 'D'){
                    fprintf(stderr,"LEFT\n");
                }
            }
        }
    }
}

bool Keyboard::isKeyDown(){
    //tv.tv_sec = 0;
    //tv.tv_usec = 0;
    //fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fileno(stdin), &fds);
    select(fileno(stdin) + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(fileno(stdin), &fds);
}
