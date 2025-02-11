/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:56:19 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/08 06:46:27 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long_bonus.h"

static void	free_collectible_images(t_list *lst)
{
	int			i;
	mlx_image_t	*images[9];

	images[0] = lst->collectible_frames[0];
	images[1] = lst->collectible_frames[1];
	images[2] = lst->collectible_frames[2];
	images[3] = lst->collectible_frames[3];
	images[4] = lst->collectible_frames[4];
	images[5] = lst->collectible_frames[5];
	images[6] = lst->collectible_frames[6];
	images[7] = lst->collectible_frames[7];
	images[8] = NULL;
	i = 0;
	while (images[i] != NULL)
	{
		mlx_delete_image(lst->mlx, images[i]);
		images[i] = NULL;
		i++;
	}
}

static void	free_images(t_list *lst)
{
	int			i;
	mlx_image_t	*images[13];

	images[0] = lst->character_bottom;
	images[1] = lst->character_left;
	images[2] = lst->character_top;
	images[3] = lst->character_right;
	images[4] = lst->floor;
	images[5] = lst->wall;
	images[6] = lst->exit;
	images[7] = lst->water;
	images[8] = lst->enemy_bottom;
	images[9] = lst->enemy_left;
	images[10] = lst->enemy_top;
	images[11] = lst->enemy_right;
	images[12] = NULL;
	i = 0;
	while (images[i] != NULL)
	{
		mlx_delete_image(lst->mlx, images[i]);
		images[i] = NULL;
		i++;
	}
	free_collectible_images(lst);
}

static void	free_mlx(t_list *lst)
{
	if (lst->mlx)
	{
		mlx_terminate(lst->mlx);
		lst->mlx = NULL;
	}
}

void	free_game_resources(t_list *lst)
{
	if (!lst->mlx)
		return ;
	free_images(lst);
	free_mlx(lst);
}
