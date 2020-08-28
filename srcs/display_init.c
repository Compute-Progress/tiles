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

	master = malloc(sizeof(Master));
	master->Grid = malloc(sizeof(screen_div) * (SCREEN_DIVX * SCREEN_DIVY));

	rect.w = WIN_W / SCREEN_DIVX;
	rect.h = WIN_H / SCREEN_DIVY;

	for (int i = 0; i < SCREEN_DIVX * SCREEN_DIVY; i++)
	{
		master->Grid[i].buttons = malloc(sizeof(button) * BUTTON_MAX);
		for (int n = 0; n < BUTTON_MAX; n++)
		{
			rect.x = (i % SCREEN_DIVX) * (WIN_W / SCREEN_DIVX);
			rect.y = (i / SCREEN_DIVY) * (WIN_H / SCREEN_DIVY);
			printf("%d, %d\n", rect.x, rect.y);
			master->Grid[i].buttons[n].hitbox = rect;
			master->Grid[i].buttons[n].is_click = false;
			master->Grid[i].buttons[n].button_click = &test_button_release;
			master->Grid[i].buttons[n].button_release = &test_button_click;
			master->Grid[i].buttons[n].color_default.color = 0xFF0000FF;
			master->Grid[i].buttons[n].color_clicked.color = 0xFF0000FF;
		}
	}
	master->display = display;

	return master;
}

Display *display_init()
{
	Display *display;

	SDL_Init(SDL_INIT_EVERYTHING);
	Uint32 render_flags = SDL_RENDERER_SOFTWARE;

	display = malloc(sizeof(Display));
	//display->spritesheet = malloc(sizeof(SDL_Rect) * ((VAL * VAL) * VAL));

	display->window = SDL_CreateWindow(WIN_NAME, WIN_X, WIN_Y, WIN_W, WIN_H, WIN_FLAGS);
	display->renderer = SDL_CreateRenderer(display->window, -1, render_flags);
	display->state = 1;

	return display;
}
