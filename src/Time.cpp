#include "Time.hpp"
#include <unistd.h>
void Time::msleep(unsigned int milliseconds){
    usleep(1000 * milliseconds);
}

Time::Timer::Timer(){
    gettimeofday(&_new_time, NULL);
    _old_time = _new_time;
}

void Time::Timer::update(){
    gettimeofday(&_new_time, NULL);
    _deltaTime = (_new_time.tv_sec - _old_time.tv_sec) * 1000.0f;
    _deltaTime += (_new_time.tv_usec - _old_time.tv_usec) / 1000.0f;
    _old_time = _new_time;
}

double Time::Timer::deltaTime() const{
    return _deltaTime;
}
