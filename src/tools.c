#include "tools.h"

void Tswap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}