#include <iostream>
#include <sys/select.h>
#include <string>
#include <sstream>
#include <cmath>
#include <termios.h>
#include "Renderer.hpp"
#include "Bitmap.hpp"
#include "Keyboard.hpp"

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

#include <unistd.h> /* usleep */
void sleepForMilliseconds(unsigned int milliseconds){
    usleep(1000 * milliseconds);
}

void counterTest(){
    for(int count = 0; count < 1000000; count++){
        std::cout << "\033[60;10H";
        std::cout << count;
    }
    std::cout << std::endl;
}

void bitmapTest(){
    float count = 0;
    Bitmap* bitmap = new Bitmap(80, 24);
    Renderer* renderer = new Renderer(80, 24);
    while(true){
        count += 4.2f;
        for(int y = 1; y < 25; y++){
            for(int x = 1; x < 81; x++){
                int bgcolor = (x * y +(int)count) % 255;
                bitmap->setPixel(x, y, bgcolor);
            }
        }
        renderer->blit(bitmap);
        sleepForMilliseconds(66);
    }
}

void sin_test(){
    Bitmap* bitmap = new Bitmap(80, 24);
    Renderer* renderer = new Renderer(80, 24);
    float count = 0;
    while(true){
        count += 0.01f;
        float x_sin = sin(count) * 39.5f;
        bitmap->clear(100);
        bitmap->setPixel(40.5f + x_sin, 10, 1);
        renderer->blit(bitmap);
        sleepForMilliseconds(16);
    }
    delete bitmap;
    delete renderer;
}
void non_blocking_input_demo(){
    struct termios t, t_orig;
    tcgetattr(fileno(stdin), &t);
    t_orig = t;
    t.c_lflag &= ~(ECHO | ICANON);
    t.c_cc[VMIN] = 1;
    tcsetattr(fileno(stdin),TCSANOW,&t);
    Keyboard* keyboard = new Keyboard();
    while(true) {
        keyboard->update();
        sleepForMilliseconds(33);
    }
    tcsetattr(fileno(stdin),TCSANOW,&t_orig);
}

int main(int argc, char** argv){
    //sin_test();
    //bitmapTest();
    non_blocking_input_demo();
    return 0;
}

