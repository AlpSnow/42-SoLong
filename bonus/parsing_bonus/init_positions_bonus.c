/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player_position_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 05:23:19 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/09 22:53:20 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long_bonus.h"

void	find_character_position(t_list *lst)
{
	int	x;
	int	y;

	y = 0;
	while (y < lst->size_map_y)
	{
		x = 0;
		while (x < lst->size_map_x)
		{
			if (lst->map[y][x] == 'P')
			{
				lst->player_x = x;
				lst->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	find_enemy_position(t_list *lst)
{
	int	x;
	int	y;

	y = 0;
	while (y < lst->size_map_y)
	{
		x = 0;
		while (x < lst->size_map_x)
		{
			if (lst->map[y][x] == 'T')
			{
				lst->enemy_x = x;
				lst->enemy_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
