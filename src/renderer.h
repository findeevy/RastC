#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
  int nverts;
  int nfaces;
} Model;

typedef struct FrameBufferColor{
  uint8_t r;
  uint8_t g;
  uint8_t b;
} FrameBufferColor;

typedef struct FrameBuffer{
  FrameBufferColor** pixel;
  int height;
  int width;
} FrameBuffer;

Vector3f NewVector3f(float x, float y, float z);

Vector3i NewVector3i(int x, int y, int z);

FrameBuffer* NewBuffer(int width, int height);

FrameBufferColor NewColor(uint8_t r, uint8_t g, uint8_t b);

void WriteToPPM(FrameBuffer* fb, const char *filename);

void Set(int x, int y, FrameBuffer* fb, FrameBufferColor color);

void Line(int x0, int y0, int x1, int y1, FrameBuffer* fb, FrameBufferColor color);

Model* NewModel();

Model* ReadOBJ(const char* file);

void RenderWireframe(Model* mdl, FrameBuffer* fb, FrameBufferColor color);

#endif
