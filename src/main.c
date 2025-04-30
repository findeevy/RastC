#include <stdio.h>
#include <string.h>
#include "renderer.h"
#include "tools.h"



int main(){
  //Initialize the dimensions of the render.
  static const int height = 720;
  static const int width = 720;

  //Initialize the ZBuffer and the frame buffer.
  FrameBuffer *fb = NewBuffer(height, width);
  float *zb = malloc(width * height * sizeof(float));
  Color fbc = NewColor(0, 0, 0);
  Color green = NewColor(0, 255, 0);
  
  for (int x = 0; x < fb -> width; ++x){
    for (int y = 0; y < fb -> height; ++y){
      Set(x, y, fb, fbc);
    }
  }

  Model *tpot = ReadOBJ("res/chicken.obj");
  //FrameBuffer *texture = ReadPPM("res/textures/chicken.ppm");
  Light light = NewLight(NewVector3f(0.0, 0.0 , -1.0), 1.0);
  tpot -> transform.x = 3.5;
  tpot -> transform.y = 2.0;
  printf("Faces: %d\nVertices: %d\nTextures: %d", tpot -> nfaces, tpot -> nverts, tpot -> ntexts);
  RenderLitPolygon(tpot, light, fb, zb, green);
  free(zb);

  FlipFramebufferVertically(fb);
  WriteToPPM(fb, "out.ppm");

  return 0;
}
