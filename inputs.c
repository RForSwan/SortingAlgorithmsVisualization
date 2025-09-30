#include "settings.h"

Inputs *inputs_create()
{
    Inputs *inputs = calloc(1, sizeof(Inputs));

    // Please define here if you want prestated levels for inputs

    return inputs;
}

int inputs_get(App* app)
{
    logger_log(app->logger, LOG_LEVEL_INFO, "app_inputs : Reviewing all inputs ");

    SDL_Event event;

    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            app->inputs->quit = true;
        }

        if(event.type == SDLK_g)
        {
            app->inputs->gizmos = !app->inputs->gizmos;
        }

    }

    // Get mouse position
    SDL_GetMouseState(&app->inputs->mouseX, &app->inputs->mouseY);
}

int inputs_clear(App* app)
{
    Inputs* inputs = app->inputs;
    inputs->pass = false;
}