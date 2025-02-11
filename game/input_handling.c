/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:38:34 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/07 23:52:32 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	is_movement_valid(mlx_key_data_t key_data, t_list *lst)
{
	int	new_x;
	int	new_y;

	new_x = lst->player_x;
	new_y = lst->player_y;
	if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
		new_y -= 1;
	else if (key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT)
		new_x -= 1;
	else if (key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN)
		new_y += 1;
	else if (key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT)
		new_x += 1;
	if (lst->map[new_y][new_x] == '1')
		return (0);
	if (lst->map[new_y][new_x] == 'E' && lst->number_collectible > 0)
		return (0);
	return (1);
}

static void	update_character_instances(t_list *lst, mlx_key_data_t key_data)
{
	lst->character_bottom->instances[0].x = lst->player_x * lst->tile_size;
	lst->character_bottom->instances[0].y = lst->player_y * lst->tile_size;
	lst->character_top->instances[0].x = lst->player_x * lst->tile_size;
	lst->character_top->instances[0].y = lst->player_y * lst->tile_size;
	lst->character_left->instances[0].x = lst->player_x * lst->tile_size;
	lst->character_left->instances[0].y = lst->player_y * lst->tile_size;
	lst->character_right->instances[0].x = lst->player_x * lst->tile_size;
	lst->character_right->instances[0].y = lst->player_y * lst->tile_size;
	lst->character_bottom->instances[0].z = 5;
	lst->character_top->instances[0].z = 5;
	lst->character_left->instances[0].z = 5;
	lst->character_right->instances[0].z = 5;
	if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
		lst->character_top->instances[0].z = 10;
	else if (key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT)
		lst->character_left->instances[0].z = 10;
	else if (key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN)
		lst->character_bottom->instances[0].z = 10;
	else if (key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT)
		lst->character_right->instances[0].z = 10;
}

static void	update_player_position(mlx_key_data_t key_data, t_list *lst)
{
	lst->move_count++;
	if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_UP)
		lst->player_y -= 1;
	else if (key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_LEFT)
		lst->player_x -= 1;
	else if (key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_DOWN)
		lst->player_y += 1;
	else if (key_data.key == MLX_KEY_D || key_data.key == MLX_KEY_RIGHT)
		lst->player_x += 1;
	display_move_count(lst);
	check_victory(lst);
}

void	handle_keypress(mlx_key_data_t key_data, void *setting)
{
	t_list	*lst;

	lst = (t_list *)setting;
	if (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT)
	{
		if (key_data.key == MLX_KEY_ESCAPE)
		{
			free_game_resources(lst);
			exit_error_free(lst, INFO_EXIT, 98);
		}
		if (is_movement_valid(key_data, lst) == 1)
			update_player_position(key_data, lst);
		update_character_instances(lst, key_data);
	}
}
