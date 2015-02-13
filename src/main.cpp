#include <iostream>
#include <sys/select.h>
#include <string>
#include <sstream>
#include <cmath>
#include <termios.h>
#include "Renderer.hpp"
#include "Bitmap.hpp"
#include "Keyboard.hpp"

#include <unistd.h> /* usleep */
void sleepForMilliseconds(unsigned int milliseconds){
    usleep(1000 * milliseconds);
}

#include <sys/ioctl.h>
unsigned short getTermWidth(){
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    return ws.ws_col;
}
unsigned short getTermHeight(){
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    return ws.ws_row;
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
    int width = getTermWidth();
    int height = getTermHeight();
    Renderer* renderer = new Renderer(width, height);
    Bitmap* bitmap = renderer->standardBitmap();
    while(true){
        count += 0.2f;
        for(unsigned int y = 0; y < bitmap->height(); y++){
            int bgcolor = (int)(y + sin(count) * 10) % 255;
            for(unsigned int x = 0; x < bitmap->width(); x++){
                bitmap->setPixel(x, y, bgcolor);
            }
        }
        renderer->blit(bitmap);
        sleepForMilliseconds((1.0f / 15.0f) * 1000);
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
        if(keyboard->isKeyDown('a')){
            std::cout << "YES!" << std::endl;
        }
        if(keyboard->isArrowKeyDown(Keyboard::UP)){
            std::cout << "UP!" << std::endl;
        }
        sleepForMilliseconds(33);
    }
    tcsetattr(fileno(stdin),TCSANOW,&t_orig);
}

int main(int argc, char** argv){
    //sin_test();
    bitmapTest();
    //non_blocking_input_demo();
    return 0;
}

