#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_number(char c) {
    return '0' <= c && c <= '9';
}

void bubble_sort(int *list) {
    for (int i = 1000 - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (list[j] > list[j+1]) {
                int tmp = list[j];
                list[j] = list[j+1];
                list[j+1] = tmp;
            }
        }
    }
}

int main() {
    FILE *fptr = fopen("input.task", "r");

    // create column arroys
    int col_i = 0;
    int first_column[1000];
    int second_column[1000];
    for (int i = 0; i < 1000; i++) {
        first_column[i] = -1;
        second_column[i] = -1;
    }

    char c;

    char onestr[1024] = "";
    char twostr[1024] = "";
    short current_number = 1;
    while ((c = fgetc(fptr)) != EOF) {
        char cstr[2] = {c, '\0'};

        if (is_number(c)) {
            // we have a number, append it to one of the two number strings
            switch (current_number) {
                case 1:
                    strcat(onestr, cstr);
                    break;
                case 2:
                    strcat(twostr, cstr);
                    break;
            }
        }
        else if (c == '\n') {
            // end of line
            // safe numbers
            first_column[col_i]  = atoi(onestr);
            second_column[col_i] = atoi(twostr);
            col_i++;

            // reset
            strcpy(onestr, "");
            strcpy(twostr, "");
            current_number = 1;
        }
        else {
            current_number = 2;
        }
    }

    // sort lists to align the smallest and the biggest numbers
    bubble_sort(first_column);
    bubble_sort(second_column);

    // calculate distance
    int distance = 0;
    for (int i = 0; i < 1000; i++) {
        distance += abs(first_column[i] - second_column[i]);
    }

    printf("distance: %i\n", distance);

    return 0;
}
