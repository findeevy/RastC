#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

FrameBuffer* NewBuffer(int width, int height);

FrameBufferColor NewColor(uint8_t r, uint8_t g, uint8_t b);

void WriteToPPM(FrameBuffer* fb, const char *filename);

void Set(int x, int y, FrameBuffer* fb, FrameBufferColor color);

void Line(int x0, int y0, int x1, int y1, FrameBuffer* fb, FrameBufferColor color);

#endif
