#include "SDL_Master.h"


int main()
{
	Display *display;
	Master *master;

	display = display_init();
	master = init(display);

	update(master);
}
