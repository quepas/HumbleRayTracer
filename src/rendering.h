#ifndef HUMBLERAYTRACER_RENDERING_H
#define HUMBLERAYTRACER_RENDERING_H

#include <SDL_render.h>
#include "math.h"
#include "scene.h"

static const int Cw = 500, Ch = 500;
static const int Vw = 1, Vh = 1, d = 1;

void PutPixel(SDL_Renderer *renderer, int Cx, int Cy, struct Color color);

struct Vec3 CanvasToViewport(int x, int y);

struct Vec2 IntersectRaySphere(struct Vec3 O, struct Vec3 D, struct Sphere sphere);

struct Color TraceRay(struct Vec3 O, struct Vec3 D, float t_min, float t_max, struct Sphere** spheres, int num_sphere);

#endif //HUMBLERAYTRACER_RENDERING_H
