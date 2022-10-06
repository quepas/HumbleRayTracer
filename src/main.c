#include <math.h>
#include <SDL2/SDL.h>

const int NUM_SPHERES = 2;
const int Cw = 640, Ch = 480;
const int Vw = 1, Vh = 1, d = 1;

struct Point {
    int x, y;
};

struct Color {
    int r, g, b;
};

struct Color BACKGROUND_COLOR = {255, 255, 255};

struct Vec3 {
    float x, y, z;
};

struct Vec2 {
    float x, y;
};

struct Sphere {
    float radius;
    struct Vec3 center;
    struct Color color;
};

struct Sphere** spheres;

const struct Vec3 O = {0.0f, 0.0f, 0.0f};

void PutPixel(SDL_Renderer* renderer, int Cx, int Cy, struct Color color) {
    int Sx = Cw / 2 + Cx;
    int Sy = Ch / 2 - Cy;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawPoint(renderer, Sx, Sy);
}

struct Vec3 CanvasToViewport(int x, int y) {
    struct Vec3 viewport_point;
    viewport_point.x = (float) x * ((float) Vw/(float) Cw);
    viewport_point.y = (float) y * ((float) Vh/(float) Ch);
    viewport_point.z = (float) d;
    return viewport_point;
}

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

struct Vec2 IntersectRaySphere(struct Vec3 O, struct Vec3 D, struct Sphere sphere) {
    float r = sphere.radius;
    struct Vec3 CO = Sub(O, sphere.center);

    float a = Dot(D, D);
    float b = 2.0f * Dot(CO, D);
    float c = Dot(CO, CO) - r*r;

    float discriminant = b*b - 4*a*c;
    if (discriminant < 0.0f) {
        struct Vec2 result = {INFINITY, INFINITY};
        return result;
    }
    float t1 = (-b + sqrtf(discriminant)) / (2*a);
    float t2 = (-b - sqrtf(discriminant)) / (2*a);
    struct Vec2 result = {t1, t2};
    return result;
}

struct Color TraceRay(struct Vec3 O, struct Vec3 D, float t_min, float t_max) {
    float closest_t = INFINITY;
    struct Sphere* closest_sphere = NULL;

    for (int i = 0; i < NUM_SPHERES; ++i) {
        struct Sphere* sphere = spheres[i];
        struct Vec2 t = IntersectRaySphere(O, D,*sphere);
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

int main(int argc, char **argv) {
    spheres = malloc(sizeof(struct Sphere*) * NUM_SPHERES);
    struct Sphere* s = malloc(sizeof(struct Sphere));
    s->radius = 1.0f;
    struct Vec3 center = {0.0f, -1.0f, 3.0f};
    s->center = center;
    struct Color color = {255, 0, 0};
    s->color = color;

    struct Sphere* s2 = malloc(sizeof(struct Sphere));
    s2->radius = 1.0f;
    struct Vec3 center2 = {2.0f, 0.0f, 4.0f};
    s2->center = center2;
    struct Color color2 = {0, 0, 255};
    s2->color = color2;

    spheres[0] = s;
    spheres[1] = s2;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
            "ray_tracer",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Cw,
            Ch,
            0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for (int x = -Cw/2; x < Cw/2; ++x) {
        for (int y = -Ch/2; y < Ch/2; ++y) {
            struct Vec3 D = CanvasToViewport(x, y);
            struct Color color = TraceRay(O, D, 1, INFINITY);
            PutPixel(renderer, x, y, color);
        }
    }
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}