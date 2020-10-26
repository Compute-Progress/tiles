#include "SDL_Master.h"

void render_button(Master *master, SDL_Rect rect, color_rgba  color)
{
	SDL_SetRenderDrawColor(master->display->renderer, color.bit_data.r,color.bit_data.g,color.bit_data.b, color.bit_data.a);

	SDL_RenderFillRect(master->display->renderer, &rect);
}

//Not needed for this test, but the button should simply change their color instead of calling the rendering functions

void test_button_click(Master *master, button *button)
{
	button->is_click = true;
	// render_button(master, button->hitbox, button->color_default);
}

void test_button_release(Master *master, button *button)
{
	button->is_click = false;
	// render_button(master, button->hitbox, button->color_default);
}
