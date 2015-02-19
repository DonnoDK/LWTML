#ifndef MAINSTATE_HPP
#define MAINSTATE_HPP
#include "IState.hpp"
class MainState : public IState{
private:
    class Keyboard* _keyboard;
    class Renderer* _renderer;
    class Bitmap* _mainScreen;
    class Bitmap* _bottomArea;
public:
    MainState();
    ~MainState();
    void process(double deltatime);
};
#endif
