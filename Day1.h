//
// Created by Daniel on 1/12/2021.
//

#ifndef INC_2021_DAY1_H
#define INC_2021_DAY1_H

#include <vector>
#include <memory>
#include <string>

struct Day1Component {
    std::vector<int> lines;
    int numberDepthIncreases = 0;
    int numberDepthIncreasesSlidingWindow = 0;
};

namespace Day1 {
    Day1Component load(const std::string& file);
    void run(Day1Component* day1Component);
}

#endif //INC_2021_DAY1_H
