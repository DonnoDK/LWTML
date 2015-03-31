#include <LWTML.hpp>
#include <cmath>
int main(int argc, char** argv){
    float count = 0;
    Renderer renderer;
    Bitmap bitmap(renderer.width(), renderer.height(), Color::color_from_rgb(255, 0, 255));
    Bitmap sprite(bitmap.width() / 3, bitmap.height() / 3, 0);
    Keyboard keyboard;
    float color_count = 0;
    Timer timer;
    while(true){
        timer.update();
        keyboard.update();
        if(keyboard.is_key_down('q')){
            break;
        }
        bitmap.clear_with_color(0);
        for(unsigned int y = 0; y < sprite.height(); y++){
            for(unsigned int x = 0; x < sprite.width(); x++){
                int bgcolor = color_count + x + y + 100 % 255;
                color_count += 0.01f;
                sprite.set_pixel(x, y, bgcolor);
            }
        }
        count += 0.1f;
        bitmap.blit_at_offset(&sprite, ((bitmap.width() / 2) - (sprite.width() / 2)) + sin(count) * bitmap.width() / 2, 10);
        renderer.blit(&bitmap);
        timer.lock_at_fps(30);
    }
    return 0;
}
