#include "settings.h"

///// SUB FUNCTIONS /////

Colors *visual_createColorSet()
{
    Colors *colors = calloc(1, sizeof(Colors));
    ///// COLOR SET
    //// Light mode
    // Background
    colors->Background_top_LM = (SDL_Color){.r = 116, .g = 171, .b = 226, .a = 255};
    colors->Background_bot_LM = (SDL_Color){.r =  85, .g =  99, .b = 222, .a = 255};
    // Button
    colors->Button_top_LM = (SDL_Color){.r =  76, .g = 209, .b =  55, .a = 255};
    colors->Button_bot_LM = (SDL_Color){.r =  56, .g = 173, .b =  40, .a = 255};
    // Button hovered
    colors->ButtonHovered_top_LM = (SDL_Color){.r =  40, .g = 167, .b =  69, .a = 255};
    colors->ButtonHovered_bot_LM = (SDL_Color){.r =  30, .g = 120, .b =  50, .a = 255};
    /// Dark mode
    // Background
    colors->Background_top_DM = (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255};
    colors->Background_bot_DM = (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255};
    // Button
    colors->Button_top_DM = (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255};
    colors->Button_bot_DM = (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255};
    // Button hovered
    colors->ButtonHovered_top_DM = (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255};
    colors->ButtonHovered_bot_DM = (SDL_Color){.r = 0, .g = 0, .b = 0, .a = 255};

    return colors;
}

void visual_destroyColorSet(Colors *colors)
{
    if(colors) free(colors);
}

//void draw_gradient_button(SDL_Renderer *renderer, SDL_Rect button, SDL_Color top, SDL_Color bottom, int radius) {
//    for (int y = 0; y < button.h; y++) {
//        float t = (float)y / (float)(button.h - 1);
//
//        Uint8 r = (Uint8)((1 - t) * top.r + t * bottom.r);
//        Uint8 g = (Uint8)((1 - t) * top.g + t * bottom.g);
//        Uint8 b = (Uint8)((1 - t) * top.b + t * bottom.b);
//
//        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
//        SDL_RenderDrawLine(renderer, button.x, button.y + y, button.x + button.w, button.y + y);
//    }
//
//    // Draw a white rectangle border
//    rectangleRGBA(renderer, button.x, button.y, button.x + button.w, button.y + button.h, 255, 255, 255, 255);
//}
//
//
//void draw_button(SDL_Renderer *renderer, SDL_Rect button, const char *label, TTF_Font *font, int hovered) {
//    SDL_Color top, bottom;    // Button
//    if (hovered) {
//        // Hover
//        top = (SDL_Color){40, 167, 69, 255};   // #28A745
//        bottom = (SDL_Color){30, 120, 50, 255};
//    } else {
//        // Normal
//        top = (SDL_Color){76, 209, 55, 255};   // #4CD137
//        bottom = (SDL_Color){56, 173, 40, 255};
//    }
//
//    draw_gradient_button(renderer, button, top, bottom, 12);
//
//    // Text
//    SDL_Color textColor = {255, 255, 255, 255};
//    SDL_Surface *textSurface = TTF_RenderText_Blended(font, label, textColor);
//    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
//    int textW, textH;
//    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
//    SDL_Rect textRect = { button.x + (button.w - textW) / 2, button.y + (button.h - textH) / 2, textW, textH };
//    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
//    SDL_FreeSurface(textSurface);
//    SDL_DestroyTexture(textTexture);
//
//
//    // SIDE BUTTONS
//    for (int i = 0; i < 4; ++i) {
//        SDL_Rect rect = {buttons[i].x, buttons[i].y, buttons[i].w, buttons[i].h};
//
//        SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255); // Button color
//        SDL_RenderFillRect(renderer, &rect);
//
//        // Draw label (simple version)
//        SDL_Color textColor2 = {255, 255, 255, 255};
//        SDL_Surface* textSurface2 = TTF_RenderText_Solid(font, buttons[i].label, textColor2);
//        SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
//        int tw, th;
//        SDL_QueryTexture(textTexture2, NULL, NULL, &tw, &th);
//        SDL_Rect textRect2 = {rect.x + (rect.w-tw)/2, rect.y + (rect.h-th)/2, tw, th};
//        SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);
//        SDL_FreeSurface(textSurface2);
//        SDL_DestroyTexture(textTexture2);
//    }
//}


void draw_gradient_background(App *app,
                              SDL_Color top, SDL_Color bottom) {
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        // linear interpolation of top and bottom
        float t = (float)y / (float)(WINDOW_HEIGHT - 1);

        Uint8 r = (Uint8)((1 - t) * top.r + t * bottom.r);
        Uint8 g = (Uint8)((1 - t) * top.g + t * bottom.g);
        Uint8 b = (Uint8)((1 - t) * top.b + t * bottom.b);

        SDL_SetRenderDrawColor(app->renderer, r, g, b, 255);
        SDL_RenderDrawLine(app->renderer, 0, y, WINDOW_WIDTH, y);
    }
}

void visual_drawButton(App *app, Button button)
{
    ///// DRAW BUTTON /////
    SDL_Color top, bottom;    // Button
    if (button.hovered) {
        // Hover
        top = (SDL_Color){40, 167, 69, 255};   // #28A745
        bottom = (SDL_Color){30, 120, 50, 255};
    } else {
        // Normal
        top = (SDL_Color){76, 209, 55, 255};   // #4CD137
        bottom = (SDL_Color){56, 173, 40, 255};
    }

    for(int i = 0; i < button.rect.h; i++)
    {
        float t = (float)i / (float)(button.rect.h - 1);

        Uint8 r = (Uint8)((1 - t) * (float)top.r + t * (float)bottom.r);
        Uint8 g = (Uint8)((1 - t) * (float)top.g + t * (float)bottom.g);
        Uint8 b = (Uint8)((1 - t) * (float)top.b + t * (float)bottom.b);

        SDL_SetRenderDrawColor(app->renderer, r, g, b, 255);
        SDL_RenderDrawLine(app->renderer, button.rect.x, button.rect.y + i, button.rect.x + button.rect.w, button.rect.y + i);
    }

    // Draw a white rectangle border
    rectangleRGBA(app->renderer, button.rect.x, button.rect.y, button.rect.x + button.rect.w, button.rect.y + button.rect.h, 255, 255, 255, 255);

    ///// DRAW TEXT /////
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Blended(app->font, button.label, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(app->renderer, textSurface);

    int textW, textH;

    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
    SDL_Rect textRect = { button.rect.x + (button.rect.w - textW) / 2, button.rect.y + (button.rect.h - textH) / 2, textW, textH };
    SDL_RenderCopy(app->renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

}

///// FUNCTIONS /////

void visual_drawSettingsScreen(App *app, Button *buttons)
{
    /*           Sorting Algorithms Visualizer
     *
     *   [S1]                      ----------O-----   < Sliding bar choose the number of elements inside the array (10-100 ?)
     *   [S2]
     *   [S3]                       [DATA TYPE]       < Selection menu to choose the data type
     *   [S4]
     *                              [RANDOMNESS TYPE] < Select the type of mixing for the array
     *                  [PLAY]
     */

    ///// BACKGROUND /////

    draw_gradient_background(app, app->colorSet->Background_top_LM, app->colorSet->Background_bot_LM);

    ///// BUTTONS /////

    for(int i = 0; i < 5; i++)
    {
        visual_drawButton(app, buttons[i]);
    }

    ///// GIZMOS /////
    if (app->inputs->gizmos) {
        // Vertical Middle line
        SDL_SetRenderDrawColor(app->renderer, 255, 255, 0, 255); // Yellow
        SDL_RenderDrawLine(app->renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
        // Horizontal Middle line
        SDL_RenderDrawLine(app->renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
    }
}

void visual_drawVisualizationScreen(App *app, Button *buttons)
{
    ///// BACKGROUND /////

    draw_gradient_background(app, app->colorSet->Background_top_LM, app->colorSet->Background_bot_LM);

    ///// Top stats bar background /////
    SDL_mutexP(app->rendererUse);
    SDL_SetRenderDrawColor(app->renderer, 30, 30, 30, 255); // dark bar
    SDL_Rect topRect = {.x = 0, .y = 0, .w = WINDOW_WIDTH, .h = TOP_BAR_HEIGHT};
    SDL_RenderFillRect(app->renderer, &topRect);
    SDL_mutexV(app->rendererUse);

    // Prepare stat strings
    char left_stats[128];
    char right_stats[128];
    double elapsed_timeA = 0.0, elapsed_timeB = 0.0;
    Uint64 startA = 0, startB = 0;
    bool runningA = false, runningB = false;

    if (app->sortTime_mutex) SDL_mutexP(app->sortTime_mutex);
    elapsed_timeA = app->SortA_time;
    elapsed_timeB = app->SortB_time;
    startA = app->SortA_ticks_start;
    startB = app->SortB_ticks_start;
    runningA = app->SortA_running;
    runningB = app->SortB_running;
    if (app->sortTime_mutex) SDL_mutexV(app->sortTime_mutex);

    if (runningA) {
        Uint64 now = SDL_GetPerformanceCounter();
        elapsed_timeA = (double)(now - startA) * 1.0 / (double)SDL_GetPerformanceFrequency();
    }
    if (runningB) {
        Uint64 now = SDL_GetPerformanceCounter();
        elapsed_timeB = (double)(now - startB) * 1.0 / (double)SDL_GetPerformanceFrequency();
    }

    // Safe throughput calculation
    const double eps = 1e-9;
    double elems_per_secA = 0.0, elems_per_secB = 0.0;
    if (elapsed_timeA > eps) elems_per_secA = (double)app->selected_nb_elements / elapsed_timeA;
    if (elapsed_timeB > eps) elems_per_secB = (double)app->selected_nb_elements / elapsed_timeB;

    // Human readable status
    char statusA[16] = "IDLE";
    char statusB[16] = "IDLE";
    if (runningA) strncpy(statusA, "RUNNING", sizeof(statusA));
    else if (app->SortA_time > 0.0) strncpy(statusA, "FINISHED", sizeof(statusA));
    if (runningB) strncpy(statusB, "RUNNING", sizeof(statusB));
    else if (app->SortB_time > 0.0) strncpy(statusB, "FINISHED", sizeof(statusB));

    // Left: per-sort info (count / status / time / throughput)
    // Example: "A: RUNNING | T=0.123s | E/s=258.1 ||| B: FINISHED | T=1.234s | E/s=26.0"
    snprintf(left_stats, sizeof(left_stats),
             "A: %s  |  T=%.3fs  |  E/s=%.1f   |   |   |   B: %s  |  T=%.3fs  |  E/s=%.1f",
             statusA, elapsed_timeA, elems_per_secA,
             statusB, elapsed_timeB, elems_per_secB);

    // Right: runtime toggles and simple metrics
    snprintf(right_stats, sizeof(right_stats),
             "Delay=%dms  Gizmos=%s  Elements=%d",
             DELAY_MS,
             app->inputs->gizmos ? "ON" : "OFF",
             app->selected_nb_elements);

    // // Example info: number of elements and sorting status on left, delay and gizmo on right
    // snprintf(left_stats, sizeof(left_stats), "Sort A: QT=%d - TIME=%.1lfS ||| Sort B: QT=%d - TIME=%.1lfS", app->selected_nb_elements, elapsed_timeA, app->selected_nb_elements, elapsed_timeB, app->selected_nb_elements);
    // snprintf(right_stats, sizeof(right_stats), "Delay=%d ms   Gizmos=%s   ThreadsRun=%s", DELAY_MS,
    //          app->inputs->gizmos ? "ON" : "OFF", app->threadsRun ? "YES" : "NO");

    // Render left stats
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *surf_left = TTF_RenderText_Blended(app->font, left_stats, textColor);
    if (surf_left) {
        SDL_Texture *tex_left;
        SDL_mutexP(app->rendererUse);
        tex_left = SDL_CreateTextureFromSurface(app->renderer, surf_left);
        SDL_mutexV(app->rendererUse);
        if (tex_left) {
            int tw, th;
            SDL_QueryTexture(tex_left, NULL, NULL, &tw, &th);
            SDL_Rect dest_left = {.x = 10, .y = (TOP_BAR_HEIGHT - th) / 2, .w = tw, .h = th};
            SDL_mutexP(app->rendererUse);
            SDL_RenderCopy(app->renderer, tex_left, NULL, &dest_left);
            SDL_mutexV(app->rendererUse);
            SDL_DestroyTexture(tex_left);
        }
        //SDL_FreeSurface(surf_left);
    }

    // Render right stats
    SDL_Surface *surf_right = TTF_RenderText_Blended(app->font, right_stats, textColor);
    if (surf_right) {
        SDL_Texture *tex_right;
        SDL_mutexP(app->rendererUse);
        tex_right = SDL_CreateTextureFromSurface(app->renderer, surf_right);
        SDL_mutexV(app->rendererUse);
        if (tex_right) {
            int tw, th;
            SDL_QueryTexture(tex_right, NULL, NULL, &tw, &th);
            SDL_Rect dest_right = {.x = WINDOW_WIDTH - tw - 10, .y = (TOP_BAR_HEIGHT - th) / 2, .w = tw, .h = th};
            SDL_mutexP(app->rendererUse);
            SDL_RenderCopy(app->renderer, tex_right, NULL, &dest_right);
            SDL_mutexV(app->rendererUse);
            SDL_DestroyTexture(tex_right);
        }
        SDL_FreeSurface(surf_right);
    }

    // Draw dividing line under top bar
    SDL_mutexP(app->rendererUse);
    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 100);
    SDL_RenderDrawLine(app->renderer, 0, TOP_BAR_HEIGHT, WINDOW_WIDTH, TOP_BAR_HEIGHT);
    SDL_mutexV(app->rendererUse);

    // Call draws for left/right sort areas (they handle NULL arr)
    draw_barsA(app, NULL, app->selected_nb_elements, -1, -1);
    draw_barsB(app, NULL, app->selected_nb_elements, -1, -1);

    ///// GIZMOS /////
    if (app->inputs->gizmos) {
        // Vertical Middle line
        SDL_SetRenderDrawColor(app->renderer, 255, 255, 0, 255); // Yellow
        SDL_RenderDrawLine(app->renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 11, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
        // Horizontal Lines
        SDL_RenderDrawLine(app->renderer, 0, WINDOW_HEIGHT / 11, WINDOW_WIDTH, WINDOW_HEIGHT / 11);
        SDL_RenderDrawLine(app->renderer, 0, (6 * WINDOW_HEIGHT) / 11, WINDOW_WIDTH, (6 * WINDOW_HEIGHT) / 11);
    }
    // Optional gizmos lines (below top bar)
    if (app->inputs->gizmos) {
        SDL_mutexP(app->rendererUse);
        SDL_SetRenderDrawColor(app->renderer, 255, 255, 0, 255);
        SDL_RenderDrawLine(app->renderer, WINDOW_WIDTH / 2, TOP_BAR_HEIGHT, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
        SDL_RenderDrawLine(app->renderer, 0, TOP_BAR_HEIGHT, WINDOW_WIDTH, TOP_BAR_HEIGHT);
        SDL_mutexV(app->rendererUse);
    }
}

//
//void draw_title_screen(App* app, SDL_Renderer *renderer, TTF_Font *font) {
//    SDL_Color top = {116, 171, 226, 255};
//    SDL_Color bottom = {85, 99, 222, 255};
//    draw_gradient_background(renderer, top, bottom);
//
//
//    // Button position
//    SDL_Rect button = {(WINDOW_WIDTH - BUTTON_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_HEIGHT) - MARGIN, BUTTON_WIDTH, BUTTON_HEIGHT};
//
//    // Get mouse position
//    int mx, my;
//    SDL_GetMouseState(&mx, &my);
//    int hovered = play_clicked(mx, my);
//
//    // Draw with over effect
//    draw_button(renderer, button, "Play", font, hovered);
//
//    // GIZMOS
//    if (app->inputs->gizmos) {
//        // Vertical Middle line
//        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
//        SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
//        // Horizontal Middle line
//        SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
//    }
//
//    SDL_RenderPresent(renderer);
//}

void visual_replay_sorted(App *app, int arr[], int n, void (*draw_func)(App*, int*, int, int, int))
{
    if (!app || !arr || n <= 0 || !draw_func) return;

    Pair *pairs = calloc(n, sizeof(Pair));
    if (!pairs) return;

    for (int i = 0; i < n; ++i) {
        pairs[i].value = arr[i];
        pairs[i].idx = i;
    }

    qsort(pairs, n, sizeof(Pair), pair_cmp);

    for (int k = 0; k < n && app->threadsRun; ++k) {
        int idx = pairs[k].idx;
        draw_func(app, arr, n, idx, -1); // highlight single bar
        SDL_Delay(DELAY_MS);
    }

    free(pairs);
}


// Check for mouse click in button
bool visual_isHovered(SDL_Rect button_r, int x, int y)
{
    int bottom = button_r.y;
    int top    = bottom + button_r.h;
    int right  = button_r.x;
    int left  = right + button_r.w;
    return x < left && x > right && y < top && y > bottom ;
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


/*void draw_barsA(App* app, int arr[], int n, int i, int j) {
//    SDL_SetRenderDrawColor(renderer, 153, 196, 210, 0); // Black background
//    SDL_RenderClear(renderer);
    SDL_mutexP(app->rendererUse);
    SDL_SetRenderDrawColor(app->renderer, 153, 196, 210, 255);
    SDL_RenderFillRect(app->renderer,&(SDL_Rect){.x = 0, .y = WINDOW_HEIGHT / 11, .w = WINDOW_WIDTH/2, .h = (6 * WINDOW_HEIGHT) / 11});
    SDL_mutexV(app->rendererUse);
    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
        {
            SDL_mutexP(app->rendererUse);
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255); // Red for compared bars
            SDL_mutexV(app->rendererUse);
        }
        else
        {
            int color_value = (arr[k] * 255) / N;
            SDL_mutexP(app->rendererUse);
            SDL_SetRenderDrawColor(app->renderer, color_value, color_value, color_value, 255); // Green for others
            SDL_mutexV(app->rendererUse);
        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / N / 3;
        // Set lines to A position
        SDL_Rect bar = {k * BAR_WIDTH / 3, WINDOW_HEIGHT / 2 - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_mutexP(app->rendererUse);
        SDL_RenderFillRect(app->renderer, &bar);
        SDL_mutexV(app->rendererUse);

        // GIZMOS
        // GIZMOS
//        if (app->inputs->gizmos) {
//            SDL_SetRenderDrawColor(app->renderer, 0, 255, 0, 255); // Green
//            // Sort A
//            SDL_RenderDrawRect(app->renderer, &(SDL_Rect){0, 0, WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});
//            // Sort B
//            SDL_RenderDrawRect(app->renderer, &(SDL_Rect){WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});
//            // Sort C
//            SDL_RenderDrawRect(app->renderer, &(SDL_Rect){0, (WINDOW_HEIGHT / 2), WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});
//            // Sort D
//            SDL_RenderDrawRect(app->renderer, &(SDL_Rect){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 2)});
//
//
//            // Vertical Middle line
//            SDL_SetRenderDrawColor(app->renderer, 255, 255, 0, 255); // Yellow
//            SDL_RenderDrawLine(app->renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
//            // Horizontal Middle line
//            SDL_RenderDrawLine(app->renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
//
//            // Sorts Lines
//            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255); // Red
//            SDL_RenderDrawRect(app->renderer, &bar);
//        }
    }
//    SDL_RenderPresent(renderer);
}*/

void draw_barsA(App* app, int arr[], int n, int i, int j)
{
    if (!app) return;

    static int *saved_arr = NULL;
    static int saved_n = 0;

    if (arr && n > 0) {
        // update saved
        int *tmp = realloc(saved_arr, sizeof(int) * n);
        if (tmp) {
            saved_arr = tmp;
            memcpy(saved_arr, arr, sizeof(int) * n);
            saved_n = n;
        } else {
            // realloc failed, keep old saved_arr
        }
    } else {
        arr = saved_arr;
        n = saved_n;
    }

    if (!arr || n <= 0) return; // nothind to draw

    const int area_x = 0;
    const int area_y = TOP_BAR_HEIGHT;
    const int area_w = WINDOW_WIDTH / 2;
    const int area_h = WINDOW_HEIGHT - TOP_BAR_HEIGHT;

    // Clear left area background
    SDL_mutexP(app->rendererUse);
    SDL_SetRenderDrawColor(app->renderer, 153, 196, 210, 255);
    SDL_RenderFillRect(app->renderer, &(SDL_Rect){.x = area_x, .y = area_y, .w = area_w, .h = area_h});
    SDL_mutexV(app->rendererUse);

    // Compute per-bar geometry
    int slot_w = area_w / n;
    int bar_w = slot_w > 1 ? slot_w - 1 : 1;

    for (int k = 0; k < n; k++) {
        // choose color
        if (k == i || k == j) {
            SDL_mutexP(app->rendererUse);
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255); // compared bars red
            sound_play_tone_from_value(k, app->selected_nb_elements, 150, 96);
            SDL_mutexV(app->rendererUse);
        } else {
            int color_value = (arr[k] * 255) / N;
            if (color_value < 0) color_value = 0;
            if (color_value > 255) color_value = 255;
            SDL_mutexP(app->rendererUse);
            SDL_SetRenderDrawColor(app->renderer, color_value, color_value, color_value, 255);
            SDL_mutexV(app->rendererUse);
        }

        // height and position (bottom-aligned inside area)
        int bar_height = (arr[k] * area_h) / N;
        if (bar_height < 1) bar_height = 1;
        int bx = area_x + k * slot_w;
        int by = area_y + (area_h - bar_height);

        SDL_Rect bar = {.x = bx, .y = by, .w = bar_w, .h = bar_height};
        SDL_mutexP(app->rendererUse);
        SDL_RenderFillRect(app->renderer, &bar);
        SDL_mutexV(app->rendererUse);

        if (app->inputs && app->inputs->gizmos) {
            SDL_mutexP(app->rendererUse);
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(app->renderer, &bar);
            SDL_mutexV(app->rendererUse);
        }
    }
}
void draw_barsB(App* app, int arr[], int n, int i, int j)
{
    if (!app) return;

    static int *saved_arr = NULL;
    static int saved_n = 0;

    if (arr && n > 0) {
        // update saved
        int *tmp = realloc(saved_arr, sizeof(int) * n);
        if (tmp) {
            saved_arr = tmp;
            memcpy(saved_arr, arr, sizeof(int) * n);
            saved_n = n;
        } else {
            // realloc failed, keep old saved_arr
        }
    } else {
        arr = saved_arr;
        n = saved_n;
    }

    if (!arr || n <= 0) return; // nothind to draw


    const int area_x = WINDOW_WIDTH / 2;
    const int area_y = TOP_BAR_HEIGHT;
    const int area_w = WINDOW_WIDTH / 2;
    const int area_h = WINDOW_HEIGHT - TOP_BAR_HEIGHT;

    // Clear right area background
    SDL_mutexP(app->rendererUse);
    SDL_SetRenderDrawColor(app->renderer, 153, 196, 210, 255);
    SDL_RenderFillRect(app->renderer, &(SDL_Rect){.x = area_x, .y = area_y, .w = area_w, .h = area_h});
    SDL_mutexV(app->rendererUse);


    int slot_w = area_w / n;
    int bar_w = slot_w > 1 ? slot_w - 1 : 1;

    for (int k = 0; k < n; k++) {
        // choose color
        if (k == i || k == j) {
            SDL_mutexP(app->rendererUse);
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255); // compared bars red
            sound_play_tone_from_value(k, app->selected_nb_elements, 150, 96);
            SDL_mutexV(app->rendererUse);
        } else {
            int color_value = (arr[k] * 255) / N;
            if (color_value < 0) color_value = 0;
            if (color_value > 255) color_value = 255;
            SDL_mutexP(app->rendererUse);
            SDL_SetRenderDrawColor(app->renderer, color_value, color_value, color_value, 255);
            SDL_mutexV(app->rendererUse);
        }

        int bar_height = (arr[k] * area_h) / N;
        if (bar_height < 1) bar_height = 1;
        int bx = area_x + k * slot_w;
        int by = area_y + (area_h - bar_height);

        SDL_Rect bar2 = {.x = bx, .y = by, .w = bar_w, .h = bar_height};
        SDL_mutexP(app->rendererUse);
        SDL_RenderFillRect(app->renderer, &bar2);
        SDL_mutexV(app->rendererUse);

        if (app->inputs && app->inputs->gizmos) {
            SDL_mutexP(app->rendererUse);
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(app->renderer, &bar2);
            SDL_mutexV(app->rendererUse);
        }
    }

}
/*
void draw_barsB(App* app, int arr[], int n, int i, int j) {
//    SDL_SetRenderDrawColor(renderer, 153, 196, 210, 0); // Black background
//    SDL_RenderClear(renderer);

    SDL_mutexP(app->rendererUse);
    SDL_SetRenderDrawColor(app->renderer, 153, 196, 210, 255);
    SDL_RenderFillRect(app->renderer,&(SDL_Rect){.x = WINDOW_WIDTH/2, .y = WINDOW_HEIGHT / 11, .w = WINDOW_WIDTH/2, .h = (6 * WINDOW_HEIGHT) / 11});
    SDL_mutexV(app->rendererUse);
    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
        {
            SDL_mutexP(app->rendererUse);
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255); // Red for compared bars
            SDL_mutexV(app->rendererUse);
        }
        else {
            int color_value = (arr[k] * 255) / N;
            SDL_mutexP(app->rendererUse);
            SDL_SetRenderDrawColor(app->renderer, color_value, color_value, color_value, 255); // Green for others
            SDL_mutexV(app->rendererUse);
        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / N / 3;
        // Set lines to B position
        SDL_Rect bar2 = {k * BAR_WIDTH / 3 + WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_mutexP(app->rendererUse);
        SDL_RenderFillRect(app->renderer, &bar2);
        SDL_mutexV(app->rendererUse);

//        // GIZMOS
//        if (app->inputs->gizmos) {
//            // Sort Lines
//            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
//            SDL_RenderDrawRect(app->renderer, &(bar2));
//        }
    }
//    SDL_RenderPresent(renderer);
}

*/
void draw_barsC(App* app, int arr[], int n, int i, int j) {
    SDL_SetRenderDrawColor(app->renderer, 153, 196, 210, 0); // Black background
    //SDL_RenderClear(app->renderer);

    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255); // Red for compared bars
        else {
            int color_value = (arr[k] * 255) / app->selected_nb_elements;
            SDL_SetRenderDrawColor(app->renderer, color_value, color_value, color_value, 255); // Green for others

        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / app->selected_nb_elements / 3;
        // Set lines to C position
        SDL_Rect bar3 = {k * BAR_WIDTH / 3, WINDOW_HEIGHT - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_RenderFillRect(app->renderer, &bar3);

        // GIZMOS
        if (app->inputs->gizmos) {
            // Sort Lines
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(app->renderer, &(bar3));
        }
    }
//    SDL_RenderPresent(renderer);
}

void draw_barsD(App* app, int arr[], int n, int i, int j) {
    SDL_SetRenderDrawColor(app->renderer, 153, 196, 210, 0); // Black background
    //SDL_RenderClear(app->renderer);

    // Draw lines
    for (int k = 0; k < n; k++) {
        if (k == i || k == j)
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255); // Red for compared bars
        else {
            int color_value = (arr[k] * 255) / app->selected_nb_elements;
            SDL_SetRenderDrawColor(app->renderer, color_value, color_value, color_value, 255); // Green for others

        }

        // Height proportional to value
        int bar_height = (arr[k] * WINDOW_HEIGHT) / app->selected_nb_elements
        / 3;
        // Set lines to D position
        SDL_Rect bar4 = {k * BAR_WIDTH / 3 + WINDOW_WIDTH / 2, WINDOW_HEIGHT - bar_height, (BAR_WIDTH - 1) / 3, bar_height};
        SDL_RenderFillRect(app->renderer, &bar4);

        // GIZMOS
        if (app->inputs->gizmos) {
            // Sort Lines
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(app->renderer, &(bar4));
        }
    }
//    SDL_RenderPresent(renderer);
}

