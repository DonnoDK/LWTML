#include "Time.hpp"
#include <unistd.h>
void Time::msleep(unsigned int milliseconds){
    usleep(1000 * milliseconds);
}
