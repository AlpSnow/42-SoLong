/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 00:38:20 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/10 02:26:01 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long_bonus.h"

static int	is_enemy_movement_valid(int new_x, int new_y, t_list *lst)
{
	if (lst->map[new_y][new_x] == '1')
		return (0);
	else if (lst->map[new_y][new_x] == 'E')
		return (0);
	else if (lst->map[new_y][new_x] == 'C')
		return (0);
	else if (lst->map[new_y][new_x] == 'W')
		return (0);
	return (1);
}

static void	update_enemy_instances(t_list *lst, int direction)
{
	lst->enemy_bottom->instances[0].x = lst->enemy_x * lst->tile_size;
	lst->enemy_bottom->instances[0].y = lst->enemy_y * lst->tile_size;
	lst->enemy_top->instances[0].x = lst->enemy_x * lst->tile_size;
	lst->enemy_top->instances[0].y = lst->enemy_y * lst->tile_size;
	lst->enemy_left->instances[0].x = lst->enemy_x * lst->tile_size;
	lst->enemy_left->instances[0].y = lst->enemy_y * lst->tile_size;
	lst->enemy_right->instances[0].x = lst->enemy_x * lst->tile_size;
	lst->enemy_right->instances[0].y = lst->enemy_y * lst->tile_size;
	lst->enemy_bottom->instances[0].z = 4;
	lst->enemy_top->instances[0].z = 4;
	lst->enemy_left->instances[0].z = 4;
	lst->enemy_right->instances[0].z = 4;
	if (direction == 0)
		lst->enemy_top->instances[0].z = 9;
	else if (direction == 1)
		lst->enemy_bottom->instances[0].z = 9;
	else if (direction == 2)
		lst->enemy_left->instances[0].z = 9;
	else if (direction == 3)
		lst->enemy_right->instances[0].z = 9;
}

static void	move_enemy_if_valid(t_list *lst, int new_x, int new_y, \
								int direction)
{
	if (is_enemy_movement_valid(new_x, new_y, lst))
	{
		lst->enemy_x = new_x;
		lst->enemy_y = new_y;
		if (lst->enemy_x == lst->player_x && lst->enemy_y == lst->player_y)
		{
			free_game_resources(lst);
			exit_error_free(lst, INFO_DEFEAT, 70);
		}
		update_enemy_instances(lst, direction);
	}
}

void	move_enemy(void *setting)
{
	static int	frame_counter = 0;
	int			direction;
	int			new_x;
	int			new_y;
	t_list		*lst;

	lst = (t_list *)setting;
	if (frame_counter++ < 15)
		return ;
	frame_counter = 0;
	direction = rand() % 4;
	new_x = lst->enemy_x;
	new_y = lst->enemy_y;
	if (direction == 0)
		new_y--;
	else if (direction == 1)
		new_y++;
	else if (direction == 2)
		new_x--;
	else if (direction == 3)
		new_x++;
	move_enemy_if_valid(lst, new_x, new_y, direction);
}
