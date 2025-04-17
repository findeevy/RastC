#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector3f NewVector3f(float x, float y, float z){
  Vector3f vector3;
  vector3.x = x, vector3.y = y, vector3.z = z;
  return vector3;
}

Vector3i NewVector3i(int x, int y, int z){
  Vector3i vector3;
  vector3.x = x, vector3.y = y, vector3.z = z;
  return vector3;
}

Model NewModel(){
  Model mdl;
  //Note that we will have dynamic memory allocation to match the amount of verts/faces, so we set them to null.
  mdl.verts = NULL;
  mdl.faces = NULL;
  return mdl;
  
}

Model ReadOBJ(const char* name){
  FILE* file = fopen(name, "r");
  if (!file) {
    perror("Could not open OBJ file");
    exit(1);
  }

  char line[256];
  int vert_count = 0;
  Model mdl = NewModel();

  while (fgets(line, sizeof(line), file)) {
    if (strncmp(line, "v ", 2) == 0) {
      vert_count += 1;
      Vector3f v;
      sscanf(line + 2, "%f %f %f", &v.x, &v.y, &v.z);
      mdl.verts = realloc(mdl.verts, vert_count * sizeof(Vector3f));
      mdl.verts[vert_count - 1] = v;
    }
  }
  return mdl;
}

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}