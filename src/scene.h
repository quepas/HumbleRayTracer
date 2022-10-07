#ifndef HUMBLERAYTRACER_SCENE_H
#define HUMBLERAYTRACER_SCENE_H

#include "math.h"

static const struct Vec3 O = {0.0f, 0.0f, 0.0f};

struct Color {
    int r, g, b;
};

static const struct Color BACKGROUND_COLOR = {255, 255, 255};

struct Sphere {
    float radius;
    struct Vec3 center;
    struct Color color;
};


#endif //HUMBLERAYTRACER_SCENE_H
