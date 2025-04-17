#ifndef TOOL_H
#define TOOL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector3i{
  int x;
  int y;
  int z;
} Vector3i;

typedef struct Vector3f{
  float x;
  float y;
  float z;
} Vector3f;

typedef struct Model{
  Vector3f* verts;
  Vector3i* faces;
} Model;

Vector3f NewVector3f(float x, float y, float z);

Vector3i NewVector3i(int x, int y, int z);

Model NewModel();

Model ReadOBJ(const char* file);

void Swap(int* a, int* b);

#endif