#include "settings.h"

SDL_Display* visual_CreateDisplay()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Display* display = calloc(1, sizeof(SDL_Display));

    display->window = SDL_CreateWindow("Bubble Sort Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(!display->window){
        printf("Error creating SDL Window: %s\n", SDL_GetError());
        free(display);
        SDL_Quit();
        return NULL;
    }
    display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);
    if(!display->renderer){
        printf("Error creating SDL Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(display->window);
        free(display);
        SDL_Quit();
        return NULL;
    }
    return display;
}

void visual_DestroyDisplay(SDL_Display* display)
{
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
    free(display);
    SDL_Quit();
}


void draw_gradient_button(SDL_Renderer *renderer, SDL_Rect button, SDL_Color top, SDL_Color bottom, int radius) {
    for (int y = 0; y < button.h; y++) {
        float t = (float)y / (float)(button.h - 1);

        Uint8 r = (Uint8)((1 - t) * top.r + t * bottom.r);
        Uint8 g = (Uint8)((1 - t) * top.g + t * bottom.g);
        Uint8 b = (Uint8)((1 - t) * top.b + t * bottom.b);

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderDrawLine(renderer, button.x, button.y + y, button.x + button.w, button.y + y);
    }

    // Draw a white rectangle border
    rectangleRGBA(renderer, button.x, button.y, button.x + button.w, button.y + button.h, 255, 255, 255, 255);
}


void draw_button(SDL_Renderer *renderer, SDL_Rect button, const char *label, TTF_Font *font, int hovered) {
    SDL_Color top, bottom;    // Button
    if (hovered) {
        // Hover
        top = (SDL_Color){40, 167, 69, 255};   // #28A745
        bottom = (SDL_Color){30, 120, 50, 255};
    } else {
        // Normal
        top = (SDL_Color){76, 209, 55, 255};   // #4CD137
        bottom = (SDL_Color){56, 173, 40, 255};
    }

    draw_gradient_button(renderer, button, top, bottom, 12);

    // Text
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, label, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int textW, textH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
    SDL_Rect textRect = { button.x + (button.w - textW) / 2, button.y + (button.h - textH) / 2, textW, textH };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void draw_gradient_background(SDL_Renderer *renderer,
                              SDL_Color top, SDL_Color bottom) {
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        // interpolation linéaire entre top et bottom
        float t = (float)y / (float)(WINDOW_HEIGHT - 1);

        Uint8 r = (Uint8)((1 - t) * top.r + t * bottom.r);
        Uint8 g = (Uint8)((1 - t) * top.g + t * bottom.g);
        Uint8 b = (Uint8)((1 - t) * top.b + t * bottom.b);

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }
}

void draw_title_screen(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Color top = {116, 171, 226, 255};
    SDL_Color bottom = {85, 99, 222, 255};
    draw_gradient_background(renderer, top, bottom);


    // Button position
    SDL_Rect button = {(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) - MARGIN, BUTTON_WIDTH, BUTTON_HEIGHT};

    // Get mouse position
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    int hovered = play_clicked(mx, my);

    // Draw with over effect
    draw_button(renderer, button, "Play", font, hovered);

    // GIZMOS
    if (Gizmos) {
        // Vertical Midlle line
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
        SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
        // Horizontal Midlle line
        SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
    }

    SDL_RenderPresent(renderer);
}


// Check for mouse click in button
int play_clicked(int x, int y)
{
    int bx = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
    int by = (WINDOW_HEIGHT - BUTTON_HEIGHT) - MARGIN;
    return x >= bx && x <= bx + BUTTON_WIDTH && y >= by && y <= by + BUTTON_HEIGHT;
}


/*void draw_bars(SDL_Renderer *renderer, int arr[], int n, int i, int j) {
    SDL_SetRenderDrawColor(renderer, 153, 196, 210, 0); // Black background
    SDL_RenderClear(renderer);

    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for compared bars
        else {
            int color_value = (arr[k] * 255) / N;
            SDL_SetRenderDrawColor(renderer, color_value, color_value, color_value, 255); // Green for others

        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / N / 3;
        // Set lines to bottom
        //SDL_Rect bar = {k * BAR_WIDTH, WINDOW_HEIGHT - bar_height, BAR_WIDTH - 1, bar_height};
        // Set lines to A position
        SDL_Rect bar = {k * BAR_WIDTH / 3, WINDOW_HEIGHT / 2 - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_RenderFillRect(renderer, &bar);
        // Set lines to B position
        SDL_Rect bar2 = {k * BAR_WIDTH / 3 + WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_RenderFillRect(renderer, &bar2);
        // Set lines to C position
        SDL_Rect bar3 = {k * BAR_WIDTH / 3, WINDOW_HEIGHT - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_RenderFillRect(renderer, &bar3);
        // Set lines to D position
        SDL_Rect bar4 = {k * BAR_WIDTH / 3 + WINDOW_WIDTH / 2, WINDOW_HEIGHT - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_RenderFillRect(renderer, &bar4);


        // GIZMOS
        if (Gizmos) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
            // Sort A
            SDL_RenderDrawRect(renderer, &(SDL_Rect){0, 0, WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});
            // Sort B
            SDL_RenderDrawRect(renderer, &(SDL_Rect){WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});
            // Sort C
            SDL_RenderDrawRect(renderer, &(SDL_Rect){0, (WINDOW_HEIGHT / 2), WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});
            // Sort D
            SDL_RenderDrawRect(renderer, &(SDL_Rect){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});


            // Vertical Midlle line
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
            SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
            // Horizontal Midlle line
            SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);

            // Sorts Lines
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
            SDL_RenderDrawRect(renderer, &bar);
            SDL_RenderDrawRect(renderer, &bar2);
            SDL_RenderDrawRect(renderer, &bar3);
            SDL_RenderDrawRect(renderer, &bar4);
        }
    }
    SDL_RenderPresent(renderer);
}*/


void draw_barsA(SDL_Renderer *renderer, int arr[], int n, int i, int j) {
    SDL_SetRenderDrawColor(renderer, 153, 196, 210, 0); // Black background
    SDL_RenderClear(renderer);

    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for compared bars
        else {
            int color_value = (arr[k] * 255) / N;
            SDL_SetRenderDrawColor(renderer, color_value, color_value, color_value, 255); // Green for others

        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / N / 3;
        // Set lines to A position
        SDL_Rect bar = {k * BAR_WIDTH / 3, WINDOW_HEIGHT / 2 - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_RenderFillRect(renderer, &bar);

        // GIZMOS
        // GIZMOS
        if (Gizmos) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
            // Sort A
            SDL_RenderDrawRect(renderer, &(SDL_Rect){0, 0, WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});
            // Sort B
            SDL_RenderDrawRect(renderer, &(SDL_Rect){WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});
            // Sort C
            SDL_RenderDrawRect(renderer, &(SDL_Rect){0, (WINDOW_HEIGHT / 2), WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});
            // Sort D
            SDL_RenderDrawRect(renderer, &(SDL_Rect){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});


            // Vertical Midlle line
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
            SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
            // Horizontal Midlle line
            SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);

            // Sorts Lines
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
            SDL_RenderDrawRect(renderer, &bar);
        }
    }
    SDL_RenderPresent(renderer);
}

void draw_barsB(SDL_Renderer *renderer, int arr[], int n, int i, int j) {
    SDL_SetRenderDrawColor(renderer, 153, 196, 210, 0); // Black background
    SDL_RenderClear(renderer);

    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for compared bars
        else {
            int color_value = (arr[k] * 255) / N;
            SDL_SetRenderDrawColor(renderer, color_value, color_value, color_value, 255); // Green for others

        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / N / 3;
        // Set lines to B position
        SDL_Rect bar2 = {k * BAR_WIDTH / 3 + WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_RenderFillRect(renderer, &bar2);

        // GIZMOS
        if (Gizmos) {
            // Sort Lines
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &(bar2));
        }
    }
    SDL_RenderPresent(renderer);
}

void draw_barsC(SDL_Renderer *renderer, int arr[], int n, int i, int j) {
    SDL_SetRenderDrawColor(renderer, 153, 196, 210, 0); // Black background
    SDL_RenderClear(renderer);

    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for compared bars
        else {
            int color_value = (arr[k] * 255) / N;
            SDL_SetRenderDrawColor(renderer, color_value, color_value, color_value, 255); // Green for others

        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / N / 3;
        // Set lines to C position
        SDL_Rect bar3 = {k * BAR_WIDTH / 3, WINDOW_HEIGHT - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_RenderFillRect(renderer, &bar3);

        // GIZMOS
        if (Gizmos) {
            // Sort Lines
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &(bar3));
        }
    }
    SDL_RenderPresent(renderer);
}

void draw_barsD(SDL_Renderer *renderer, int arr[], int n, int i, int j) {
    SDL_SetRenderDrawColor(renderer, 153, 196, 210, 0); // Black background
    SDL_RenderClear(renderer);

    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for compared bars
        else {
            int color_value = (arr[k] * 255) / N;
            SDL_SetRenderDrawColor(renderer, color_value, color_value, color_value, 255); // Green for others

        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / N / 3;
        // Set lines to D position
        SDL_Rect bar4 = {k * BAR_WIDTH / 3 + WINDOW_WIDTH / 2, WINDOW_HEIGHT - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_RenderFillRect(renderer, &bar4);

        // GIZMOS
        if (Gizmos) {
            // Sort Lines
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &(bar4));
        }
    }
    SDL_RenderPresent(renderer);
}

