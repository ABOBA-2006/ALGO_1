#pragma once
#include <stdbool.h>

#include "defines.h"

void splitData(struct FILES *files, int subArrayLength, bool isBFile);

void mergeData(struct FILES *files,  int subArrayLength);