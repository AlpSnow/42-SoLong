/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <mwallis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 04:33:33 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/01 02:15:35 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	check_walls_surrounding(t_list *lst)
{
	int	x;
	int	y;

	x = 0;
	while (x < lst->size_map_x)
	{
		if (lst->map[0][x] != '1')
			exit_error_free(lst, ERROR_WALLS, 60);
		if (lst->map[lst->size_map_y - 1][x] != '1')
			exit_error_free(lst, ERROR_WALLS, 60);
		x++;
	}
	y = 0;
	while (y < lst->size_map_y)
	{
		if (lst->map[y][0] != '1' || lst->map[y][lst->size_map_x - 1] != '1')
			exit_error_free(lst, ERROR_WALLS, 60);
		y++;
	}
}

static void	check_map_elements(t_list *lst)
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
				lst->number_character++;
			else if (lst->map[y][x] == 'C')
				lst->number_collectible++;
			else if (lst->map[y][x] == 'E')
				lst->number_exit++;
			else if (lst->map[y][x] != '1' && lst->map[y][x] != '0'
					&& lst->map[y][x] != 'P' && lst->map[y][x] != 'C'
					&& lst->map[y][x] != 'E')
				exit_error_free(lst, ERROR_INVALID_CHAR, 145);
			x++;
		}
		y++;
	}
}

void	check_map_validity(t_list *lst)
{
	check_walls_surrounding(lst);
	check_map_elements(lst);
	if (lst->number_character != 1)
		exit_error_free(lst, ERROR_NUMBER_CHARACTER, 135);
	else if (lst->number_collectible < 1)
		exit_error_free(lst, ERROR_NUMBER_COLLECTIBLE, 115);
	else if (lst->number_exit != 1)
		exit_error_free(lst, ERROR_NUMBER_EXIT, 117);
}
