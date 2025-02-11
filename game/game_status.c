/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 01:14:33 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/08 01:26:45 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	display_move_count(t_list *lst)
{
	char	*move_str;
	char	*color;

	move_str = ft_itoa(lst->move_count);
	if (move_str == NULL)
	{
		free_game_resources(lst);
		exit_error_free(lst, ERROR_ALLOC, 41);
	}
	if (lst->move_count <= 50)
		color = "\033[92m";
	else
		color = "\033[91m";
	write(1, "Moves: ", 7);
	write(1, color, 5);
	write(1, move_str, ft_strlen(move_str));
	write(1, "\033[0m\n", 5);
	free(move_str);
}

static void	handle_collectible_pickup(t_list *lst)
{
	size_t	i;
	int		collectible_x;
	int		collectible_y;

	lst->number_collectible--;
	lst->map[lst->player_y][lst->player_x] = '0';
	i = 0;
	while (i < lst->collectible->count)
	{
		collectible_x = lst->collectible->instances[i].x;
		collectible_y = lst->collectible->instances[i].y;
		if (collectible_x == lst->player_x * lst->tile_size
			&& collectible_y == lst->player_y * lst->tile_size)
		{
			lst->collectible->instances[i].enabled = false;
			break ;
		}
		i++;
	}
	put_image_to_window(lst, lst->floor, lst->player_x, lst->player_y);
	lst->floor->instances[lst->floor->count - 1].z = 1;
}

void	check_victory(t_list *lst)
{
	char	current_tile;

	current_tile = lst->map[lst->player_y][lst->player_x];
	if (current_tile == 'C')
		handle_collectible_pickup(lst);
	if (current_tile == 'E' && lst->number_collectible == 0)
	{
		free_game_resources(lst);
		exit_error_free(lst, INFO_VICTORY, 72);
	}
}
