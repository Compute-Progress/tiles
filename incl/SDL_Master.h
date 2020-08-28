#ifndef SDL_MASTER_H
# define SDL_MASTER_H
# include <SDL2/SDL.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>

# define WIN_NAME "Tiles"
# define WIN_H 1000
# define WIN_W 1000
# define WIN_Y SDL_WINDOWPOS_CENTERED
# define WIN_X SDL_WINDOWPOS_CENTERED
# define WIN_FLAGS 0

# define MOUSE_IN 1
# define KEY_IN 0

# define TILE_W 0
# define TILE_H 0

# define BUTTON_MAX 1
# define SCREEN_DIVX 5 /* It is best to have divisions per w and h in case the screen is not square, though it may not matter*/
# define SCREEN_DIVY 5

# define FRAME_DELAY 0
# define ENDGAME 0
# define VAL 0


struct s_master;
typedef struct s_master Master;

typedef void * (*func)(Master *);

typedef union	u_color_rgba
{
	Uint32 color;
	struct
	{
		Uint8 r;
		Uint8 g;
		Uint8 b;
		Uint8 a;
	}		bit_data;
}			color_rgba;

typedef struct	s_input
{
	SDL_Scancode key;

	int 		mouse_x;
	int 		mouse_y;
}				Input;

typedef struct s_display
{
	SDL_Renderer *renderer;
	SDL_Window	*window;
	SDL_Rect	*spritesheet;
	SDL_Texture	*tex;

	Input		input;
	int			state;
}				Display;

typedef struct s_button
{
	SDL_Rect hitbox;
	SDL_Texture *tex;

	color_rgba color_clicked;
	color_rgba color_default;

	bool is_click;

	func button_click;
	func button_release;
}			button;

typedef struct
{
	button *buttons;
	int max;
	int current;
}		screen_div;

typedef struct s_master
{
	Display *display;
	screen_div *Grid;
}				Master;

/* File : display_init.c */
Display	*display_init();
void	annhilate(Display *display);

/* File : reference_texture.c */
void	ref_texture(SDL_Rect *ref, int width, int length);

/*File update.c */
void	update(Display *display);

void test_button_release(Master *master, button *button);
void test_button_click(Master *master, button *button);
Master *init(Display *display);
void render_button(Master *master, SDL_Rect rect, color_rgba  color);
#endif
