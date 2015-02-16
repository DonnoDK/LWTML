#ifndef TIME_HPP
#define TIME_HPP
#include <sys/time.h>
namespace Time{
    void msleep(unsigned int milliseconds);
    class Timer{
    private:
        struct timeval _old_time;
        struct timeval _new_time;
        double _deltaTime;
    public:
        Timer();
        void update();
        double deltaTime() const;
    };
};
#endif
