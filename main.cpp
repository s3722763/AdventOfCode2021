#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Day1.h"

int run_tests();

int main(int argc, char** argv) {
    if (argc > 1) {
        for (auto i = 1; i < argc; i++) {
            if (std::strcmp(argv[i], "TEST") == 0) {
                return run_tests();
            }
        }
    }

    // Day 1
    auto day1Data = Day1::load("Input/Day1/Problem.txt");
    Day1::run(&day1Data);
    std::cout << "Day 1 Part 1 Solution: " << day1Data.numberDepthIncreases << "\n";
    std::cout << "Day 1 Part 2 Solution: " << day1Data.numberDepthIncreasesSlidingWindow << "\n";
    std::cout << std::endl;

    return 0;
}

int run_tests() {
    doctest::Context context;

    return context.run();
}
