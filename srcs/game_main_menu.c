#include "doom.h"
#include "libft.h"
#include "menus.h"

static void	check_inputs_menu(t_doom *data, t_button *btab, int nbuttons)
{
	const uint8_t	*input;

	input = SDL_GetKeyboardState(NULL);
	if (input[SDL_SCANCODE_UP])
	{
		if (data->button == -1 || data->button == 0)
			data->button = 0;
		else
			--data->button;
	}
	else if (input[SDL_SCANCODE_DOWN])
	{
		if (data->button == nbuttons - 1)
			return ;
		else
			++data->button;
	}
	else if (input[SDL_SCANCODE_RETURN] || input[SDL_SCANCODE_RETURN2])
		switch_state(data, MAIN_MENU, btab[data->button].state);
}

int			game_main_menu(t_doom *data)
{
	t_button	buttons[4];

	buttons[0] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), LEAVING, "PLAY");
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), SCORES, "SCORES");
	buttons[2] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), SETTINGS, "SETTINGS");
	buttons[3] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (2 * DEF_BUTTON_H + 2 * BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), LEAVING, "QUIT GAME");

	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 4);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 8), label("DOOM", RED), data->lib.ptrfont[0]);
	put_buttons_names(data, buttons, BLACK, 4);
	check_inputs_menu(data, buttons, 4);
	return (0);
}
