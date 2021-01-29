#include "SDL_Master.h"

void annhilate(Display *display)
{
	SDL_DestroyRenderer(display->renderer);
	SDL_DestroyWindow(display->window);
	SDL_Quit();
}

Master *init(Display *display)
{
	Master *master;
	SDL_Rect rect;

	master = calloc(1, sizeof(Master));
	master->buttons = malloc(sizeof(button) * (3));
    master->b_total = 3;

    master->buttons[0].hitbox.x = WIN_W / 2;
    master->buttons[0].hitbox.y = WIN_H / 4;
    master->buttons[0].hitbox.w = 50;
    master->buttons[0].hitbox.h = 30;
    master->buttons[0].index = 0;
    master->buttons[0].color_default.color = 0x0000FFFF;
    master->buttons[0].color_clicked.color = 0xFF0000FF;

    master->buttons[1].hitbox.y = (WIN_H / 4) * 2;
    master->buttons[1].hitbox.x = WIN_W / 2;
    master->buttons[1].hitbox.w = 50;
    master->buttons[1].hitbox.h = 30;
    master->buttons[1].index = 1;
    master->buttons[1].color_default.color = 0x0000FFFF;
    master->buttons[1].color_clicked.color = 0xFF0000FF;

    master->buttons[2].hitbox.x = WIN_W / 2;
    master->buttons[2].hitbox.y = (WIN_H / 4) * 3;
    master->buttons[2].hitbox.w = 50;
    master->buttons[2].hitbox.h = 30;
    master->buttons[2].index = 2;
    master->buttons[2].color_default.color = 0x0000FFFF;
    master->buttons[2].color_clicked.color = 0xFF0000FF;

	
	master->display = display;
    master->display->input.index = 0;
    master->display->input.controller = NULL;
    SDL_Log("Controllers %d\n", SDL_NumJoysticks());

    

    if (SDL_NumJoysticks() == 1)
    {
        SDL_Log("Controller initalized");
        master->display->input.controller = SDL_GameControllerOpen(0);
    }
    else
        SDL_Log("No controller found");

	return master;
}

Display *display_init()
{
	Display *display;

	SDL_Init(SDL_INIT_EVERYTHING);
	Uint32 render_flags = SDL_RENDERER_SOFTWARE;

	display = malloc(sizeof(Display));
	display->window = SDL_CreateWindow(WIN_NAME, WIN_X, WIN_Y, WIN_W, WIN_H, WIN_FLAGS);
	display->renderer = SDL_CreateRenderer(display->window, -1, render_flags);
	display->state = 1;

	return display;
}
