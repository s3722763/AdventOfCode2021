//
// Created by Daniel on 5/12/21.
//

#include "Utility.h"

void Utility::split(std::string line, const std::string& delimiter, std::vector<std::string>* result) {
    result->clear();

    std::string token;
    auto index = 0;

    while((index = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, index);

        result->push_back(token);

        line.erase(0, index + delimiter.length());
    }

    result->push_back(line);
}
