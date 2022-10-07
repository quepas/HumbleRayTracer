#include "math.h"

float Dot(struct Vec3 a, struct Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

struct Vec3 Mul(float scalar, struct Vec3 v) {
    v.x *= scalar;
    v.y *= scalar;
    v.z *= scalar;
    return v;
}

struct Vec3 Sub(struct Vec3 a, struct Vec3 b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}
