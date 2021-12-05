//
// Created by Daniel on 3/12/21.
//

#include <fstream>
#include <array>
#include "Day3.h"
#include "doctest.h"
#include <cmath>
#include <iostream>

Day3Component Day3::load(const std::string &file) {
    auto component = Day3Component();

    std::ifstream filestream(file);
    std::string line;

    while (std::getline(filestream, line)) {
        component.numbers.push_back(line);
        component.numberSizeBits = line.size();
    }

    return component;
}

void Day3::run(Day3Component* day3Component) {
    // Part 1
    std::vector<unsigned int> count{};
    count.resize(day3Component->numberSizeBits);

    for (auto i = 0; i < day3Component->numberSizeBits; i++) {
        for (auto& column : day3Component->numbers) {
            if (column.at(i) == '1') {
                count[i] += 1;
            }
        }
    }

    auto half = day3Component->numbers.size() / 2;
    day3Component->gamma = 0;
    unsigned int power =  day3Component->numberSizeBits - 1;

    std::for_each(count.begin(),  count.end(), [&](auto number) {
        //std::cout << number << std::endl;
        if (number > half) {
            day3Component->gamma += static_cast<unsigned int>(std::pow(2, power));
        }

        power -= 1;
    });

    unsigned int andWith = 0;
    for (auto i = 0; i < day3Component->numberSizeBits; i++) {
        andWith |= 1 << i;
    }

    day3Component->epsilon = (~day3Component->gamma) & andWith;

    // Part 2
    //std::reverse(count.begin(), count.end());
    auto oxygenCount = count;
    auto oxygenNumbers = day3Component->numbers;
    //std::reverse(oxygenNumbers.begin(), oxygenNumbers.end());

    for (auto i = 0; i < day3Component->numberSizeBits; i++) {
        auto columnCount = 0;

        for (auto& column : oxygenNumbers) {
            if (column.at(i) == '1') {
                columnCount += 1;
            }
        }

        //std::cout << columnCount << " - " << oxygenNumbers.size() << " - half: " << half << std::endl;
        if (columnCount >= (oxygenNumbers.size() - columnCount)) {
            for (auto number = oxygenNumbers.begin(); number != oxygenNumbers.end();) {
                if (number->at(i) == '0') {
                    number = oxygenNumbers.erase(number);
                } else {
                    //std::cout << "Keeping number " << *number << " - is one at index " << i << std::endl;
                    number++;
                }
            }
        } else {
            for (auto number = oxygenNumbers.begin(); number != oxygenNumbers.end();) {
                if (number->at(i) == '1') {
                    number = oxygenNumbers.erase(number);
                } else {
                    //std::cout << "Keeping number " << *number << " - is zero at index " << i << std::endl;
                    number++;
                }
            }
        }

        if (oxygenNumbers.size() <= 1) {
            //std::cout << "Found: " << oxygenNumbers[0] << std::endl;
            break;
        }

        //std::cout << std::endl;
    }

    auto co2Numbers = day3Component->numbers;

    for (auto i = 0; i < day3Component->numberSizeBits; i++) {
        auto columnCount = 0;

        for (auto& column : co2Numbers) {
            if (column.at(i) == '1') {
                columnCount += 1;
            }
        }

        //half = co2Numbers.size() / 2;
        //std::cout << columnCount << " - " << oxygenNumbers.size() << " - half: " << half << std::endl;
        if (columnCount < (co2Numbers.size() - columnCount)) {
            for (auto number = co2Numbers.begin(); number != co2Numbers.end();) {
                if (number->at(i) == '0') {
                    number = co2Numbers.erase(number);
                } else {
                    //std::cout << "Keeping number " << *number << " - is one at index " << i << std::endl;
                    number++;
                }
            }
        } else {
            for (auto number = co2Numbers.begin(); number != co2Numbers.end();) {
                if (number->at(i) == '1') {
                    number = co2Numbers.erase(number);
                } else {
                    //std::cout << "Keeping number " << *number << " - is zero at index " << i << std::endl;
                    number++;
                }
            }
        }

        if (co2Numbers.size() <= 1) {
            //std::cout << "Found: " << co2Numbers[0] << std::endl;
            break;
        }

        //std::cout << std::endl;
    }

    day3Component->co2Rating = 0;
    day3Component->oxygenRating = 0;

    power = day3Component->numberSizeBits - 1;
    auto* numberString = &oxygenNumbers.at(0);

    std::for_each(numberString->begin(),numberString->end(), [&](auto number) {
        //std::cout << number << std::endl;
        if (number == '1') {
            day3Component->oxygenRating += static_cast<unsigned int>(std::pow(2, power));
        }

        power -= 1;
    });

    power = day3Component->numberSizeBits - 1;
    numberString = &co2Numbers.at(0);

    std::for_each(numberString->begin(),  numberString->end(), [&](auto number) {
        //std::cout << number << std::endl;
        if (number == '1') {
            day3Component->co2Rating += static_cast<unsigned int>(std::pow(2, power));
        }

        power -= 1;
    });
}

TEST_CASE("Day 3 test") {
    auto data = Day3::load("./Input/Day3/Test.txt");
    Day3::run(&data);

    REQUIRE(data.gamma == 22);
    REQUIRE(data.epsilon == 9);
    REQUIRE(data.oxygenRating == 23);
    REQUIRE(data.co2Rating == 10);
}