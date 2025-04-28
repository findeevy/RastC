#include <stdio.h>
#include <string.h>
#include "renderer.h"
#include "tools.h"

int main(){
  FrameBuffer *fb = NewBuffer(720, 720);
  FrameBufferColor fbc = NewColor(0, 0, 0);
  FrameBufferColor red = NewColor(255, 0, 0);
  
  for (int x = 0; x < fb -> width; ++x){
    for (int y = 0; y < fb -> height; ++y){
      Set(x, y, fb, fbc);
    }
  }

  Model *tpot = ReadOBJ("res/utah_teapot.obj");
  Light light = NewLight(NewVector3f(0.0, 0.0 , -1.0), 1.0);
  tpot -> transform.x = 3.5;
  tpot -> transform.y = 2.0;
  printf("Faces: %d\nVerts: %d\n", tpot -> nfaces, tpot -> nverts);
  RenderLitPolygon(tpot, light, fb, red);
  FlipFramebufferVertically(fb);
  WriteToPPM(fb, "out.ppm");
  return 0;
}
