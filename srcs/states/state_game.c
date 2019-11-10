#include "doom.h"
#include "player.h"
#include <SDL.h>
#include "graphic_lib.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "octree.h"

void		skybox(t_doom *data)
{
	int			i;
	int			j;
//	unsigned int			format;
	unsigned char			tab[4];
	static unsigned int		tabl[512 * 512];
	static int				ok = 0;
//	int						fd;

	tab[0] = 0;
/*	if (!ok)
	{
	fd = open("test.binary", O_RDONLY);
	read(fd, tabl, 512*512*4);
	ok++;
	}*/
	printf("pitch   = %u\n", data->lib.textures[0]->pitch);
	i = 0;
	while (i < 512)
	{
		j = 0;
		while (j < 512)
		{
			tab[3] = ((unsigned char *)data->lib.textures[0]->pixels)[i * data->lib.textures[0]->pitch + j * 4];
			tab[1] = ((unsigned char *)data->lib.textures[0]->pixels)[i * data->lib.textures[0]->pitch + j * 4 + 1];
			tab[2] = ((unsigned char *)data->lib.textures[0]->pixels)[i * data->lib.textures[0]->pitch + j * 4 + 2];
			tab[0] = ((unsigned char *)data->lib.textures[0]->pixels)[i * data->lib.textures[0]->pitch + j * 4];
			tabl[i * 512 + j] = *((unsigned int *)&tab);
			data->lib.image[i * WIDTH + j] = *((unsigned int*)&tab);
			data->lib.image[i * WIDTH + j] = tabl[i * 512 + j];
			j++;
		}
		i++;
	}
	if (!ok)
	{
		i = open("damien.binary", O_TRUNC | O_WRONLY | O_CREAT, 0777);
		write(i, tabl, 512*512*4);
		ok++;
	}
}

static inline t_octree	*on_x_higher_than_middle(t_vec3d *position
	, t_octree *node)
{
	if (position->y < (double)(node->center.y >> 1))
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[1]);
		else
			return (node->child[5]);
	}
	else
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[3]);
		else
			return (node->child[7]);
	}
}

static inline t_octree	*on_x_lower_than_middle(t_vec3d *position
		, t_octree *node)
{
	if (position->y < (double)(node->center.y >> 1))
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[0]);
		else
			return (node->child[4]);
	}
	else
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[2]);
		else
			return (node->child[6]);
	}
}

static t_octree				*find_position(t_vec3d *position, t_octree *node)
{
	while (node->leaf != EMPTY)
	{
		if (node->leaf == INSIDE)
		{
			if (position->x < (double)(node->center.x >> 1))
				node = on_x_lower_than_middle(position, node);
			else
				node = on_x_higher_than_middle(position, node);
		}
	}
	return (node);
}

void			interaction(t_doom *data)
{
	t_octree	*node;
	t_vec3d		intersect;
	int			ret;

	node = find_position(&data->player.camera.origin, data->octree);
	ret = check_x_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
	if (ret < 0 && node->leaf == BREAKABLE)
	{
		node->leaf = EMPTY;
		data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
		return ;
	}
	else if (ret == 3)
	{
		ret = check_x_intersect(&intersect, intersect, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_y_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_z_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
	}
	ret = check_y_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
	if (ret < 0 && node->leaf == BREAKABLE)
	{
		node->leaf = EMPTY;
		data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
		return ;
	}
	else if (ret == 3)
	{
		ret = check_x_intersect(&intersect, intersect, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_y_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_z_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
	}
	ret = check_z_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
	if (ret < 0 && node->leaf == BREAKABLE)
	{
		node->leaf = EMPTY;
		data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
		return ;
	}
	else if (ret == 3)
	{
		ret = check_x_intersect(&intersect, intersect, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_y_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_z_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
	}
}

int			state_game(t_doom *data)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN && data->lib.event.key.keysym.sym == SDLK_ESCAPE)
			switch_state(data, PLAYING, MAIN_MENU);
		else if (data->lib.event.type == SDL_MOUSEMOTION)
			camera_mouse_motion(&data->player.camera
					, &data->lib.event.motion.xrel, &data->lib.event.motion.yrel
					, &data->player.sensitivity);
		else if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
		{
			data->ball = 1;
			data->lib.cam_keys |= DESTROY;
		}
		else if (data->lib.event.type == SDL_MOUSEBUTTONUP)
			data->lib.cam_keys &= ~DESTROY;
		camera_press_key(&data->lib.event, data);
	}
	if (data->lib.cam_keys & DESTROY)
		interaction(data);
	camera_event_translate(data);
	ft_memcpy(data->lib.image, data->lib.hud_texture->pixels, (WIDTH * HEIGHT) << 2);
	raytracing(data);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
