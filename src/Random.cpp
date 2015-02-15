#include "Random.hpp"
#include <ctime>
#include <cstdlib>
static bool seeded = false;
static void seedRandom(){
    if(seeded == false){
        seeded = true;
        srand(time(NULL));
    }
}

unsigned int Random::intFromTo(unsigned int from, unsigned int to){
    seedRandom();
    return rand() % to + from;
}
