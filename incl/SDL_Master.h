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


typedef enum Button_Mask
{
    //Rename hthese to names with less conflicts probability
	DIR_NONE	= 0b000000000000000,
	A	        = 0b000000000000001,
	DIR_RIGHT	= 0b000000000000010,
	DIR_DOWN	= 0b000000000000100,
	DIR_UP		= 0b000000000001000,
	TRIGG_L		= 0b000000000100000,
	TRIGG_R		= 0b000000001000000,
	BUTTON_L	= 0b000000010000000,
	BUTTON_R	= 0b000000100000000,
	DIR_LEFT    = 0b000001000000000,
	B		    = 0b000010000000000,
	Y		    = 0b000100000000000,
	X		    = 0b001000000000000,
	SELECT		= 0b010000000000000,
	START		= 0b100000000000000,
}	Button_Mask;
typedef struct	s_input
{
	SDL_Point	prim_click_pos;
	SDL_bool	prim_down;

	SDL_Point	sec_click_pos;
	// If secondary button is still down after iterating through all the enemies,
	// it means that none of them were Glory kills and to the user meant to
	// jump.
	SDL_bool	sec_down;

	// This will be used for going LEFT, RIGHT, DOWN, UP in menu items
	Button_Mask	b_mask;
    SDL_GameController *controller;
    bool        mouse;
    int         index;
    int         mask;
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
    int         index;
	SDL_Rect hitbox;
	SDL_Texture *tex;

	color_rgba color_clicked;
	color_rgba color_default;

}			button;

typedef struct
{
	button *buttons;
	int max;
	int current;
}		screen_div;
// The primary click can also be used to

// Primary click controls Fire and Switch Weapons
// If they get added it will also control special, Flame Thrower, Chainsaw

// Secondary click controls jump movement and Glory Kills
// If it gets added will have velocity for dash direction.
typedef struct s_master
{
	Display *display;
	screen_div *Grid;
    button      *buttons;
    int         b_total;
}				Master;

/* File : display_init.c */
Display	*display_init();
void	annhilate(Display *display);

/* File : reference_texture.c */
void	ref_texture(SDL_Rect *ref, int width, int length);

/*File update.c */
void	update(Master *master);

bool    isBoxCollide(int x, int y);

void test_button_click(Master *master, button *button);
void test_button_hover(Master *master, button *button);
void test_button_render(Master *master, button *button);

Master *init(Display *display);
void render_button(Master *master, SDL_Rect rect, color_rgba  color, bool fill);
#endif
