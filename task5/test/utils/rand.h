//
// Created by xac1k on 4/12/26.
//

#ifndef TASK5_RAND_H
#define TASK5_RAND_H
#include <random>
#include <chrono>

class Random {
private:
    static std::mt19937& getEngine() {
        static std::mt19937 engine(std::chrono::steady_clock::now().time_since_epoch().count());
        return engine;
    }

public:
    static double getDouble(double min = 0.0, double max = 1.0) {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(getEngine());
    }

    static int getInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(getEngine());
    }

    static bool getBool(double probability = 0.5) {
        return getDouble() < probability;
    }
};

inline double randFloat() {
    return Random::getDouble();
}
#endif //TASK5_RAND_H