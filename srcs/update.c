#include "SDL_Master.h"
#include <sys/time.h>

static void get_input(Input *input)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		SDL_GetMouseState(&input->mouse_x, &input->mouse_y);
		if (event.type == SDL_QUIT)
			exit(0);
		//if (MOUSE_IN && event.type == SDL_MOUSEMOTION)
		if (KEY_IN && event.type == SDL_KEYDOWN)
			input->key = event.key.keysym.scancode;
	}
}

void update_buttons(Master *master)
{
	int x, y, n;

	x = master->display->input.mouse_x / (WIN_W / SCREEN_DIVX);
	y = master->display->input.mouse_y / (WIN_H / SCREEN_DIVY);

	n = (y* SCREEN_DIVX) + x;

	if (n >= 0 && n <= 25)
		render_button(master, master->Grid[n].buttons[0].hitbox, master->Grid[n].buttons[0].color_clicked);
/* 	for (int i = 0; i < SCREEN_DIVX * SCREEN_DIVY; i++)
	{
	//printf("Start %d\n", n);
		if (master->Grid[i].buttons[0].is_click)
			render_button(master, master->Grid[i].buttons[0].hitbox, master->Grid[i].buttons[0].color_clicked);
		else
			render_button(master, master->Grid[i].buttons[0].hitbox, master->Grid[i].buttons[0].color_default);
		master->Grid[i].buttons[0].is_click = false;
	} */
//	printf("End \n");
}

void update(Master *master)
{
	struct timeval time, current;
	long elapsed;

	while (master->display->state)
	{
		gettimeofday(&time, NULL);

		get_input(&master->display->input);
		update_buttons(master);

		SDL_SetRenderDrawColor(master->display->renderer, 0,0,0,255);
		SDL_RenderPresent(master->display->renderer);
		SDL_RenderClear(master->display->renderer);

		gettimeofday(&current, NULL);
		elapsed = ((current.tv_sec - time.tv_sec) * 1000 + ((current.tv_sec - time.tv_sec) / 1000));

		if (elapsed < FRAME_DELAY)
			SDL_Delay(FRAME_DELAY - elapsed);
	}
	annhilate(master->display);
	exit(0);
}
