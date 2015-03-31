#include <iostream>
#include <LWTML/LWTML.hpp>
#include <cmath>

void bitmapTest(){
    Renderer* renderer = new Renderer();
    Keyboard* keyboard = Keyboard::shared_keyboard();
    Bitmap* bitmap = renderer->standard_bitmap();
    int r_count = 0;
    int g_count = 0;
    int b_count = 0;
    Timer* timer = Timer::locked_at_fps(30);
    while(true){
        timer->update();
        keyboard->update();
        if(keyboard->is_key_down('q')){
            break;
        }
        for(unsigned int y = 0; y < bitmap->height(); y++){
            for(unsigned int x = 0; x < bitmap->width(); x++){
                unsigned char r = r_count;
                unsigned char g = g_count;
                unsigned char b = b_count;
                unsigned char color = Color::color_from_rgb(r, g, b);
                bitmap->set_pixel(x, y, color);
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
    }
    delete bitmap;
    delete renderer;
    delete timer;
}

void sin_test(){
    Renderer* renderer = new Renderer();
    Bitmap* bitmap = renderer->standard_bitmap();
    Keyboard* keyboard = Keyboard::shared_keyboard();
    float count = 0;
    Timer* timer = new Timer();
    while(true){
        keyboard->update();
        if(keyboard->is_key_down('q')){
            break;
        }
        bitmap->clear_with_color(0);
        count += 0.04f;
        for(int i = 0; i < 20; i++){
            float x_sin = sin(count - (i * 0.025f)) * bitmap->width() / 2.0f;
            float y_sin = cos(count - (i * 0.025f)) * bitmap->height() / 2.0f;
            bitmap->set_pixel((bitmap->width() / 2.0f) + x_sin, bitmap->height() / 2.0f + y_sin, 196 + i);
        }
        renderer->blit(bitmap);
        timer->lock_at_fps(15);

    }
    delete timer;
    delete bitmap;
    delete renderer;
}


void text_test(){
    float count = 0;
    Renderer renderer;
    Bitmap* bitmap = renderer.standard_bitmap();
    Bitmap sprite(bitmap->width() / 3, bitmap->height() / 3, 0);
    Keyboard* keyboard = Keyboard::shared_keyboard();
    Text text("TEST!", 2, 3);
    float color_count = 0;
    Timer* timer = Timer::locked_at_fps(30);
    while(true){
        timer->update();
        keyboard->update();
        if(keyboard->is_key_down('q')){
            break;
        }
        bitmap->clear_with_color(0);
        for(unsigned int y = 0; y < sprite.height(); y++){
            for(unsigned int x = 0; x < sprite.width(); x++){
                int bgcolor = color_count + x + y + 100 % 255;
                color_count += 0.01f;
                sprite.set_pixel(x, y, bgcolor);
            }
        }
        count += 0.1f;
        bitmap->blit_at_offset(&sprite, ((bitmap->width() / 2) - (sprite.width() / 2)) + sin(count) * bitmap->width() / 2, 10);
        renderer.blit(bitmap);
        renderer.render_text(&text, 10, 10);
    }
    delete bitmap;
    delete timer;
}


int main(int argc, char** argv){
    text_test();
    sin_test();
    bitmapTest();
    return 0;
}

