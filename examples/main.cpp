#include <iostream>
#include <LWTML/LWTML.hpp>
#include <cmath>

void bitmapTest(){
    Renderer* renderer = new Renderer();
    Keyboard* keyboard = Keyboard::shared_keyboard();
    Bitmap* bitmap = renderer->standardBitmap();
    int r_count = 0;
    int g_count = 0;
    int b_count = 0;
    Timer* timer = new Timer();
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
        timer->lock_at_fps(30);
    }
    delete bitmap;
}

void sin_test(){
    Renderer* renderer = new Renderer();
    Bitmap* bitmap = renderer->standardBitmap();
    Keyboard* keyboard = Keyboard::shared_keyboard();
    float count = 0;
    Timer* timer = new Timer();
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
        timer->lock_at_fps(15);

    }
    delete timer;
    delete bitmap;
    delete renderer;
}

void non_blocking_input_demo(){
    Keyboard* keyboard = Keyboard::shared_keyboard();
    Timer* timer = new Timer();
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
        timer->lock_at_fps(30);
    }
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
    Renderer* renderer = new Renderer(20, 20);
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
    Keyboard* keyboard = Keyboard::shared_keyboard();
    bool isRunning = true;
    Timer* timer = new Timer();

    while(isRunning){
        timer->update();
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
        timer->lock_at_fps(30);

    }
    delete timer;
    delete renderer;
    delete pop1;
    delete pop2;
}

void blitTest(){
    float count = 0;
    Renderer* renderer = new Renderer();
    Bitmap* bitmap = renderer->standardBitmap();
    Bitmap* sprite = new Bitmap(bitmap->width() / 3, bitmap->height() / 3, 0);
    Keyboard* keyboard = Keyboard::shared_keyboard();
    float color_count = 0;
    Timer* timer = new Timer();
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
        timer->update();
        timer->lock_at_fps(30);
    }
    delete bitmap;
    delete sprite;
    delete renderer;
}

void text_test(){
    float count = 0;
    Renderer* renderer = new Renderer();
    Bitmap* bitmap = renderer->standardBitmap();
    Bitmap* sprite = new Bitmap(bitmap->width() / 3, bitmap->height() / 3, 0);
    Keyboard* keyboard = Keyboard::shared_keyboard();
    Text* text = new Text("TEST!", 2, 3);
    float color_count = 0;
    Timer* timer = new Timer();
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
        timer->update();
        timer->lock_at_fps(60);
    }
    delete bitmap;
    delete sprite;
    delete renderer;
    delete text;
}

void timer_test(){
    Keyboard* keyboard = Keyboard::shared_keyboard();
    Timer* timer = Timer::locked_at_fps(1);
    while(true){
        keyboard->update();
        timer->update();
        int test = 0;
        for(int i = 0; i < 100000000; i++){
            test++;
        }
        std::cout << "delta_time: " << timer->delta_time() << std::endl;
        if(keyboard->isKeyDown('q')){
            break;
        }
    }
    delete timer;
}

int main(int argc, char** argv){
    //timer_test();
    //text_test();
    //sin_test();
    bitmapTest();
    gol_test();
    //blitTest();
    //non_blocking_input_demo();
    return 0;
}

