#ifndef TIMER_HPP
#define TIMER_HPP
#include <sys/time.h>
class Timer{
private:
    double get_system_time();
    struct timeval _time_now;
    int _sec_base;
    double _now;
    double _old;
    double _delta;
    double _fps;
    double _real_frame_time;
public:
    static Timer* locked_at_fps(double fps);
    Timer();
    void update();
    double delta_time();
    void lock_at_fps(double fps);
};
#endif
