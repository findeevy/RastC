#include <stdio.h>
#include "framebuffer.h"

int main(){
  FrameBuffer *fb = NewBuffer(640, 480);
  FrameBufferColor fbc = NewColor(0, 0, 0);
  for (int x = 0; x < fb -> width; ++x){
    for (int y = 0; y < fb -> height; ++y){
      fbc = NewColor((int)(((float)x/(fb -> width))*255), (int)(((float)y/(fb -> height))*255), 0);
      Set(x, y, fb, fbc);
    }
  }
  WriteToPPM(fb, "out.ppm");
  return 0;
}
