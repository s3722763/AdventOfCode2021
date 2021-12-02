//
// Created by Daniel on 2/12/2021.
//

#include "Day2.h"
#include <fstream>
#include "doctest.h"

Day2Component Day2::load(const std::string &file) {
    Day2Component component{};

    std::ifstream filestream(file);
    std::string line;

    while (std::getline(filestream, line)) {
        auto breakPosition = line.find(' ');

        auto action = line.substr(0, breakPosition);
        auto amountStr = line.substr(breakPosition + 1, line.size());
        int amount = std::stoi(amountStr);

        Movement movement{};
        movement.amount = amount;

        if (action == "forward") {
            movement.direction = Direction::Forward;
        } else if (action == "down") {
            movement.direction = Direction::Down;
        } else {
            // Assume up
            movement.direction = Direction::Up;
        }

        component.movements.push_back(movement);
    }

    return component;
}

void Day2::run(Day2Component* day2Component) {
    day2Component->depthPart1 = 0;
    day2Component->depthPart2 = 0;
    day2Component->horizontalPositionPart1 = 0;
    day2Component->horizontalPositionPart2 = 0;
    day2Component->aim = 0;

    for (auto& movement : day2Component->movements) {
        if (movement.direction == Direction::Forward) {
            // Part 1
            day2Component->horizontalPositionPart1 += movement.amount;
            // Part 2
            day2Component->horizontalPositionPart2 += movement.amount;
            day2Component->depthPart2 += day2Component->aim * movement.amount;
        } else if (movement.direction == Direction::Down) {
            // Part 1
            day2Component->depthPart1 += movement.amount;
            // Part 2
            day2Component->aim += movement.amount;
        } else {
            // Assume up
            // Part 1
            day2Component->depthPart1 -= movement.amount;
            // Part 2
            day2Component->aim -= movement.amount;
        }
    }
}

TEST_CASE("Day 2 test") {
    auto data = Day2::load("./Input/Day2/Test.txt");
    Day2::run(&data);

    REQUIRE(data.depthPart1 == 10);
    REQUIRE(data.horizontalPositionPart1 == 15);
    REQUIRE(data.depthPart2 == 60);
    REQUIRE(data.horizontalPositionPart2 == 15);
}
