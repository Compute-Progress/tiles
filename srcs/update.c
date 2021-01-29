#include "SDL_Master.h"

static void keyboard(Input *input, SDL_Event event)
{
    Uint8 *keys = SDL_GetKeyboardState(NULL);
    SDL_GetMouseState(&input->prim_click_pos.x, &input->prim_click_pos.y);

    if (event.type == SDL_MOUSEBUTTONDOWN)
        input->mask |= A;
    if (keys[SDL_SCANCODE_SPACE])
        input->mask |= A;
    if (keys[SDL_SCANCODE_LEFT])
        input->mask |= DIR_LEFT;
    if (keys[SDL_SCANCODE_RIGHT])
        input->mask |= DIR_RIGHT;
    if (keys[SDL_SCANCODE_UP])
        input->mask |= DIR_UP;
    if (keys[SDL_SCANCODE_DOWN])
        input->mask |= DIR_DOWN;

    input->index += 1 & (input->mask >> 2);
    input->index -= 1 & (input->mask >> 3);
}

static void controller(Input *input, SDL_Event event)
{
    SDL_GameController *controller;
    SDL_Joystick    *joy;
    int dir;

    if (controller != NULL)
    {

        SDL_Log("Looking at controller");
        controller = input->controller;
        joy = SDL_GameControllerGetJoystick(controller);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) << 0);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) << 1);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) << 2);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP) << 3);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) << 4);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) << 5);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) << 6);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) << 7);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) << 8);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B) << 9);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y) << 10);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X) << 11);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK) << 12);
        input->mask |= (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START) << 13);

        dir = SDL_JoystickGetHat(joy, 0);
        if (dir == SDL_HAT_LEFT)
            input->mask |= DIR_LEFT;
        else if (dir == SDL_HAT_RIGHT)
            input->mask |= DIR_RIGHT;
        else if (dir == SDL_HAT_UP)
            input->mask |= DIR_UP;
        else if (dir == SDL_HAT_DOWN)
            input->mask |= DIR_DOWN;

        input->index += 1 & (input->mask >> 2);
        input->index -= 1 & (input->mask >> 3);
        SDL_Log("Done");
    }
}

//static void touch(Input *input)
//{

//}



static void get_input(Input *input)
{
	SDL_Event event;
    
    input->mask = 0;
    input->mouse = false;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
        if (event.type == SDL_MOUSEMOTION)
            input->mouse = true;
        controller(input, event);
        keyboard(input, event);
	}
    input->mask |= (input->index << 14); 
}

bool box_collide(SDL_Point point, SDL_Rect box)
{
    int x;
    int y;

    x = point.x;
    y = point.y;
    return (x >= box.x && x <= box.x + box.w && y >= box.y && y <= box.y + box.h);
}

void update_buttons(Master *master)
{
	int i, mask;
    bool yes = false;
    mask = master->display->input.mask;

    //SDL_Log("%d\n", mask);
    if (master->display->input.mouse)
        yes = true;
    i = 0;
    if (master->display->input.index < 0)
        master->display->input.index = 2;
    if (master->display->input.index >= 3)
        master->display->input.index = 0;
	while (i < master->b_total)
    {
        if ((box_collide(master->display->input.prim_click_pos, master->buttons[i].hitbox)) |           
            (master->display->input.index == master->buttons[i].index))
        {
            if (mask & 1)
                test_button_click(master, &master->buttons[i]);
            else
                test_button_hover(master, &master->buttons[i]);
        }
        else
        {
            test_button_render(master, &master->buttons[i]);
        }
        i++;
    }
    master->display->input.mask = 0;
}

void update(Master *master)
{

    SDL_Log("Update_loop");
	while (master->display->state)
	{
//   int i = 0;
//   while (i < SDL_NumJoysticks())
//   {
//       if (SDL_IsGameController(i))
//       {
//           master->display->input.controller = SDL_GameControllerOpen(i);
//           if ( master->display->input.controller)
//               break ;
//       }
//       i++;
//   }
 
   int press = SDL_GameControllerGetButton( master->display->input.controller, SDL_CONTROLLER_BUTTON_A);
 
   if (press)
   {
       SDL_GameControllerRumble( master->display->input.controller, 0x0F00, 0x0100, 70);
   }


		get_input(&master->display->input);
        //SDL_Log("Got input");
		update_buttons(master);
        //SDL_Log("Updated buttons");

		SDL_SetRenderDrawColor(master->display->renderer, 0,0,0,255);
		SDL_RenderPresent(master->display->renderer);
		SDL_RenderClear(master->display->renderer);
        //SDL_Log("Drawn scene");

	}
	annhilate(master->display);
	exit(0);
}
