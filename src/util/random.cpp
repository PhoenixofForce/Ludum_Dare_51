#include "random.h"

namespace rnd {

    float random() {
        static const int max_rand = 1'000'000'000;

        static std::mt19937 mt{
            (unsigned int) std::chrono::steady_clock::now().time_since_epoch().count()
        };
        static std::uniform_int_distribution die{0, max_rand};

        int random = die(mt);

        return (float) random / max_rand;
    }
    
    float random(float lower, float upper) {
        return random() * (upper - lower) + lower;
    }

    int random(int lower, int upper) {
        return (int) random((float) lower, (float) upper);
    }

}
