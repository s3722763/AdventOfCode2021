//
// Created by Daniel on 5/12/21.
//

#include "Day4.h"
#include "doctest.h"
#include <fstream>
#include <string>
#include <iostream>

Day4Component Day4::load(const std::string &file) {
    Day4Component component{};

    std::ifstream filestream(file);
    std::string line;

    // First line is the numbers
    std::getline(filestream, line);

    size_t index = 0;
    std::string delimiter = ",";
    std::string token;

    while((index = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, index);

        int number = std::stoi(token);
        component.numbersCalled.push_back(number);

        line.erase(0, index + delimiter.length());
    }

    int number = std::stoi(line);
    component.numbersCalled.push_back(number);

    //std::reverse(component.numbersCalled.begin(), component.numbersCalled.end());
    // Read next empty line
    std::getline(filestream, line);

    BingoBoard bingoBoard{};

    bingoBoard.boardNumbers.resize(5);
    bingoBoard.boardNumberCalled.resize(5);
    for (auto i = 0; i < 5; i++) {
        bingoBoard.boardNumbers[i].resize(5);
        bingoBoard.boardNumberCalled[i].resize(5);
    }

    size_t row = 0;

    while (std::getline(filestream, line)) {
        if (line.empty()) [[unlikely]] {
            component.bingoBoards.push_back(bingoBoard);
            bingoBoard = BingoBoard{};
            bingoBoard.boardNumbers.resize(5);
            bingoBoard.boardNumberCalled.resize(5);
            for (auto i = 0; i < 5; i++) {
                bingoBoard.boardNumbers[i].resize(5);
                bingoBoard.boardNumberCalled[i].resize(5);
            }

            row = 0;
        } else {
            index = 0;
            size_t column = 0;
            delimiter = " ";

            while((index = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, index);

                if (!token.empty()) [[likely]] {
                    int number = std::stoi(token);
                    bingoBoard.boardNumbers[row][column] = number;
                    column += 1;

                    //line.erase(0, index + delimiter.length());
                }

                line.erase(0, index + delimiter.length());
            }

            int number = std::stoi(line);
            bingoBoard.boardNumbers[row][column] = number;

            row += 1;
        }
    }

    // Add last bingo board
    component.bingoBoards.push_back(bingoBoard);

    return component;
}

void Day4::run(Day4Component* day4Component) {
    auto round = 1;
    size_t winnerIndex = -1;
    size_t numberOnWinning = 0;

    for (int calledNumber : day4Component->numbersCalled) {
        //std::cout << "Starting round " << round << " with number " << calledNumber << std::endl;
        round += 1;
        size_t index = 0;

        for(auto board = day4Component->bingoBoards.begin(); board != day4Component->bingoBoards.end();) {
            for (auto row = 0; row < 5; row++) {
                for (auto column = 0; column < 5; column++) {
                    if (board->boardNumbers[row][column] == calledNumber) {
                        board->boardNumberCalled[row][column] = true;
                    }
                }
            }

            if (Day4::CheckBoard(&*board)) {
                int markedSum = 0;

                for (auto i = 0; i < 5; i++) {
                    for (auto j = 0; j < 5; j++) {
                        if (!board->boardNumberCalled[i][j]) {
                            //std::cout << winningBoard->boardNumbers[i][j] << ",";
                            markedSum += board->boardNumbers[i][j];
                        }
                    }
                }

                //std::cout << std::endl;
                if (day4Component->part1Score == 0) {
                    day4Component->part1Score = markedSum * calledNumber;
                } else if (day4Component->bingoBoards.size() == 1) {
                    day4Component->part2Score = markedSum * calledNumber;
                }

                board = day4Component->bingoBoards.erase(board);
                //day4Component->boardNumberCalled.erase(board->boardNumberCalled.begin() + index);
            } else {
                index += 1;
                board++;
            }
        }

        int i = 1;
        /*for (auto& board : day4Component->bingoBoards) {
            std::cout << "Board " << i << std::endl;
            i += 1;
            Day4::printBoard(&board);
        }

        std::cout << std::endl;*/
    }
}

bool Day4::CheckBoard(BingoBoard* bingoBoard) {
    // Check rows
    for (auto row = 0; row < 5; row++) {
        unsigned int numberTrue = 0;

        for (auto column = 0; column < 5; column++) {
            if (bingoBoard->boardNumberCalled[row][column]) {
                numberTrue += 1;
            } else {
                break;
            }
        }

        if (numberTrue == 5) {
            return true;
        }
    }

    // Check columns
    for (auto column = 0; column < 5; column++) {
        unsigned int numberTrue = 0;

        for (auto row = 0; row < 5; row++) {
            if (bingoBoard->boardNumberCalled[row][column]) {
                numberTrue += 1;
            } else {
                break;
            }
        }

        if (numberTrue == 5) {
            return true;
        }
    }

    return false;
}

void Day4::printBoard(BingoBoard* bingoBoard) {
    std::cout << "----------" << std::endl;
    for (auto i = 0; i < 5; i++) {
        for (auto j = 0; j < 5; j++) {
            auto number = bingoBoard->boardNumbers[i][j];
            if (number < 10) {
                std::cout << " ";
            }

            std::cout << bingoBoard->boardNumbers[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (auto i = 0; i < 5; i++) {
        for (auto j = 0; j < 5; j++) {
            std::cout << (bingoBoard->boardNumberCalled[i][j] ? "o" : "-") << " ";
        }

        std::cout << std::endl;
    }

    std::cout << "----------" << std::endl;
    std::cout << std::endl;
}

TEST_CASE("Day 4 test") {
    auto data = Day4::load("./Input/Day4/Test.txt");
    Day4::run(&data);

    REQUIRE(data.part1Score == 4512);
    REQUIRE(data.part2Score == 1924);
}