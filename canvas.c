#include "canvas.h"

int canvas_init(Canvas *canvas, const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }
    canvas->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!canvas->window) {
        SDL_Quit();
        return -1;
    }
    canvas->renderer = SDL_CreateRenderer(canvas->window, -1, SDL_RENDERER_ACCELERATED);
    if (!canvas->renderer) {
        SDL_DestroyWindow(canvas->window);
        SDL_Quit();
        return -1;
    }
    canvas->width = width;
    canvas->height = height;
    return 0;
}

void canvas_clear(Canvas *canvas, SDL_Color color) {
    SDL_SetRenderDrawColor(canvas->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(canvas->renderer);
}

void canvas_draw_rect(Canvas *canvas, int x, int y, int w, int h, SDL_Color color) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(canvas->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(canvas->renderer, &rect);
}

void change_color(Canvas *canvas, SDL_Rect rect, SDL_Color color) {
        SDL_SetRenderDrawColor(canvas->renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(canvas->renderer, &rect);

}

void canvas_draw_line(Canvas *canvas, int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(canvas->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(canvas->renderer, x1, y1, x2, y2);
}

void canvas_present(Canvas *canvas) {
    SDL_RenderPresent(canvas->renderer);
}

void canvas_destroy(Canvas *canvas) {
    SDL_DestroyRenderer(canvas->renderer);
    SDL_DestroyWindow(canvas->window);
    SDL_Quit();
}
