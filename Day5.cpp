//
// Created by Daniel on 5/12/21.
//

#include "Day5.h"
#include "doctest.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Utility.h"

Day5Component Day5::load(const std::string &file) {
    Day5Component component{};

    std::ifstream filestream(file);
    std::string line;

    while(std::getline(filestream, line)) {
        std::vector<std::string> vectors{};
        std::vector<std::string> startVectorStr{};
        std::vector<std::string> endVectorStr{};

        Utility::split(line, " -> ", &vectors);
        Utility::split(vectors[0], ",", &startVectorStr);
        Utility::split(vectors[1], ",", &endVectorStr);

        auto vent = Vent {
            .start = {
                .x = std::stoi(startVectorStr[0]),
                .y = std::stoi(startVectorStr[1]),
            },
            .end = {
                .x = std::stoi(endVectorStr[0]),
                .y = std::stoi(endVectorStr[1]),
            }
        };

        component.vents.push_back(vent);
    }

    return component;
}

void Day5::run(Day5Component* day5Component) {
    std::vector<std::vector<unsigned int>> ventCollisons{};

    // Get maximum index
    size_t maximumIndex = 0;

    for (auto& vent : day5Component->vents) {
        if (vent.start.x > maximumIndex) {
            maximumIndex = vent.start.x;
        }

        if (vent.start.y > maximumIndex) {
            maximumIndex = vent.start.y;
        }

        if (vent.end.x > maximumIndex) {
            maximumIndex = vent.end.x;
        }

        if (vent.end.y > maximumIndex) {
            maximumIndex = vent.end.y;
        }
    }

    ventCollisons.resize(maximumIndex);

    for (auto i = 0; i <= maximumIndex; i++) {
        ventCollisons[i].resize(maximumIndex);
    }

    //int at = 0;
    for (auto& vent : day5Component->vents) {
        //std::cout << "At " << at << "\n";
        //at += 1;
        if (vent.start.x == vent.end.x || vent.start.y == vent.end.y) {
            for (size_t x = vent.start.x; x <= vent.end.x; x++) {
                for (size_t y = vent.start.y; y <= vent.end.y; y++) {
                    ventCollisons[x][y] += 1;
                }
            }
        }
    }

    day5Component->numberCrossovers = 0;

    for (auto& row : ventCollisons) {
        for (auto& cell : row) {
            if (cell > 1) {
                day5Component->numberCrossovers += 1;
            }
        }
    }
}

Orientation Vent::getOrientation(Vector2<int> p, Vector2<int> q, Vector2<int> r) {
    auto value = ((q.y - p.y) * (r.x - q.x)) - ((q.x - p.x) * (r.y - q.y));

    if (value == 0) {
        return Orientation::Collinear;
    }

    return value > 0 ? Orientation::Clockwise : Orientation::Anticlockwise;
}

bool Vent::onSegment(Vector2<int> p, Vector2<int> q, Vector2<int> r) {
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y)) {
        return true;
    }

    return false;
}

bool Vent::intersects(Vent *other) {
    auto o1 = Vent::getOrientation(this->start, this->end, other->start);
    auto o2 = Vent::getOrientation(this->start, this->end, other->end);
    auto o3 = Vent::getOrientation(other->start, other->end, this->start);
    auto o4 = Vent::getOrientation(other->start, other->end, this->end);

    if (o1 != o2 && o3 != o4) {
        return true;
    }

    if (o1 == Orientation::Collinear && Vent::onSegment(this->start, other->start, this->end)) {
        return true;
    }

    if (o2 == Orientation::Collinear && Vent::onSegment(this->start, other->end, this->end)) {
        return true;
    }

    if (o3 == Orientation::Collinear && Vent::onSegment(other->start, this->start, other->end)) {
        return true;
    }

    if (o4 == Orientation::Collinear && Vent::onSegment(other->start, this->end, other->end)) {
        return true;
    }

    return false;
}

TEST_CASE("Day 5 Test") {
    auto data = Day5::load("./Input/Day5/Test.txt");
    Day5::run(&data);

    REQUIRE(data.numberCrossovers == 5);
}