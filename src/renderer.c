#include "renderer.h"
#include "tools.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

Vector3f NewVector3f(float x, float y, float z){
  Vector3f vector3;
  vector3.x = x, vector3.y = y, vector3.z = z;
  return vector3;
}

Vector3i NewVector3i(int x, int y, int z){
  Vector3i vector3;
  vector3.x = x, vector3.y = y, vector3.z = z;
  return vector3;
}

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
  if(x >= 0 && y >= 0 && x < fb -> width && y < fb -> height ){
    fb -> pixel[x][y] = color;
  }
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
    Swap(&x0, &y0); 
    Swap(&x1, &y1); 
    direction = true; 
  } 
  if (x0>x1){
    Swap(&x0, &x1); 
    Swap(&y0, &y1); 
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

Model* NewModel(){
  Model *mdl = malloc(sizeof(Model));
    if (!mdl) {
        fprintf(stderr, "Memory allocation failed for Model.\n");
        return NULL;
    }
  //Note that we will have dynamic memory allocation to match the amount of verts/faces, so we set them to null.
  mdl -> verts = NULL;
  mdl -> faces = NULL;
  mdl -> nfaces = 0;
  mdl -> nverts = 0;
  return mdl;
  
}

Model* ReadOBJ(const char* name) {
    FILE* file = fopen(name, "r");
    if (!file) {
        perror("Could not open OBJ file");
        exit(1);
    }

    char line[256];
    Model *mdl = NewModel();

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) {
            Vector3f v;
            sscanf(line + 2, "%f %f %f", &v.x, &v.y, &v.z);
            mdl->nverts++;
            mdl->verts = realloc(mdl->verts, mdl->nverts * sizeof(Vector3f));
            mdl->verts[mdl->nverts - 1] = v;
        } 
	else if (strncmp(line, "f ", 2) == 0) {
            char* face_chunk = strtok(line + 2, " ");
            while (face_chunk != NULL) {
                Vector3i f = {0, 0, 0};
                sscanf(face_chunk, "%d/%d/%d", &f.x, &f.y, &f.z);
                mdl->nfaces++;
                mdl->faces = realloc(mdl->faces, mdl->nfaces * sizeof(Vector3i));
                mdl->faces[mdl->nfaces - 1] = f;
                face_chunk = strtok(NULL, " ");
            }
        }
    }

    fclose(file);
    return mdl;
}

void RenderWireframe(Model* mdl, FrameBuffer* fb, FrameBufferColor color){
  for (int i=0; i < mdl -> nfaces; i++) { 
    Vector3i face = mdl -> faces[i];
    int vert_arr[3] = {face.x, face.y, face.z};
    //printf("%d %d %d\n", vert_arr[0], vert_arr[1], vert_arr[2]);
    for (int j=0; j<3; j++) { 
      Vector3f v0 = mdl->verts[vert_arr[j]]; 
      Vector3f v1 = mdl->verts[vert_arr[(j+1)%3]]; 
      //printf("%f %f %f %f\n", v0.x, v1.x, v0.y, v1.y);
      int x0 = ((v0.x+1.)*(fb->width))/20.; 
      int y0 = ((v0.y+1.)*(fb->height))/20.; 
      int x1 = ((v1.x+1.)*(fb->width))/20.; 
      int y1 = ((v1.y+1.)*(fb->height))/20.;
      //printf("%d %d %d %d\n", x0, x1, y0, y1);
      printf("RWF");
      Line(x0, y0, x1, y1, fb, color); 
    }
    printf("%f\n", (float)i/(mdl -> nfaces));
  }
}
