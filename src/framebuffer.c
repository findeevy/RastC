#include "framebuffer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Function to set RGB value in the framebuffer.
FrameBufferColor NewColor(uint8_t r, uint8_t g, uint8_t b){
  FrameBufferColor color;
  color.r = r, color.g = g, color.b = b;
  return color;
}

//Function to set RGB value in the framebuffer.
FrameBuffer* NewBuffer(int width, int height){
  FrameBufferColor **temparr;
  temparr = (FrameBufferColor **)malloc(width * sizeof(FrameBufferColor *));
  for (int i = 0; i < width; ++i){
    temparr[i] = (FrameBufferColor *)malloc(height * sizeof(FrameBufferColor));
  }
  FrameBuffer* fb = (FrameBuffer*)malloc(sizeof(FrameBuffer));
  fb -> pixel = temparr;
  fb -> height = height;
  fb -> width = width;
  return fb;
}

//Function to set RGB value in the framebuffer.
void Set(int x, int y, FrameBuffer* fb, FrameBufferColor color){
  fb -> pixel[x][y] = color;
}

void WriteToPPM(FrameBuffer* fb, const char *filename){
  FILE *fp = fopen(filename, "wb");
  fprintf(fp, "P6\n%d %d\n255\n", fb->width, fb->height);
  for (int y = 0; y < fb->height; ++y){
    for (int x = 0; x < fb->width; ++x){
      fputc(fb -> pixel[x][y].r, fp);
      fputc(fb -> pixel[x][y].g, fp);
      fputc(fb -> pixel[x][y].b, fp);
    }
  }
  fclose(fp);
  printf("File written");
}

