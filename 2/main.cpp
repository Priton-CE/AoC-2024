#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

uint32_t task1(std::string input) {
    std::vector<std::vector<uint16_t>> matrix;
    matrix.reserve(1001);
    matrix.push_back(std::vector<uint16_t>());

    // convert file to a matrix
    std::string number;
    for (char c : input) {
        if ('0' <= c && c <= '9') {
            number += c;
        }
        else {
            if (!number.empty()) {
                matrix.at(matrix.size() - 1).push_back(std::stoi(number));
                number.clear();
            }

            if (c == '\n') {
                matrix.push_back(std::vector<uint16_t>());
            }
        }
    }
    matrix.pop_back();

    uint32_t safe_count = 0;

    // per line
    for (std::vector<uint16_t> line : matrix) {
        uint8_t direction = 0;
        bool unsafe = false;

        // check for upgoing or downgoing and for difference
        for (int i = 0; i < line.size() - 1; i++) {
            // validate that we are going in the last direction
            // otherwise break
            if ((direction == 1 || direction == 0) && line.at(i) < line.at(i + 1)) {
                if (direction == 0) direction = 1;
            }
            else if ((direction == 2 || direction == 0) && line.at(i) > line.at(i + 1)) {
                if (direction == 0) direction = 2;
            }
            else {
                unsafe = true;
                break;
            }

            uint16_t diff = std::abs(line.at(i) - line.at(i + 1));
            if (diff > 3 || diff == 0) {
                unsafe = true;
                break;
            }
        }

        if (!unsafe)
            safe_count++;
    }

    return safe_count;
}

uint32_t task2(std::string input) {
    std::vector<std::vector<uint16_t>> matrix;
    matrix.reserve(1001);
    matrix.push_back(std::vector<uint16_t>());

    // convert file to a matrix
    std::string number;
    for (char c : input) {
        if ('0' <= c && c <= '9') {
            number += c;
        }
        else {
            if (!number.empty()) {
                matrix.at(matrix.size() - 1).push_back(std::stoi(number));
                number.clear();
            }

            if (c == '\n') {
                matrix.push_back(std::vector<uint16_t>());
            }
        }
    }
    matrix.pop_back();

    uint32_t safe_count = 0;

    // per line
    for (std::vector<uint16_t> line : matrix) {
        bool unsafe = false;
        bool dampener_used = false;

        // check which direction the line is going
        uint8_t rightbigger = 0;
        uint8_t leftbigger = 0;
        for (int i = 0; i < line.size() - 1; i++) {
            if (line.at(i) < line.at(i + 1))
                rightbigger++;
            else if (line.at(i) > line.at(i + 1))
                leftbigger++;
        }

        uint8_t direction = 0;
        if (rightbigger > leftbigger)
            direction = 1;
        else
            direction = 2;

        // for up to two times go through the line and remove up to one element
        bool redo = true;
        while (redo) {
            redo = false;
            // check for upgoing or downgoing and for difference
            for (int i = 0; i < line.size() - 1; i++) {
                // validate that we are going in the last direction
                // otherwise break
                if (direction == 1 && line.at(i) < line.at(i + 1)) {
                }
                else if (direction == 2 && line.at(i) > line.at(i + 1)) {
                }
                else {
                    if (!dampener_used) {
                        // we have not removed an element yet so remove it and redo the line
                        dampener_used = true;
                        redo = true;
                        line.erase(line.begin() + i);
                        break;
                    }
                    else {
                        unsafe = true;
                        break;
                    }
                }
            }
        }

        // the line is properly growing or shrinking. Now check how rapid changes are
        for (int i = 0; i < line.size() - 1; i++) {
            uint16_t diff = std::abs(line.at(i) - line.at(i + 1));
            if (diff > 3 || diff == 0) {
                if (!dampener_used) {
                    dampener_used = true;
                    continue;
                }
                else {
                    unsafe = true;
                    break;
                }
            }
        }

        // if line is safe note that
        if (!unsafe)
            safe_count++;
    }

    return safe_count;
}

int main() {
    std::ifstream file("input.task");

    std::stringstream strStream;
    strStream << file.rdbuf();
    std::string input = strStream.str();

    clock_t clock_start = clock();
    uint32_t num = task1(input);
    clock_t clock_end = clock();

    printf("safe count: %i\n", num);
    printf("time: %li micro seconds\n\n", clock_end - clock_start / (CLOCKS_PER_SEC / 1000000));

    clock_start = clock();
    num = task2(input);
    clock_end = clock();

    printf("safe count with dampener: %i\n", num);
    printf("time: %li micro seconds\n\n", clock_end - clock_start / (CLOCKS_PER_SEC / 1000000));


    return 0;
}
