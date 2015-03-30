#include <LWTML/LWTML.hpp>
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

int main(int argc, char** argv){
    Renderer* renderer = new Renderer();
    Bitmap* current_pop = renderer->standardBitmap();
    Bitmap* old_pop = renderer->standardBitmap();
    current_pop->clear(0);
    old_pop->clear(0);
    randomReseed(old_pop);
    Keyboard* keyboard = Keyboard::shared_keyboard();
    bool isRunning = true;
    Timer* timer = Timer::locked_at_fps(30);
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
        renderer->blit(current_pop);
        for(int y = 0; y < (int)current_pop->height(); y++){
            for(int x = 0; x < (int)current_pop->width(); x++){
                int cell = current_pop->pixel(x, y);
                old_pop->setPixel(x, y, cell);
            }
        }
    }
    delete timer;
    delete renderer;
    delete current_pop;
    delete old_pop;
}
