#include "doom.h"
#include "menus.h"
#include "libft.h"

# define HEALTH_BAR_HEIGHT_START 853
# define HEALTH_BAR_WIDTH_START 584
# define HEALTH_BAR_WIDTH 750
# define HEALTH_BAR_HEIGHT 50

void	put_health_bar(t_doom *data)
{
	draw_rectangle(&(data->lib), (t_point){HEALTH_BAR_WIDTH_START, HEALTH_BAR_HEIGHT_START},
		(t_point){(int)((data->player.health / 1000.0) * HEALTH_BAR_WIDTH),
		HEALTH_BAR_HEIGHT}, 0x21bf00);
}