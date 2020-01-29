/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_on_renderer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:41:11 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/28 18:15:06 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "menus.h"
#include "graphic_lib.h"
#include <SDL_ttf.h>
#include <SDL.h>

void	put_string_on_renderer(t_doom *data, t_point pos, t_label label
	, TTF_Font *font)
{
	SDL_Texture	*text;
	SDL_Rect	src;
	SDL_Rect	dest;

	data->lib.surface = TTF_RenderText_Blended(font, label.str, label.color);
	text = SDL_CreateTextureFromSurface(data->lib.renderer, data->lib.surface);
	SDL_FreeSurface(data->lib.surface);
	SDL_QueryTexture(text, &data->lib.text.format, &data->lib.text.access,
		&src.w, &src.h);
	src.x = 0;
	src.y = 0;
	dest = src;
	dest.x = pos.x - src.w / 2;
	dest.y = pos.y - src.h / 2;
	SDL_RenderCopy(data->lib.renderer, text, &src, &dest);
	SDL_DestroyTexture(text);
}
