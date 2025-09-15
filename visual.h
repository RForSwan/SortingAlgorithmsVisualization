#ifndef _VISUAL_H_
#define _VISUAL_H_

typedef struct SDL_Display_s
{
    SDL_Window*   window;
    SDL_Renderer* renderer;

}SDL_Display;

SDL_Display* visual_CreateDisplay();
void         visual_DestroyDisplay(SDL_Display* display);


void draw_title_screen(SDL_Renderer *renderer);
int play_clicked(int x, int y);
void draw_bars(SDL_Renderer *renderer, int arr[], int n, int i, int j);

#endif
