#include "canvas.h"
#include <SDL2/SDL.h>

#define ROWS 40
#define COLS 30

typedef struct {
    int status;
    SDL_Rect rect;
} Cell;

Uint32 startTime;

Uint32 Time(){
    return SDL_GetTicks() - startTime;
}

void initialize(Canvas *canvas,Cell (*grid)[30]) {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 30; j++) {
            grid[i][j].status = 0;
            grid[i][j].rect = (SDL_Rect) {j * 20, i * 20, 20, 20};

        }
    }


    grid[0][0].status = 1;
    grid[1][1].status = 1;
    grid[0][2].status = 1;
    grid[1][2].status = 1;
    grid[2][1].status = 1;
}


void copy_grid(Cell source[ROWS][COLS], int destination[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            destination[i][j] = source[i][j].status;
        }
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", destination[i][j]);
        }
        printf("\n");
        
    }
    printf("-------------------------------------\n");

    
}


void update(Canvas *canvas, Cell (*grid)[COLS]) {
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j].status == 1) {
                change_color(canvas, grid[i][j].rect, black);
            }
        }
    }

    int temp[ROWS][COLS] = {0};
    copy_grid(grid, temp);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int live_neighbors = 0;

            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue; 
                    int ni = i + x;
                    int nj = j + y;
                    if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS) {
                        live_neighbors += temp[ni][nj];
                    }
                }
            }

            
            if (temp[i][j] == 1) {
                if (live_neighbors < 2 || live_neighbors > 3) {
                    grid[i][j].status = 0; 
                }
            } else {
                if (live_neighbors == 3) {
                    grid[i][j].status = 1; 
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    startTime = SDL_GetTicks();

    Canvas canvas;
    if (canvas_init(&canvas, "Canvas Example", 800, 600) != 0) {
        return -1;
    }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {250,0,0, 255};
    int running = 1;
    SDL_Event event;

    Cell grid[40][30];
    int i=0;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        if (i==0) {
            initialize(&canvas,grid);
        }

        canvas_clear(&canvas, white);
        for (int i = 0; i < ROWS; i++) {
        canvas_draw_line(&canvas, 20*i, 0, 20*i, 600, red);
            
        }
        for (int i = 0; i < COLS; i++) {
        canvas_draw_line(&canvas, 0, 20*i, 800, 20*i, red);
            
        }
        update(&canvas, grid);
        canvas_present(&canvas);

        SDL_Delay(100); 
        i++;
    }

    canvas_destroy(&canvas);

    return 0;
}
