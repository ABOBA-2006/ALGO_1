#pragma once
#include <stdbool.h>

#include "defines.h"


bool isFileEmpty(FILE *file);

void splitData(struct FILES *files, int subArrayLength, bool isBFile);

void mergeData(struct FILES *files,  int subArrayLength);

void extendedSort(struct FILES *files, int subArrayLength);
