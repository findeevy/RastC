#include <stdio.h>
#include <string.h>
#include "renderer.h"
#include "tools.h"

int main(){
  FrameBuffer *fb = NewBuffer(720, 720);
  FrameBufferColor fbc = NewColor(0, 0, 0);
  FrameBufferColor blue = NewColor(0, 0, 255);
  
  for (int x = 0; x < fb -> width; ++x){
    for (int y = 0; y < fb -> height; ++y){
      Set(x, y, fb, fbc);
    }
  }

  Model *tpot = ReadOBJ("res/utah_teapot.obj");
  tpot -> transform.x = 23.6;
  tpot -> transform.y = 22.0;
  RenderWireframe(tpot, fb, blue);
  FlipFramebufferVertically(fb);
  WriteToPPM(fb, "out.ppm");

  return 0;
}
