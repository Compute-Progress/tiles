#include "SDL_Master.h"

void render_button(Master *master, SDL_Rect rect, color_rgba  color)
{
	SDL_SetRenderDrawColor(master->display->renderer, color.bit_data.r,color.bit_data.g,color.bit_data.b, color.bit_data.a);

	//printf("Color rgba %xd %xd %xd %xd\n", color.bit_data.r,color.bit_data.g,color.bit_data.b, color.bit_data.a);

	SDL_RenderFillRect(master->display->renderer, &rect);
}

void test_button_click(Master *master, button *button)
{
	//Uint32 color;
	printf("Button clicked\n");
	button->is_click = true;
	//render_button(master, button->hitbox, button->color_default);
}

void test_button_release(Master *master, button *button)
{
	printf("Button Released\n");
	button->is_click = false;

	//render_button(master, button->hitbox, button->color_default);
}
