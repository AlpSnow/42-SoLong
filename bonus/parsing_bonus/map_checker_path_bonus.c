/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <mwallis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:23:58 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/06 05:35:27 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long_bonus.h"

static void	flood_fill(char **map_copy, int x, int y, int test_type)

{
	if (test_type == 1)
	{
		if (map_copy[y][x] == '1' || map_copy[y][x] == 'F'
			|| map_copy[y][x] == 'E' || map_copy[y][x] == 'W')
			return ;
	}
	if (test_type == 2)
	{
		if (map_copy[y][x] == '1' || map_copy[y][x] == 'F'
			|| map_copy[y][x] == 'W')
			return ;
	}
	map_copy[y][x] = 'F';
	flood_fill(map_copy, x + 1, y, test_type);
	flood_fill(map_copy, x - 1, y, test_type);
	flood_fill(map_copy, x, y + 1, test_type);
	flood_fill(map_copy, x, y - 1, test_type);
}

static void	check_exit_is_accessible(t_list *lst, char **map_copy)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < lst->size_map_y)
	{
		x = 0;
		while (x < lst->size_map_x)
		{
			if (map_copy[y][x] == 'E')
			{
				i = 0;
				while (map_copy[i] != NULL)
					free(map_copy[i++]);
				free(map_copy);
				exit_error_free(lst, ERROR_NO_VALID_PATH, 100);
			}
			x++;
		}
		y++;
	}
}

static void	check_all_collectibles_are_accessible(t_list *lst, char **map_copy)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < lst->size_map_y)
	{
		x = 0;
		while (x < lst->size_map_x)
		{
			if (map_copy[y][x] == 'C')
			{
				i = 0;
				while (map_copy[i] != NULL)
					free(map_copy[i++]);
				free(map_copy);
				exit_error_free(lst, ERROR_NO_VALID_PATH, 100);
			}
			x++;
		}
		y++;
	}
}

static char	**copy_the_map(t_list *lst)
{
	char	**map_copy;
	int		y;
	int		i;

	y = 0;
	map_copy = malloc(sizeof(char *) * (lst->size_map_y + 1));
	if (map_copy == NULL)
		exit_error_free(lst, ERROR_ALLOC, 41);
	while (y < lst->size_map_y)
	{
		map_copy[y] = ft_strdup(lst->map[y]);
		if (map_copy[y] == NULL)
		{
			i = 0;
			while (i < y)
				free(map_copy[i++]);
			free(map_copy);
			exit_error_free(lst, ERROR_ALLOC, 41);
		}
		y++;
	}
	map_copy[y] = NULL;
	return (map_copy);
}

void	check_path_validity(t_list *lst)
{
	char	**map_copy;
	int		i;

	map_copy = copy_the_map(lst);
	find_character_position(lst);
	find_enemy_position(lst);
	flood_fill(map_copy, lst->player_x, lst->player_y, 1);
	check_all_collectibles_are_accessible(lst, map_copy);
	i = 0;
	while (map_copy[i] != NULL)
		free(map_copy[i++]);
	free(map_copy);
	map_copy = copy_the_map(lst);
	flood_fill(map_copy, lst->player_x, lst->player_y, 2);
	check_exit_is_accessible(lst, map_copy);
	i = 0;
	while (map_copy[i] != NULL)
		free(map_copy[i++]);
	free(map_copy);
}
