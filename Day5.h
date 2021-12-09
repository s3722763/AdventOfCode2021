//
// Created by Daniel on 5/12/21.
//

#ifndef INC_2021_DAY5_H
#define INC_2021_DAY5_H

#include <vector>

enum Orientation {
    Collinear,
    Clockwise,
    Anticlockwise
};

template<typename T>
struct Vector2 {
    T x;
    T y;
};

struct Vent {
    Vector2<int> start;
    Vector2<int> end;

    bool intersects(Vent* other);

private:
    Orientation getOrientation(Vector2<int> p, Vector2<int> q, Vector2<int> r);
    bool onSegment(Vector2<int> p, Vector2<int> q, Vector2<int> r);
};

struct Day5Component {
    std::vector<Vent> vents;
    unsigned int numberCrossovers = 0;
};

namespace Day5 {
    Day5Component load(const std::string& file);
    void run(Day5Component* day5Component);
}

#endif //INC_2021_DAY5_H
