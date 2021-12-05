//
// Created by Daniel on 3/12/21.
//

#ifndef INC_2021_DAY3_H
#define INC_2021_DAY3_H

#include <string>
#include <vector>

//constexpr unsigned int DAY_3_NUMBER_SIZE = 12;

struct Day3Component {
    std::vector<std::string> numbers;
    size_t numberSizeBits = 0;
    unsigned int gamma = 0;
    unsigned int epsilon = 0;
    unsigned int oxygenRating = 0;
    unsigned int co2Rating = 0;
};

namespace Day3 {
    Day3Component load(const std::string& file);
    void run(Day3Component* day3Component);
}

#endif //INC_2021_DAY3_H
