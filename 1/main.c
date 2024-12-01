#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

bool is_number(char c) {
    return '0' <= c && c <= '9';
}

void bubble_sort(int *list, int length) {
    for (int i = length - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (list[j] > list[j+1]) {
                int tmp = list[j];
                list[j] = list[j+1];
                list[j+1] = tmp;
            }
        }
    }
}

void parse_list(char *input, uint32_t input_length, int *first_column, int* second_column, uint32_t column_length) {
    int col_i = 0;

    char onestr[1024] = "";
    char twostr[1024] = "";
    short current_number = 1;
    for (int i = 0; i < input_length; i++) {
        char c = input[i];
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
}

uint32_t part1(char* input, uint32_t input_length) {
    // create column arroys
    int first_column[1000];
    int second_column[1000];

    parse_list(input, input_length, first_column, second_column, 1000);

    bubble_sort(first_column, 1000);
    bubble_sort(second_column, 1000);

    uint32_t distance = 0;
    for (int i = 0; i < 1000; i++) {
        distance += abs(first_column[i] - second_column[i]);
    }

    return distance;
}

typedef struct {
    int number;
    int count;
} pair;

int count_of_pair(pair *pairlist, uint32_t pairlist_length, int number) {
    for (int i = 0; i < pairlist_length; i++) {
        if (pairlist[i].number == number)
            return pairlist[i].count;
    }

    return 0;
}

uint32_t part2(char* input, uint32_t input_length) {
    // create column arroys
    int first_column[1000];
    int second_column[1000];

    parse_list(input, input_length, first_column, second_column, 1000);

    // NOTE: This fancy solution turns out to be slower than just two nested for loops...
    // but it looks cooler so ima keep it
    pair *pairlist = NULL;
    uint32_t pairlist_length = 0;
    for (int i = 0; i < 1000; i++) {
        if (!count_of_pair(pairlist, pairlist_length, second_column[i])) {
            // not in list yet
            pairlist_length++;
            pair *new_pairlist = malloc(pairlist_length * sizeof(pair));
            memcpy(new_pairlist, pairlist, (pairlist_length-1) * sizeof(pair));
            free(pairlist);
            pairlist = new_pairlist;

            pairlist[pairlist_length - 1].number = second_column[i];
            pairlist[pairlist_length - 1].count = 1;
        }
        else {
            for (int j = 0; j < pairlist_length; j++) {
                if (pairlist[j].number == second_column[i])
                    pairlist[j].count++;
            }
        }
    }

    uint32_t similarity = 0;
    for (int i = 0; i < 1000; i++) {
        similarity += first_column[i] * count_of_pair(pairlist, pairlist_length, first_column[i]);
    }

    free(pairlist);

    return similarity;
}

int main() {
    FILE *fptr = fopen("input.task", "r");
    char input[1000 * 1024] = "";

    uint32_t input_length = 0;
    char c;
    while ((c = fgetc(fptr)) != EOF) {
        char cstr[2] = {c, '\0'};
        strcat(input, cstr);
        input_length++;
    }

    clock_t start_clock = clock();
    uint32_t distance = part1(input, input_length);
    clock_t end_clock = clock();

    printf("\nPart 1\n");
    printf("distance: %i\n", distance);
    printf("time: %li micro seconds\n", (end_clock - start_clock) / (CLOCKS_PER_SEC / 1000000));

    printf("\nPart 2\n");
    start_clock = clock();
    uint32_t similarity = part2(input, input_length);
    end_clock = clock();

    printf("similarity: %i\n", similarity);
    printf("time: %li micro seconds\n", (end_clock - start_clock) / (CLOCKS_PER_SEC / 1000000));

    printf("\n");

    return 0;
}
