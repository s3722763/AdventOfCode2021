//
// Created by Daniel on 5/12/21.
//

#ifndef INC_2021_DAY4_H
#define INC_2021_DAY4_H

#include <array>
#include <vector>

struct BingoBoard {
    std::vector<std::vector<int>>boardNumbers;
    std::vector<std::vector<bool>> boardNumberCalled;
};

struct Day4Component {
    std::vector<int> numbersCalled;
    std::vector<BingoBoard> bingoBoards;
    int part1Score = 0;
    int part2Score = 0;
};

namespace Day4 {
    Day4Component load(const std::string& file);
    bool CheckBoard(BingoBoard* bingoBoard);
    void printBoard(BingoBoard* bingoBoard);
    void run(Day4Component* day4Component);
}

#endif //INC_2021_DAY4_H
