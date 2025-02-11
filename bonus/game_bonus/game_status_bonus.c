/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_status_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 01:14:33 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/08 06:54:14 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long_bonus.h"

void	display_move_count(t_list *lst)
{
	static int			last_move_count = -1;
	static mlx_image_t	*move_display = NULL;
	char				*score_str;
	char				*score_full_text;

	if (lst->move_count == last_move_count)
		return ;
	last_move_count = lst->move_count;
	score_str = ft_itoa(lst->move_count);
	if (!score_str)
	{
		free_game_resources(lst);
		exit_error_free(lst, ERROR_ALLOC, 41);
	}
	score_full_text = ft_strjoin("Moves: ", score_str);
	free(score_str);
	if (!score_full_text)
	{
		free_game_resources(lst);
		exit_error_free(lst, ERROR_ALLOC, 41);
	}
	if (move_display)
		mlx_delete_image(lst->mlx, move_display);
	move_display = mlx_put_string(lst->mlx, score_full_text, 145, 135);
	free(score_full_text);
}

static void	disable_all_frames_collectible(t_list *lst, size_t index)
{
	int	frame;

	frame = 0;
	while (frame < 8)
	{
		lst->collectible_frames[frame]->instances[index].enabled = false;
		frame++;
	}
}

static void	handle_collectible_pickup(t_list *lst)
{
	size_t	i;
	int		collectible_x;
	int		collectible_y;

	lst->number_collectible--;
	lst->map[lst->player_y][lst->player_x] = '0';
	i = 0;
	while (i < lst->collectible_frames[0]->count)
	{
		collectible_x = lst->collectible_frames[0]->instances[i].x;
		collectible_y = lst->collectible_frames[0]->instances[i].y;
		if (collectible_x == lst->player_x * lst->tile_size
			&& collectible_y == lst->player_y * lst->tile_size)
		{
			disable_all_frames_collectible(lst, i);
			break ;
		}
		i++;
	}
	put_image_to_window(lst, lst->floor, lst->player_x, lst->player_y);
	lst->floor->instances[lst->floor->count - 1].z = 1;
}

void	check_victory_or_drown(t_list *lst)
{
	char	current_tile;

	current_tile = lst->map[lst->player_y][lst->player_x];
	if (current_tile == 'W')
	{
		free_game_resources(lst);
		exit_error_free(lst, INFO_DEFEAT_WATER, 65);
	}
	if (current_tile == 'C')
		handle_collectible_pickup(lst);
	if (current_tile == 'E' && lst->number_collectible == 0)
	{
		free_game_resources(lst);
		exit_error_free(lst, INFO_VICTORY, 72);
	}
}
