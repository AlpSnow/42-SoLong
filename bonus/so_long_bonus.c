/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:35:48 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/10 03:24:33 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static int	is_ber_file(char *str)
{
	char	*ext;

	ext = ft_strrchr(str, '.');
	if (ext == NULL)
		return (0);
	if (ft_strcmp(ext, ".ber") == 0)
		return (1);
	return (0);
}

static void	init_empty_enemy(t_list *lst)
{
	lst->enemy_bottom = NULL;
	lst->enemy_left = NULL;
	lst->enemy_top = NULL;
	lst->enemy_right = NULL;
	lst->enemy_x = 0;
	lst->enemy_y = 0;
	lst->number_enemy = 0;
}

static void	init_empty_lst(t_list *lst)
{
	int	i;

	lst->map = NULL;
	lst->size_map_x = 0;
	lst->size_map_y = 0;
	lst->number_character = 0;
	lst->number_collectible = 0;
	lst->number_exit = 0;
	lst->mlx = NULL;
	lst->character_bottom = NULL;
	lst->character_left = NULL;
	lst->character_top = NULL;
	lst->character_right = NULL;
	lst->floor = NULL;
	lst->wall = NULL;
	lst->exit = NULL;
	lst->player_x = 0;
	lst->player_y = 0;
	lst->tile_size = 0;
	lst->move_count = 0;
	lst->water = NULL;
	i = 0;
	while (i < 8)
		lst->collectible_frames[i++] = NULL;
	init_empty_enemy(lst);
}

int	main(int argc, char *argv[])
{
	t_list	lst;
	int		i;

	if (argc != 2)
		return (write(2, ERROR_ARGC, 66), 1);
	if (is_ber_file(argv[1]) == 0)
		return (write(2, ERROR_BER, 64), 1);
	init_empty_lst(&lst);
	map_load(&lst, argv[1]);
	check_map_validity(&lst);
	check_path_validity(&lst);
	init_game_data(&lst);
	display_map(&lst);
	mlx_key_hook(lst.mlx, &handle_keypress, &lst);
	mlx_loop_hook(lst.mlx, move_enemy, &lst);
	mlx_loop(lst.mlx);
	i = 0;
	while (i < lst.size_map_y)
	{
		free(lst.map[i]);
		i++;
	}
	free(lst.map);
	free_game_resources(&lst);
	return (0);
}
