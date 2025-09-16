#ifndef _VISUAL_H_
#define _VISUAL_H_


void draw_title_screen(SDL_Renderer *renderer, TTF_Font *font);
int play_clicked(int x, int y);
void draw_bars(SDL_Renderer *renderer, int arr[], int n, int i, int j);

void draw_barsA(SDL_Renderer *renderer, int arr[], int n, int i, int j);
void draw_barsB(SDL_Renderer *renderer, int arr[], int n, int i, int j);
void draw_barsC(SDL_Renderer *renderer, int arr[], int n, int i, int j);
void draw_barsD(SDL_Renderer *renderer, int arr[], int n, int i, int j);

#endif
