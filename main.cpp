#include <iostream>
#include <SDL.h>
#include <math.h>
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
using namespace std;

bool table[WINDOW_HEIGHT][WINDOW_WIDTH];
unsigned short antX = floor(floor(WINDOW_WIDTH / 2) / 3), antY = floor(floor(WINDOW_HEIGHT / 2) / 3), antDirection = 0, PT_SIZE = 3;

int main(int argc, char** argv)
{
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    while(true)
    {
        live();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        for(unsigned short line = 0; line < WINDOW_HEIGHT; line++)
        {
            for(unsigned short column = 0; column < WINDOW_WIDTH; column++)
            {
                unsigned short columnPx = column * PT_SIZE, linePx = line * PT_SIZE;
                if(table[line][column])
                    for(unsigned short x = columnPx; x < columnPx + 3; x++)
                        for(unsigned short y = linePx; y < linePx + 3; y++)
                            SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        unsigned short antXTmp = antX * PT_SIZE, antYTmp = antY * PT_SIZE;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, antXTmp + 1, antYTmp + 1);
        switch(antDirection)
        {
            case 0:
                SDL_RenderDrawPoint(renderer, antXTmp + 1, antYTmp);
                SDL_RenderDrawPoint(renderer, antXTmp, antYTmp + 2);
                SDL_RenderDrawPoint(renderer, antXTmp + 1, antYTmp + 2);
                SDL_RenderDrawPoint(renderer, antXTmp + 2, antYTmp + 2);
                break;
            case 1:
                SDL_RenderDrawPoint(renderer, antXTmp, antYTmp + 1);
                SDL_RenderDrawPoint(renderer, antXTmp + 2, antYTmp);
                SDL_RenderDrawPoint(renderer, antXTmp + 2, antYTmp + 1);
                SDL_RenderDrawPoint(renderer, antXTmp + 2, antYTmp + 2);
                break;
            case 2:
                SDL_RenderDrawPoint(renderer, antXTmp + 1, antYTmp + 2);
                SDL_RenderDrawPoint(renderer, antXTmp, antYTmp);
                SDL_RenderDrawPoint(renderer, antXTmp + 1, antYTmp);
                SDL_RenderDrawPoint(renderer, antXTmp + 2, antYTmp);
                break;
            case 3:
                SDL_RenderDrawPoint(renderer, antXTmp + 2, antYTmp + 1);
                SDL_RenderDrawPoint(renderer, antXTmp, antYTmp);
                SDL_RenderDrawPoint(renderer, antXTmp, antYTmp + 1);
                SDL_RenderDrawPoint(renderer, antXTmp, antYTmp + 2);
                break;
        }

        if(table[antY][antX]) antDirection++;
        else antDirection--;
        antDirection %= 4;
        table[antY][antX] = !table[antY][antX];

        switch(antDirection)
        {
            case 0: antY++; break;
            case 1: antX++; break;
            case 2: antY--; break;
            case 3: antX--; break;
        }

        SDL_RenderPresent(renderer);
        if(SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
