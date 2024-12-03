#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define JUMP_LENGTH_TASK1 8
#define JUMP_LENGTH_TASK2_MUL 8
#define JUMP_LENGTH_TASK2_TOG 4

bool is_number(char c) {
    return '0' <= c && c <= '9';
}

int verify_and_extract_mul(std::string &input, int framestart, std::string &number_one, std::string &number_two) {
    int fail_at = -1;
    bool at_number_two = false;
    for (int j = framestart; j < input.length(); j++) {
        char fc = input.at(j);

        // check sequences
        if (fc == 'm' && j - framestart == 0) continue;
        if (fc == 'u' && j - framestart == 1) continue;
        if (fc == 'l' && j - framestart == 2) continue;
        if (fc == '(' && j - framestart == 3) continue;
        if (fc == ',' && j - framestart - number_one.length() == 4) { at_number_two = true; continue; }
        if (fc == ')' && j - framestart - number_one.length() - number_two.length() == 5 && number_one.length() > 0 && number_two.length() > 0) {
            // we have made it to the end of the expected instruction and both numbers exist
            // fail_at will be -1
            break;
        }
        if (is_number(fc)) {
            // we encountered one of the expected numbers
            // determine their length
            if (at_number_two) {
                number_two += fc;
            }
            else {
                number_one += fc;
            }

            continue;
        }

        // none of the checks hit so we had a miss
        // terminte this operation and return to the loop
        fail_at = j;
        break;
    }

    return fail_at;
}

uint32_t task1(std::string input) {
    uint32_t sum = 0;

    for (int i = 0; i < input.length(); i++) {
        char c = input.at(i);

        int framestart = -1;
        if (is_number(c)) {
            // walk back and check if we encounter one of the expected characters
            // that come before a number ('(' and ',')
            for (int j = i; j > 4; j--) { // safe guard us by staying above 4, which is the minimum length of the instruction half before a number
                char v = input.at(j);
                if (!is_number(v)) {
                    if (v == '(') {
                        // the char before the numbers is a bracket
                        // check if before the bracket we can find a valid instruction
                        framestart = j - 3;
                    }
                    else if (v == ',') {
                        // the char before the numbers is a comma
                        // before this should be another number so set i to j - 1 and run this whole check again on the new number
                        i = j - 1 - JUMP_LENGTH_TASK1 - 1; // keep in mind we will increment i at the end of the loop and and another few because of a missed frame
                    }
                    break;
                }
            }
        }
        else if (c == 'm') {
            // we found the potential beginning of an instruction
            // set the framestart to the current position
            framestart = i;
        }
        else if (c == 'u') {
            // we found the potential beginning of an instruction
            // set the framestart to the expected start position
            framestart = i - 1;
        }
        else if (c == 'l') {
            // we found the potential beginning of an instruction
            // set the framestart to the expected start position
            framestart = i - 2;
        }
        else if (c == '(') {
            // we found the potential beginning of an instruction
            // set the framestart to the expected start position
            framestart = i - 3;
        }
        else if (c == ',') {
            // we found the potential middle of an instruction
            // we dont know how far back the beginning might be so go back one char and try again
            i -= 2; // at the end of this loop we will increment i by 1
            continue;
        }
        else if (c == ')') {
            // we found the potential middle of an instruction
            // we dont know how far back the beginning might be so go back one char and try again
            i -= 2; // at the end of this loop we will increment i by 1
            continue;
        }

        if (framestart < 0) {
            i += JUMP_LENGTH_TASK1 - 1; // keep in mind at the end we increment by one
            continue;
        }

        // we have detected a (valid) frame start
        // verify it
        std::string number_one;
        std::string number_two;
        int fail_at = verify_and_extract_mul(input, framestart, number_one, number_two);

        if (fail_at >= 0) {
            i = std::max(i, fail_at) + JUMP_LENGTH_TASK1 + 1 - 1; // keep in mind at the end we increment by one
            continue;
        }

        // we have a valid instruction and the numbers have been extracted
        // parse and calculate
        int one = std::stoi(number_one);
        int two = std::stoi(number_two);

        sum += one * two;

        // skip one char behind this frame and account for next loop increasing by one
        i = JUMP_LENGTH_TASK1 + framestart + 6 + number_one.length() + number_two.length() + 1 - 1;
    }

    return sum;
}

uint32_t task2(std::string input) {
    uint32_t sum = 0;

    bool mult_enabled = true;
    int last_toggle_pos = 0;

    for (int i = 0; i < input.length(); i++) {
        char c = input.at(i);

        int framestart = -1;
        if (is_number(c)) {
            // walk back and check if we encounter one of the expected characters
            // that come before a number ('(' and ',')
            for (int j = i; j > 4; j--) { // safe guard us by staying above 4, which is the minimum length of the instruction half before a number
                char v = input.at(j);
                if (!is_number(v)) {
                    if (v == '(') {
                        // the char before the numbers is a bracket
                        // check if before the bracket we can find a valid instruction
                        framestart = j - 3;
                    }
                    else if (v == ',') {
                        // the char before the numbers is a comma
                        // before this should be another number so set i to j - 1 and run this whole check again on the new number
                        i = j - 1 - JUMP_LENGTH_TASK1 - 1; // keep in mind we will increment i at the end of the loop and and another few because of a missed frame
                    }
                    break;
                }
            }
        }
        else if (c == 'm') {
            // we found the potential beginning of an instruction
            // set the framestart to the current position
            framestart = i;
        }
        else if (c == 'u') {
            // we found the potential beginning of an instruction
            // set the framestart to the expected start position
            framestart = i - 1;
        }
        else if (c == 'l') {
            // we found the potential beginning of an instruction
            // set the framestart to the expected start position
            framestart = i - 2;
        }
        else if (c == '(') {
            // we found the potential beginning of an instruction
            // set the framestart to the expected start position
            framestart = i - 3;
        }
        else if (c == ',') {
            // we found the potential middle of an instruction
            // we dont know how far back the beginning might be so go back one char and try again
            i -= 2; // at the end of this loop we will increment i by 1
            continue;
        }
        else if (c == ')') {
            // we found the potential middle of an instruction
            // we dont know how far back the beginning might be so go back one char and try again
            i -= 2; // at the end of this loop we will increment i by 1
            continue;
        }

        if (framestart < 0) {
            i += JUMP_LENGTH_TASK1 - 1; // keep in mind at the end we increment by one
            continue;
        }

        // we have detected a (valid) frame start
        // verify it
        std::string number_one;
        std::string number_two;
        int fail_at = verify_and_extract_mul(input, framestart, number_one, number_two);

        if (fail_at >= 0) {
            i = std::max(i, fail_at) + JUMP_LENGTH_TASK1 + 1 - 1; // keep in mind at the end we increment by one
            continue;
        }

        // we have a valid instruction and the numbers have been extracted
        int first_do = input.find("do()", last_toggle_pos);
        int first_dont = input.find("don't()", last_toggle_pos);

        if (first_do > i) first_do = -1;
        if (first_dont > i) first_dont = -1;

        if (first_do > first_dont) {
            mult_enabled = true;
            last_toggle_pos = first_do + 1;
        }
        else if (first_dont > first_do) {
            mult_enabled = false;
            last_toggle_pos = first_dont + 1;
        }

        if (mult_enabled) {
            // parse and calculate
            int one = std::stoi(number_one);
            int two = std::stoi(number_two);

            sum += one * two;
        }

        // skip one char behind this frame and account for next loop increasing by one
        i = JUMP_LENGTH_TASK1 + framestart + 6 + number_one.length() + number_two.length() + 1 - 1;
    }

    return sum;
}

int main() {
    std::ifstream file("input.task");

    std::stringstream strStream;
    strStream << file.rdbuf();
    std::string input = strStream.str();

    clock_t clock_start = clock();
    uint32_t num = task1(input);
    clock_t clock_end = clock();

    printf("sum: %i\n", num);
    printf("time: %li micro seconds\n\n", clock_end - clock_start / (CLOCKS_PER_SEC / 1000000));

    clock_start = clock();
    num = task2(input);
    clock_end = clock();

    printf("toggled sum: %i\n", num);
    printf("time: %li micro seconds\n\n", clock_end - clock_start / (CLOCKS_PER_SEC / 1000000));


    return 0;
}
