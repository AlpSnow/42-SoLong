/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:04:20 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/10 01:34:40 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long_bonus.h"

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
	else if (lst->map[y][x] == 'W')
		put_image_to_window(lst, lst->water, x, y);
	return (i);
}

static void	draw_foreground(t_list *lst, int x, int y)
{
	if (lst->map[y][x] == 'C')
		draw_all_collectible_frames(lst, x, y);
	else if (lst->map[y][x] == 'E')
		put_image_to_window(lst, lst->exit, x, y);
}

static void	init_game_entities(t_list *lst, int i)
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
	put_image_to_window(lst, lst->enemy_bottom,
		lst->enemy_x, lst->enemy_y);
	put_image_to_window(lst, lst->enemy_top, lst->enemy_x, lst->enemy_y);
	put_image_to_window(lst, lst->enemy_left, lst->enemy_x, lst->enemy_y);
	put_image_to_window(lst, lst->enemy_right,
		lst->enemy_x, lst->enemy_y);
	lst->enemy_bottom->instances[0].z = 9;
	lst->enemy_top->instances[0].z = 4;
	lst->enemy_left->instances[0].z = 4;
	lst->enemy_right->instances[0].z = 4;
	put_image_to_window(lst, lst->floor, lst->enemy_x, lst->enemy_y);
	lst->floor->instances[i + 1].z = 1;
}

void	display_map(t_list *lst)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
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
	init_game_entities(lst, i);
	mlx_loop_hook(lst->mlx, animate_collectibles, lst);
}
