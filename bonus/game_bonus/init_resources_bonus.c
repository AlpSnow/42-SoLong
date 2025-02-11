/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resources_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:59:04 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/10 20:55:24 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long_bonus.h"

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

static void	load_apple_animation(t_list *lst)
{
	lst->collectible_frames[0] = load_image_texture(lst,
			"./images/animation/apple_sprite_1.png");
	lst->collectible_frames[1] = load_image_texture(lst,
			"./images/animation/apple_sprite_2.png");
	lst->collectible_frames[2] = load_image_texture(lst,
			"./images/animation/apple_sprite_3.png");
	lst->collectible_frames[3] = load_image_texture(lst,
			"./images/animation/apple_sprite_4.png");
	lst->collectible_frames[4] = load_image_texture(lst,
			"./images/animation/apple_sprite_5.png");
	lst->collectible_frames[5] = load_image_texture(lst,
			"./images/animation/apple_sprite_6.png");
	lst->collectible_frames[6] = load_image_texture(lst,
			"./images/animation/apple_sprite_7.png");
	lst->collectible_frames[7] = load_image_texture(lst,
			"./images/animation/apple_sprite_8.png");
}

static void	load_enemy_sprites(t_list *lst)
{
	lst->enemy_bottom = load_image_texture(lst,
			"./images/knight/knight_bottom.png");
	lst->enemy_left = load_image_texture(lst,
			"./images/knight/knight_left.png");
	lst->enemy_top = load_image_texture(lst,
			"./images/knight/knight_top.png");
	lst->enemy_right = load_image_texture(lst,
			"./images/knight/knight_right.png");
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
	lst->exit = load_image_texture(lst, "./images/castle.png");
	lst->water = load_image_texture(lst, "./images/water.png");
	load_enemy_sprites(lst);
	load_apple_animation(lst);
}
