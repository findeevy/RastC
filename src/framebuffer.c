#include "framebuffer.h"
#include "tools.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void Line(int x0, int y0, int x1, int y1, FrameBuffer* fb, FrameBufferColor color){
  bool direction = false; 
  if (abs(x0-x1)<abs(y0-y1)){
    Tswap(&x0, &y0); 
    Tswap(&x1, &y1); 
    direction = true; 
  } 
  if (x0>x1){
    Tswap(&x0, &x1); 
    Tswap(&y0, &y1); 
  } 
  for (int x=x0; x<=x1; x++) { 
    float t = (x-x0)/(float)(x1-x0); 
    int y = y0*(1.-t) + y1*t; 
    if (direction){ 
      Set(y, x, fb, color);
    } 
    else{ 
      Set(x, y, fb, color); 
    } 
  }
}

