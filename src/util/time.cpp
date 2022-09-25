#include "time.h"

namespace clck {

    using clock_type = std::chrono::steady_clock;

    long getCurrentTime() {
        std::chrono::time_point<clock_type> now { clock_type::now() };
        auto duration{now.time_since_epoch()};
        auto millis{std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()};
        return millis;
    }

    long getCurrentTimeNS() {
        std::chrono::time_point<clock_type> now { clock_type::now() };
        auto duration{now.time_since_epoch()};
        auto nanos{std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count()};
        return nanos;
    }

    void sleep(long ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

}