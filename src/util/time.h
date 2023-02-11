#ifndef TIME_H
#define TIME_H

#include <chrono>
#include <thread>

namespace clck {

    long getCurrentTime();
    long getCurrentTimeNS();

    void sleep(long ms);

}

#endif