#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Max(int a, int b){
  if (a > b){
    return a;
  }
  return b;
}

int Min(int a, int b){
  if (a < b){
    return a;
  }
  return b;
}

