#include <LWTML/LWTML.hpp>
#include <cmath>
int main(int argc, char** argv){
    float count = 0;
    Renderer* renderer = new Renderer();
    Bitmap* bitmap = renderer->standardBitmap();
    Bitmap* sprite = new Bitmap(bitmap->width() / 3, bitmap->height() / 3, 0);
    Keyboard* keyboard = Keyboard::shared_keyboard();
    float color_count = 0;
    Timer* timer = Timer::locked_at_fps(30);
    while(true){
        timer->update();
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
    }
    delete bitmap;
    delete sprite;
    delete renderer;
    delete timer;
    return 0;
}
