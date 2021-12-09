#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"

int run_tests(int argc, char** argv);

int main(int argc, char** argv) {
    if (argc > 1) {
        for (auto i = 1; i < argc; i++) {
            if (std::strcmp(argv[i], "TEST") == 0) {
                return run_tests(argc, argv);
            }
        }
    }

    // Day 1
    auto day1Data = Day1::load("Input/Day1/Problem.txt");
    Day1::run(&day1Data);
    std::cout << "Day 1 Part 1 Solution: " << day1Data.numberDepthIncreases << "\n";
    std::cout << "Day 1 Part 2 Solution: " << day1Data.numberDepthIncreasesSlidingWindow << "\n";
    std::cout << std::endl;

    // Day 2
    auto day2Data = Day2::load("Input/Day2/Problem.txt");
    Day2::run(&day2Data);
    std::cout << "Day 2 Part 1 Solution: " << day2Data.horizontalPositionPart1 * day2Data.depthPart1 << "\n";
    std::cout << "Day 2 Part 2 Solution: " << day2Data.horizontalPositionPart2 * day2Data.depthPart2 << "\n";
    std::cout << std::endl;

    auto day3Data = Day3::load("Input/Day3/Problem.txt");
    Day3::run(&day3Data);
    std::cout << "Day 3 Part 1 Solution: " << day3Data.epsilon * day3Data.gamma << "\n";
    std::cout << "Day 3 Part 2 Solution: " << day3Data.co2Rating * day3Data.oxygenRating << "\n";
    std::cout << std::endl;

    auto day4Data = Day4::load("Input/Day4/Problem.txt");
    Day4::run(&day4Data);
    std::cout << "Day 4 Part 1 Solution: " << day4Data.part1Score << "\n";
    std::cout << "Day 4 Part 2 Solution: " << day4Data.part2Score << "\n";
    std::cout << std::endl;

    auto day5Data = Day5::load("Input/Day5/Problem.txt");
    Day5::run(&day5Data);
    std::cout << "Day 5 Part 1 Solution: " << day5Data.numberCrossovers << "\n";
    //std::cout << "Day 5 Part 2 Solution: " << day4Data.part2Score << "\n";
    std::cout << std::endl;

    return 0;
}

int run_tests(int argc, char** argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);

    return context.run();
}
