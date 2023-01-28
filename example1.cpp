#include <iostream>

#include <SDL2/SDL.h>

#define Height 200
#define Width  200

using namespace std;

SDL_Surface *screen = nullptr;

void set_pixel(int x, int y, Uint32 pixel)
{
      Uint8 *target_pixel = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
      *(Uint32 *)target_pixel = pixel;
}

Uint32 get_pixel(int x, int y)
{
      Uint8 *target_pixel = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
      return *(Uint32 *)target_pixel;
}

void ClearScreen() {
    screen = SDL_CreateRGBSurface(0, Width, Height, 32, 0, 0, 0, 0);
}

void DrawScreen(SDL_Renderer *renderer) {
    SDL_Texture *tex = nullptr;

    SDL_Rect rect;
    rect.x = 0; rect.y = 0; rect.w = Width; rect.h = Height;

    tex = SDL_CreateTextureFromSurface(renderer, screen);
    if (tex == NULL) {
        cout << "ERROR" << endl;
    }
    SDL_RenderCopy(renderer, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

int main() {
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        cout << "SDL could not be initiaiized: " << SDL_GetError();
    else
        cout << "SDL system is ready to go" << endl;

    window = SDL_CreateWindow("3D Eingine", 20, 20, Width, Height, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    screen = SDL_CreateRGBSurface(0, Width, Height, 32, 0, 0, 0, 0);

    bool run = true;

    ClearScreen();

    set_pixel(Width / 2, Height / 2, 0xFF0000);
    cout << hex << get_pixel(Width / 2, Height / 2) << endl;
    while (run) {
        SDL_Event event;
    
        while(SDL_PollEvent(&event)){
            switch(event.type) {
                case SDL_QUIT:
                    run = false;
                    break;
                default:
                    break;
            }
        }
        DrawScreen(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
