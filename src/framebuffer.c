#include "framebuffer.h"
#include <stdint.h>

//Function to set RGB value in the framebuffer.
FrameBufferColor New(uint8_t r, uint8_t g, uint8_t b){
  FrameBufferColor color;
  color.r = r, color.g = g, color.b = b;
  return color;
}

//Function to set RGB value in the framebuffer.
void Set(int x, int y, FrameBuffer* fb, FrameBufferColor color){
  fb->pixel[y][x] = color;
}
