#include "MainState.hpp"
#include "Renderer.hpp"
#include "Keyboard.hpp"
#include "Color.hpp"
#include "Bitmap.hpp"

MainState::MainState(){
    _renderer = new Renderer();
    _keyboard = new Keyboard();
    _mainScreen = new Bitmap(_renderer->width() - 10, _renderer->height() - 10, Color::colorFromRGB(255, 0, 255));
    _bottomArea = new Bitmap(_renderer->width(), 9, Color::colorFromRGB(255, 0, 255));
}

MainState::~MainState(){
    delete _renderer;
    delete _keyboard;
    delete _mainScreen;
    delete _bottomArea;
}

void MainState::process(double deltatime){

}
