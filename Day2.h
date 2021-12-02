//
// Created by Daniel on 2/12/2021.
//

#ifndef INC_2021_DAY2_H
#define INC_2021_DAY2_H

#include <vector>
#include <string>

enum Direction {
    Forward,
    Down,
    Up
};

struct Movement {
    Direction direction;
    int amount;
};

struct Day2Component {
    std::vector<Movement> movements;
    int horizontalPositionPart1 = 0;
    int depthPart1 = 0;
    int horizontalPositionPart2 = 0;
    int depthPart2 = 0;
    int aim = 0;
};

namespace Day2 {
    Day2Component load(const std::string& file);
    void run(Day2Component* day2Component);
}

#endif //INC_2021_DAY2_H
