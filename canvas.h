#ifndef CANVAS_H
#define CANVAS_H

#include <SDL2/SDL.h>

// Structure to hold canvas properties
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;
} Canvas;


// Initialize the canvas
int canvas_init(Canvas *canvas, const char *title, int width, int height);

// Clear the canvas with a given color
void canvas_clear(Canvas *canvas, SDL_Color color);

// Draw a rectangle on the canvas
void canvas_draw_rect(Canvas *canvas, int x, int y, int w, int h, SDL_Color color);


void change_color(Canvas *canvas, SDL_Rect rect, SDL_Color color);


// Draw a line on the canvas
void canvas_draw_line(Canvas *canvas, int x1, int y1, int x2, int y2, SDL_Color color);

// Present the canvas (refresh the screen)
void canvas_present(Canvas *canvas);

// Clean up the canvas
void canvas_destroy(Canvas *canvas);

#endif // CANVAS_H
