#include <math.h>
#include "rendering.h"

void PutPixel(SDL_Renderer *renderer, int Cx, int Cy, struct Color color) {
    int Sx = Cw / 2 + Cx;
    int Sy = Ch / 2 - Cy;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawPoint(renderer, Sx, Sy);
}

struct Vec3 CanvasToViewport(int x, int y) {
    struct Vec3 viewport_point;
    viewport_point.x = (float) x * ((float) Vw / (float) Cw);
    viewport_point.y = (float) y * ((float) Vh / (float) Ch);
    viewport_point.z = (float) d;
    return viewport_point;
}

struct Vec2 IntersectRaySphere(struct Vec3 O, struct Vec3 D, struct Sphere sphere) {
    float r = sphere.radius;
    struct Vec3 CO = Sub(O, sphere.center);

    float a = Dot(D, D);
    float b = 2.0f * Dot(CO, D);
    float c = Dot(CO, CO) - r * r;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0.0f) {
        struct Vec2 result = {INFINITY, INFINITY};
        return result;
    }
    float t1 = (-b + sqrtf(discriminant)) / (2 * a);
    float t2 = (-b - sqrtf(discriminant)) / (2 * a);
    struct Vec2 result = {t1, t2};
    return result;
}

struct Color TraceRay(struct Vec3 O, struct Vec3 D, float t_min, float t_max, struct Sphere** spheres, int num_sphere) {
    float closest_t = INFINITY;
    struct Sphere *closest_sphere = NULL;

    for (int i = 0; i < num_sphere; ++i) {
        struct Sphere *sphere = spheres[i];
        struct Vec2 t = IntersectRaySphere(O, D, *sphere);
        float t1 = t.x, t2 = t.y;
        if (t1 >= t_min && t1 <= t_max && t1 < closest_t) {
            closest_t = t1;
            closest_sphere = sphere;
        }
        if (t2 >= t_min && t2 <= t_max && t2 < closest_t) {
            closest_t = t2;
            closest_sphere = sphere;
        }
    }
    if (closest_sphere == NULL) {
        return BACKGROUND_COLOR;
    }
    return closest_sphere->color;
}
