/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:04:20 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/06 05:43:21 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	put_image_to_window(t_list *lst, mlx_image_t *image, int x, int y)
{
	if (mlx_image_to_window(lst->mlx, image,
			x * lst->tile_size, y * lst->tile_size) < 0)
	{
		free_game_resources(lst);
		exit_error_free(lst, ERROR_DISPLAY_IMAGE, 151);
	}
}

static int	draw_background(t_list *lst, int x, int y, int i)
{
	if (lst->map[y][x] == '1')
		put_image_to_window(lst, lst->wall, x, y);
	else if (lst->map[y][x] == '0')
	{
		put_image_to_window(lst, lst->floor, x, y);
		lst->floor->instances[i].z = 1;
		i++;
	}
	return (i);
}

static void	draw_foreground(t_list *lst, int x, int y)
{
	if (lst->map[y][x] == 'C')
		put_image_to_window(lst, lst->collectible, x, y);
	else if (lst->map[y][x] == 'E')
		put_image_to_window(lst, lst->exit, x, y);
}

static void	init_character_instances(t_list *lst, int i)
{
	put_image_to_window(lst, lst->character_bottom,
		lst->player_x, lst->player_y);
	put_image_to_window(lst, lst->character_top, lst->player_x, lst->player_y);
	put_image_to_window(lst, lst->character_left, lst->player_x, lst->player_y);
	put_image_to_window(lst, lst->character_right,
		lst->player_x, lst->player_y);
	lst->character_bottom->instances[0].z = 10;
	lst->character_top->instances[0].z = 5;
	lst->character_left->instances[0].z = 5;
	lst->character_right->instances[0].z = 5;
	put_image_to_window(lst, lst->floor, lst->player_x, lst->player_y);
	lst->floor->instances[i].z = 1;
}

void	display_map(t_list *lst)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (y < lst->size_map_y)
	{
		x = 0;
		while (x < lst->size_map_x)
		{
			i = draw_background(lst, x, y, i);
			draw_foreground(lst, x, y);
			x++;
		}
		y++;
	}
	init_character_instances(lst, i);
}
