#ifndef _VISUAL_H_
#define _VISUAL_H_

///// INCLUDES /////


///// VISUALS /////

typedef struct Colors_s
{
    ///// COLOR SET
    //// Light mode
    // Background
    SDL_Color Background_top_LM;
    SDL_Color Background_bot_LM;
    // Button
    SDL_Color Button_top_LM;
    SDL_Color Button_bot_LM;
    // Button hovered
    SDL_Color ButtonHovered_top_LM;
    SDL_Color ButtonHovered_bot_LM;
    /// Dark mode
    // Background
    SDL_Color Background_top_DM;
    SDL_Color Background_bot_DM;
    // Button
    SDL_Color Button_top_DM;
    SDL_Color Button_bot_DM;
    // Button hovered
    SDL_Color ButtonHovered_top_DM;
    SDL_Color ButtonHovered_bot_DM;
} Colors;

typedef struct Button_s
{
    SDL_Rect rect;
    const char *label;
    bool hovered;
} Button;

// Menus buttons on the left of the screen
extern Button buttons[4];

void draw_title_screen(App* app, SDL_Renderer *renderer, TTF_Font *font);
int play_clicked(int x, int y);
void draw_bars(SDL_Renderer *renderer, int arr[], int n, int i, int j);

void draw_barsA(App* app, SDL_Renderer *renderer, int arr[], int n, int i, int j);
void draw_barsB(App* app, SDL_Renderer *renderer, int arr[], int n, int i, int j);
void draw_barsC(App* app, SDL_Renderer *renderer, int arr[], int n, int i, int j);
void draw_barsD(App* app, SDL_Renderer *renderer, int arr[], int n, int i, int j);

///// OTHERS /////

Colors *visual_createColorSet();
void visual_destroyColorSet(Colors *colors);

///// SUB FUNCTIONS /////

///// FUNCTIONS /////

void visual_drawSettingsScreen(App* app);
void visual_drawVisualizationScreen(App* app);

#endif
