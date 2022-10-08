#include <SDL2/SDL.h>
#include "rendering.h"

int main(int argc, char **argv) {
    const int NUM_SPHERES = 2;
    struct Sphere** spheres = malloc(sizeof(struct Sphere *) * NUM_SPHERES);
    struct Sphere *s = malloc(sizeof(struct Sphere));
    s->radius = 1.0f;
    struct Vec3 center = {0.0f, -1.0f, 3.0f};
    s->center = center;
    struct Color color = {255, 0, 0};
    s->color = color;

    struct Sphere *s2 = malloc(sizeof(struct Sphere));
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

    for (int x = -Cw / 2; x < Cw / 2; ++x) {
        for (int y = -Ch / 2; y < Ch / 2; ++y) {
            struct Vec3 D = CanvasToViewport(x, y);
            struct Color color = TraceRay(O, D, 1, INFINITY, spheres, NUM_SPHERES);
            PutPixel(renderer, x, y, color);
        }
    }
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}