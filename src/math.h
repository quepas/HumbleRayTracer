#ifndef HUMBLERAYTRACER_MATH_H
#define HUMBLERAYTRACER_MATH_H

struct Vec3 {
    float x, y, z;
};

struct Vec2 {
    float x, y;
};

float Dot(struct Vec3 a, struct Vec3 b);

struct Vec3 Mul(float scalar, struct Vec3 v);

struct Vec3 Sub(struct Vec3 a, struct Vec3 b);

#endif //HUMBLERAYTRACER_MATH_H
