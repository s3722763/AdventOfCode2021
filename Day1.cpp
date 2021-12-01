//
// Created by Daniel on 1/12/2021.
//

#include "Day1.h"
#include <sstream>
#include <fstream>
#include "doctest.h"

Day1Component Day1::load(const std::string& file) {
    auto component = Day1Component();

    std::ifstream filestream(file);
    std::string line;

    while (std::getline(filestream, line)) {
        int number = std::stoi(line);
        component.lines.push_back(number);
    }

    return component;
}

void Day1::run(Day1Component* day1Component) {
    // Part 1
    day1Component->numberDepthIncreases = 0;

    for (int i = 1; i < day1Component->lines.size(); i++) {
         if (day1Component->lines.at(i) > day1Component->lines.at(i - 1)) {
             day1Component->numberDepthIncreases += 1;
         }
    }

    // Part 2
    day1Component->numberDepthIncreasesSlidingWindow = 0;
    int pastSum = 0;

    for (int i = 0; i < day1Component->lines.size() - 2; i++) {
        if (pastSum == 0) [[unlikely]] {
            pastSum = day1Component->lines[0] + day1Component->lines[1] + day1Component->lines[2];
        } else {
            int newSum = day1Component->lines[i] + day1Component->lines[i + 1] + day1Component->lines[i + 2];

            if (newSum > pastSum) {
                day1Component->numberDepthIncreasesSlidingWindow += 1;
            }

            pastSum = newSum;
        }
    }
}

TEST_CASE("Day 1 test") {
    auto data = Day1::load("./Input/Day1/Test.txt");
    Day1::run(&data);

    REQUIRE(data.numberDepthIncreases == 7);
    REQUIRE(data.numberDepthIncreasesSlidingWindow == 5);
}