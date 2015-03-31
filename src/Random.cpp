#include "../include/Random.hpp"
#include <ctime>
#include <cstdlib>
static bool seeded = false;
static void seed_random(){
    if(seeded == false){
        seeded = true;
        srand(time(NULL));
    }
}

unsigned int Random::int_from_to(unsigned int from, unsigned int to){
    seed_random();
    return rand() % to + from;
}
