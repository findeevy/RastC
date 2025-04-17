#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}