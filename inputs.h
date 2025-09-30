#ifndef _INPUTS_H_
#define _INPUTS_H_

typedef struct App_s App;

typedef struct Inputs_s{
    bool quit;
    bool pass;

    bool gizmos;

    int mouseX;
    int mouseY;
}Inputs;

Inputs *inputs_create();

int inputs_get(App *app);
int inputs_clear(App *app);

#endif