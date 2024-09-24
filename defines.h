#pragma once
#include <stdio.h>

#define PATH_A "../main_file_small_A.txt"
#define PATH_A2 "../half_sorted_file_A.txt"
#define PATH_B "../temporary_file_small_B.txt"
#define PATH_C "../temporary_file_small_C.txt"

#define AMOUNT_OF_INTS 16000000 // equivalent to ~100 mb of int numbers

struct FILES{
    FILE *file_A;
    FILE *file_A2;
    FILE *file_B;
    FILE *file_C;
};
