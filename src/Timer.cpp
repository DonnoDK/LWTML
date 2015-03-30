#include "Timer.hpp"
#include <unistd.h>
#include <iostream>

double Timer::get_system_time(){
    gettimeofday(&_time_now, 0);
    if(_sec_base == 0){
        _sec_base = _time_now.tv_sec;
        return _time_now.tv_usec / 1000000.0f;
    }
    return (_time_now.tv_sec - _sec_base) + _time_now.tv_usec / 1000000.0f;
}

Timer::Timer(){
    _sec_base = 0;
    _old = 0;
    _now = 0;
    _delta = 0;
    _fps = 0;
}

void Timer::update(){
    _now = get_system_time();
    _delta = _now - _old;
    _old = _now;
    if(_fps > 0){
        lock_at_fps(_fps);
    }
}

double Timer::delta_time(){
    return _delta;
}

void Timer::lock_at_fps(double fps){
    double target_frame_time = 1.0f / fps;
    if(_delta < target_frame_time){
        double sleep_time = (target_frame_time - _delta) * 1000000;
        usleep(sleep_time);
        _now = get_system_time();
        _delta = _now - _old + _delta;
        _old = _now;
    }
}

Timer* Timer::locked_at_fps(double fps){
    Timer* timer = new Timer();
    if(fps > 0){
        timer->_fps = fps;
    }
    return timer;
}

