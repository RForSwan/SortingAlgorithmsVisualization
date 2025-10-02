#include "settings.h"

Inputs *inputs_create()
{
    Inputs *inputs = calloc(1, sizeof(Inputs));

    // Please define here if you want prestated levels for inputs
    inputs->quit    = false;
    inputs->pass    = false;
    inputs->gizmos  = false;
    inputs->mouseX  = 0;
    inputs->mouseY  = 0;
    inputs->clicked = false;

    return inputs;
}

void inputs_destroy(Inputs *inputs)
{
    if(inputs) free(inputs);
}

int inputs_get(App* app, Button *buttons, const unsigned int nb_buttons)
{
    logger_log(app->logger, LOG_LEVEL_INFO, "app_inputs : Reviewing all inputs ");

    Inputs* inputs = app->inputs;
    SDL_Event event;

    while(SDL_PollEvent(&event) != 0)
    {

        if(event.type == SDL_QUIT)
        {
            logger_log(app->logger, LOG_LEVEL_DEBUG, "inputs_get : Quitting button pressed");
            inputs->quit = true;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            logger_log(app->logger, LOG_LEVEL_DEBUG, "inputs_get : Mouse button clicked");
            inputs->clicked = true;
        }
        if(event.type == SDL_KEYDOWN)
        {
            logger_log(app->logger, LOG_LEVEL_DEBUG, "inputs_get : Key pressed [%c]", event.key.keysym.sym);
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                logger_log(app->logger, LOG_LEVEL_INFO, "inputs_get : Initialise quitting sequence");
                inputs->quit = true;
            }
            if(event.key.keysym.sym == SDLK_RETURN)
            {
                inputs->clicked = true;
            }
            if(event.key.keysym.sym == SDLK_g)
            {
                logger_log(app->logger, LOG_LEVEL_INFO, "inputs_get : Switch gizmo on and off");
                inputs->gizmos = !inputs->gizmos;
            }
            if(event.key.keysym.sym == SDLK_p)
            {
                logger_log(app->logger, LOG_LEVEL_INFO, "inputs_get : Increase waiting delay while sorting");
                DELAY_MS += 2;
                logger_log(app->logger, LOG_LEVEL_DEBUG, "inputs_get : Delay now set to [%2dms]", DELAY_MS);
            }
            if(event.key.keysym.sym == SDLK_m)
            {
                logger_log(app->logger, LOG_LEVEL_INFO, "inputs_get : Decrease waiting delay while sorting");
                DELAY_MS -= 2;
                logger_log(app->logger, LOG_LEVEL_DEBUG, "inputs_get : Delay now set to [%2dms]", DELAY_MS);
            }
        }
    }

    // Get mouse position
    SDL_GetMouseState(&app->inputs->mouseX, &app->inputs->mouseY);

    for(int i = 0; i < nb_buttons; i++)
    {
        buttons[i].hovered = visual_isHovered(buttons[i].rect, app->inputs->mouseX, app->inputs->mouseY);
        buttons[i].pressed = buttons[i].hovered && inputs->clicked;

    }
    if(buttons) app->inputs->pass = buttons[0].pressed;
}

int inputs_clear(App* app)
{
    Inputs* inputs = app->inputs;
    inputs->pass = false;
    inputs->clicked = false;
}
