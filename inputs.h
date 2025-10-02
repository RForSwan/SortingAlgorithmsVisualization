#ifndef _INPUTS_H_
#define _INPUTS_H_

typedef struct App_s App;
typedef struct Button_s Button;

typedef struct Inputs_s{
    bool quit;
    bool pass;

    bool gizmos;

    int mouseX;
    int mouseY;
    bool clicked;
}Inputs;

Inputs *inputs_create();
void inputs_destroy(Inputs *inputs);

int inputs_get(App *app, Button *buttons, const unsigned int nb_buttons);
int inputs_clear(App *app);

#endif