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

void counterTest(){
    for(int count = 0; count < 1000000; count++){
        std::cout << "\033[60;10H";
        std::cout << count;
    }
    std::cout << std::endl;
}

void bitmapTest(){
    float count = 0;
    Renderer* renderer = new Renderer();
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
    Renderer* renderer = new Renderer();
    Bitmap* bitmap = renderer->standardBitmap();
    float count = 0;
    while(true){
        bitmap->clear(0);
        count += 0.04f;
        for(int i = 0; i < 20; i++){
            float x_sin = sin(count - (i * 0.025f)) * bitmap->width() / 2.0f;
            float y_sin = cos(count - (i * 0.025f)) * bitmap->height() / 2.0f;
            bitmap->setPixel((bitmap->width() / 2.0f) + x_sin, bitmap->height() / 2.0f + y_sin, 196 + i);
        }
        renderer->blit(bitmap);
        sleepForMilliseconds((1.0f / 15.0f) * 1000);
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
    sin_test();
    //bitmapTest();
    //non_blocking_input_demo();
    return 0;
}

