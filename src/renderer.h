#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct Vector2f{
  float x;
  float y;
} Vector2f;

typedef struct Vector2i{
  int x;
  int y;
} Vector2i;

typedef struct Vector3i{
  int x;
  int y;
  int z;
} Vector3i;

typedef struct Face{
  Vector3i fverts;
  Vector3i ftexts;
} Face;

typedef union Vector3f{
    struct {
        float x, y, z;
    };
    float array[3];
} Vector3f;

typedef struct Model{
  Vector3f* verts;
  Face* faces;
  Vector2f* texts;
  Vector3f transform;
  int nverts;
  int nfaces;
  int ntexts;
} Model;

typedef struct Light{
  Vector3f direction;
  float intensity;
} Light;

typedef struct Color{
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Color;

typedef struct FrameBuffer{
  Color** pixel;
  int height;
  int width;
} FrameBuffer;

Light NewLight(Vector3f direction, float intensity);

Vector3f NewVector3f(float x, float y, float z);

Vector3i NewVector3i(int x, int y, int z);

Vector2f NewVector2f(float x, float y);

Vector2i NewVector2i(int x, int y);

FrameBuffer* NewBuffer(int width, int height);

Color NewColor(uint8_t r, uint8_t g, uint8_t b);

void WriteToPPM(FrameBuffer* fb, const char *filename);

void Set(int x, int y, FrameBuffer* fb, Color color);

void Line(int x0, int y0, int x1, int y1, FrameBuffer* fb, Color color);

void Triangle(Vector3f* points, FrameBuffer* fb, float* zb, Color color);

Model* NewModel();

Vector3f Vector3fSub(Vector3f a, Vector3f b);

float Vector3fMul(Vector3f a, Vector3f b);

Vector3f Cross(Vector3f a, Vector3f b);

float Magnitude(Vector3f a);

Vector3f Normalize(Vector3f a);

//Computes for "point" in a give triangle.
Vector3f Barycentric(Vector3f a, Vector3f b, Vector3f c, Vector3f point);

void FlipFramebufferVertically(FrameBuffer* fb);

Model* ReadOBJ(const char* file);

void RenderWireframe(Model* mdl, FrameBuffer* fb, Color color);

void RenderUnlitPolygon(Model* mdl, FrameBuffer* fb, float* zb, Color color);

void RenderLitPolygon(Model* mdl, Light light, FrameBuffer* fb, float* zb, Color color);

#endif
