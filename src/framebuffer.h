#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER

#include <stdint.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} FrameBufferColor;

typedef struct {
  FrameBufferColor pixel[HEIGHT][WIDTH];
} FrameBuffer;

FrameBufferColor New(uint8_t r, uint8_t g, uint8_t b);

void Set(int x, int y, FrameBuffer* fb, FrameBufferColor color);

#endif
