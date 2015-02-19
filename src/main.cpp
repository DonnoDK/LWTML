#include <iostream>
#include <cmath>
#include "Renderer.hpp"
#include "Bitmap.hpp"
#include "Keyboard.hpp"
#include "Color.hpp"
#include "Random.hpp"
#include "Time.hpp"
#include "Text.hpp"
#include "ServiceLocator.hpp"

void counterTest(){
    for(int count = 0; count < 1000000; count++){
        std::cout << "\033[60;10H";
        std::cout << count;
    }
    std::cout << std::endl;
}

void bitmapTest(){
    ServiceLocator* sl = new ServiceLocator();
    sl->installService(new Renderer());
    sl->installService(new Keyboard());
    Renderer* renderer = (Renderer*)sl->service(IService::RENDERER);
    Keyboard* keyboard = (Keyboard*)sl->service(IService::KEYBOARD_INPUT);
    Bitmap* bitmap = renderer->standardBitmap();
    int r_count = 0;
    int g_count = 0;
    int b_count = 0;
    while(true){
        keyboard->update();
        if(keyboard->isKeyDown('q')){
            break;
        }
        for(unsigned int y = 0; y < bitmap->height(); y++){
            for(unsigned int x = 0; x < bitmap->width(); x++){
                unsigned char r = r_count;
                unsigned char g = g_count;
                unsigned char b = b_count;
                unsigned char color = Color::colorFromRGB(r, g, b);
                bitmap->setPixel(x, y, color);
                if(b_count > 255){
                    r_count = 0;
                    g_count = 0;
                    b_count = 0;
                    continue;
                }
                if(g_count > 255){
                    g_count = 0;
                    b_count += 51;
                    continue;
                }
                if(r_count > 255){
                    r_count = 0;
                    g_count += 51;
                    continue;
                }
                r_count += 51;
            }
        }
        renderer->blit(bitmap);
        Time::msleep((1.0f / 30.0f) * 1000);
    }
    delete bitmap;
    delete sl;
}

void sin_test(){
    Renderer* renderer = new Renderer();
    Bitmap* bitmap = renderer->standardBitmap();
    Keyboard* keyboard = new Keyboard();
    float count = 0;
    while(true){
        keyboard->update();
        if(keyboard->isKeyDown('q')){
            break;
        }
        bitmap->clear(0);
        count += 0.04f;
        for(int i = 0; i < 20; i++){
            float x_sin = sin(count - (i * 0.025f)) * bitmap->width() / 2.0f;
            float y_sin = cos(count - (i * 0.025f)) * bitmap->height() / 2.0f;
            bitmap->setPixel((bitmap->width() / 2.0f) + x_sin, bitmap->height() / 2.0f + y_sin, 196 + i);
        }
        renderer->blit(bitmap);
        Time::msleep((1.0f / 15.0f) * 1000);
    }
    delete bitmap;
    delete keyboard;
    delete renderer;
}

void non_blocking_input_demo(){
    Keyboard* keyboard = new Keyboard();
    while(true) {
        keyboard->update();
        if(keyboard->isKeyDown('a')){
            std::cout << "YES!" << std::endl;
        }
        if(keyboard->isKeyDown('q')){
            break;
        }
        if(keyboard->isArrowKeyDown(Keyboard::UP)){
            std::cout << "UP!" << std::endl;
        }
        Time::msleep(33);
    }
    delete keyboard;
}

void randomReseed(Bitmap* map){
    for(unsigned int y = 0; y < map->height(); y++){
        for(unsigned int x = 0; x < map->width(); x++){
            int answer = Random::intFromTo(1, 2);
            if(answer % 2 == 0){
                map->setPixel(x, y, 1);
            }
        }
    }
}

void gol_test(){
    Renderer* renderer = new Renderer();
    Bitmap* pop1 = renderer->standardBitmap();
    Bitmap* pop2 = renderer->standardBitmap();
    pop1->clear(0);
    pop2->clear(0);
    Bitmap* current_pop = pop1;
    Bitmap* old_pop = pop2;
    randomReseed(current_pop);
    Bitmap* temp = current_pop;
    current_pop = old_pop;
    old_pop = temp;
    Keyboard* keyboard = new Keyboard();
    bool isRunning = true;

    while(isRunning){
        keyboard->update();
        if(keyboard->isKeyDown('q')){
            isRunning = false;
        }
        if(keyboard->isKeyDown('r')){
            randomReseed(old_pop);
            current_pop->clear(0);
            continue;
        }

        for(int y = 0; y < (int)current_pop->height(); y++){
            for(int x = 0; x < (int)current_pop->width(); x++){
                /* TODO: logic here */
                int neightbors = 0;
                for(int yi = y - 1; yi <= y + 1; yi++){
                    for(int xi = x - 1; xi <= x + 1; xi++){
                        if(xi == x && yi == y){
                            continue;
                        }
                        if(xi < 0 || yi < 0){
                            continue;
                        }
                        if(xi >= (int)current_pop->width()){
                            continue;
                        }
                        if(yi >= (int)current_pop->height()){
                            continue;
                        }
                        if(old_pop->pixel(xi, yi) > 0){
                            neightbors++;
                        }
                    }
                }
                /* alive */
                if(current_pop->pixel(x, y) > 0){
                    if(neightbors < 2 || neightbors > 3){
                        current_pop->setPixel(x, y, 0);
                    }
                }else{ /* dead */
                    if(neightbors == 3){
                        current_pop->setPixel(x, y, 1);
                    }
                }
            }
        }
        /* TODO: copy map */

        renderer->blit(current_pop);
        for(int y = 0; y < (int)current_pop->height(); y++){
            for(int x = 0; x < (int)current_pop->width(); x++){
                int cell = current_pop->pixel(x, y);
                old_pop->setPixel(x, y, cell);
            }
        }


        Time::msleep((1.0f / 60.0f) * 1000);
    }
    delete renderer;
    delete keyboard;
    delete pop1;
    delete pop2;
}

void blitTest(){
    float count = 0;
    Renderer* renderer = new Renderer();
    Bitmap* bitmap = renderer->standardBitmap();
    Bitmap* sprite = new Bitmap(bitmap->width() / 3, bitmap->height() / 3, 0);
    Keyboard* keyboard = new Keyboard();
    float color_count = 0;
    while(true){
        keyboard->update();
        if(keyboard->isKeyDown('q')){
            break;
        }
        bitmap->clear(0);
        for(unsigned int y = 0; y < sprite->height(); y++){
            for(unsigned int x = 0; x < sprite->width(); x++){
                int bgcolor = color_count + x + y + 100 % 255;
                color_count += 0.01f;
                sprite->setPixel(x, y, bgcolor);
            }
        }
        count += 0.1f;
        bitmap->blit(sprite, ((bitmap->width() / 2) - (sprite->width() / 2)) + sin(count) * bitmap->width() / 2, 10);
        renderer->blit(bitmap);
        Time::msleep((1.0f / 30.0f) * 1000);
    }
    delete keyboard;
    delete bitmap;
    delete sprite;
    delete renderer;
}

void text_test(){
    float count = 0;
    Renderer* renderer = new Renderer();
    Bitmap* bitmap = renderer->standardBitmap();
    Bitmap* sprite = new Bitmap(bitmap->width() / 3, bitmap->height() / 3, 0);
    Keyboard* keyboard = new Keyboard();
    Text* text = new Text("TEST!", 2, 3);
    float color_count = 0;
    while(true){
        keyboard->update();
        if(keyboard->isKeyDown('q')){
            break;
        }
        bitmap->clear(0);
        for(unsigned int y = 0; y < sprite->height(); y++){
            for(unsigned int x = 0; x < sprite->width(); x++){
                int bgcolor = color_count + x + y + 100 % 255;
                color_count += 0.01f;
                sprite->setPixel(x, y, bgcolor);
            }
        }
        count += 0.1f;
        bitmap->blit(sprite, ((bitmap->width() / 2) - (sprite->width() / 2)) + sin(count) * bitmap->width() / 2, 10);
        renderer->blit(bitmap);
        renderer->renderText(text, 10, 10);
        Time::msleep((1.0f / 60.0f) * 1000);
    }
    delete keyboard;
    delete bitmap;
    delete sprite;
    delete renderer;
    delete text;
}

void timer_test(){
    ServiceLocator* sl = new ServiceLocator();
    sl->installService(new Keyboard());
    Keyboard* keyboard = (Keyboard*)sl->service(IService::KEYBOARD_INPUT);
    Time::Timer* timer = new Time::Timer();
    while(true){
        keyboard->update();
        std::cout << timer->deltaTime() << std::endl;
        timer->update();
        if(keyboard->isKeyDown('q')){
            break;
        }
        Time::msleep(66);
    }
    delete sl;
    delete timer;
}

int main(int argc, char** argv){
    //timer_test();
    //text_test();
    //sin_test();
    //gol_test();
    bitmapTest();
    //blitTest();
    //non_blocking_input_demo();
    return 0;
}

