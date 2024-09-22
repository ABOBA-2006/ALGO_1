#pragma once
#include <stdio.h>

#define PATH_A "../main_file_small_A.txt"
#define PATH_B "../temporary_file_small_B.txt"
#define PATH_C "../temporary_file_small_C.txt"

struct FILES{
    FILE *file_A;
    FILE *file_B;
    FILE *file_C;
};
