#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>
#include <cmath>
#include <termios.h>
#include <sys/poll.h>

class Terminal{
public:
    static void printCharAt(int x, int y, char symbol, int bgColor, int fgColor){
        std::cout << "\033[3" << fgColor << "m";
        std::cout << "\033[4" << bgColor << "m";
        std::cout << "\033[" << y << ";" << x << "H";
        std::cout << symbol;
        std::cout << std::endl;
    }
};
void printStringAt(int x, int y, int color, std::string string){
    std::cout << "\033[" << y << ";" << x << "H";
    std::cout << "\033[3" << color << "m";
    std::cout << string << std::endl;
}

void sleepForMilliseconds(unsigned int milliseconds){
    usleep(1000 * milliseconds);
}

void clearScreen(){
    std::cout << "\033[2J";
}

void hideCursor(){
    std::cout << "\033[?25l";
}

void counterTest(){
    for(int count = 0; count < 1000000; count++){
        std::cout << "\033[60;10H";
        std::cout << count;
    }
    std::cout << std::endl;
}

void setPixelAt(int x, int y, int color){
    std::cout << "\033[";
    std::cout << y << ";" << x << "H";
    std::cout << "\033[48;5;" << color << "m";
    std::cout << ' ';
}

void bitmapTest(){
    clearScreen();
    hideCursor();
    float count = 0;
    while(true){
        count += 4.2f;
        for(int y = 1; y < 25; y++){
            for(int x = 1; x < 81; x++){
                int bgcolor = (x * y +(int)count) % 255;
                setPixelAt(x, y, bgcolor);
            }
        }
        sleepForMilliseconds(66);
    }
    std::cout << std::endl;
}

void clearScreenBuffer(int color){
    for(int y = 1; y < 26; y++){
        for(int x = 1; x < 81; x++){
            std::cout << "\033[" << y << ";" << x << "H";
            std::cout << "\033[4" << color << "m";
            std::cout << ' ';
        }
    }
}


void enable_non_blocking(){
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}
void disable_non_blocking(){
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int kbhit(){
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void sin_test(){
    clearScreen();
    hideCursor();
    float count = 0;
    while(true){
        count += 0.05f;
        float x_sin = sin(count) * 40.0f;
        clearScreenBuffer(0);
        setPixelAt(41 + x_sin, 10, 1);
        setPixelAt(1, 1, 2);
        setPixelAt(80, 1, 2);
        setPixelAt(1, 23, 2);
        setPixelAt(80, 23, 2);
        sleepForMilliseconds(33);
    }
}
void non_blocking_input_demo(){
    struct termios t, t_orig;
    tcgetattr(fileno(stdin), &t);
    t_orig = t;
    t.c_lflag &= ~(ECHO | ICANON);
    t.c_cc[VMIN] = 1;
    tcsetattr(fileno(stdin),TCSANOW,&t);
    while(true) {
        char c;
        fprintf(stderr, "tick!\n");
        if(kbhit()){
            c = getchar();
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
            }else{
                if(c == 'q'){
                    break;
                }
            }
        }
        sleepForMilliseconds(33);
    }
    tcsetattr(fileno(stdin),TCSANOW,&t_orig);
}

int main(int argc, char** argv){
    //sin_test();
    bitmapTest();
    return 0;
}

