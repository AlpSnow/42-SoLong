/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:59:04 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/05 02:43:45 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static mlx_image_t	*load_image_texture(t_list *lst, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (texture == NULL)
	{
		free_game_resources(lst);
		exit_error_free(lst, ERROR_LOAD_TEXTURE, 104);
	}
	image = mlx_texture_to_image(lst->mlx, texture);
	mlx_delete_texture(texture);
	if (image == NULL)
	{
		free_game_resources(lst);
		exit_error_free(lst, ERROR_LOAD_IMAGE, 115);
	}
	return (image);
}

void	init_game_data(t_list *lst)
{
	lst->tile_size = 100;
	lst->mlx = mlx_init(lst->tile_size * lst->size_map_x,
			lst->tile_size * lst->size_map_y, "so_long", true);
	if (lst->mlx == NULL)
		exit_error_free(lst, ERROR_MLX_INIT, 95);
	lst->character_bottom = load_image_texture(lst,
			"./images/peasant/peasant_grass_bottom.png");
	lst->character_left = load_image_texture(lst,
			"./images/peasant/peasant_grass_left.png");
	lst->character_top = load_image_texture(lst,
			"./images/peasant/peasant_grass_top.png");
	lst->character_right = load_image_texture(lst,
			"./images/peasant/peasant_grass_right.png");
	lst->floor = load_image_texture(lst, "./images/grass.png");
	lst->wall = load_image_texture(lst, "./images/wall.png");
	lst->collectible = load_image_texture(lst, "./images/apple.png");
	lst->exit = load_image_texture(lst, "./images/castle.png");
}
