/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:56:19 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/05 00:31:58 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	free_images(t_list *lst)
{
	int			i;
	mlx_image_t	*images[9];

	images[0] = lst->character_bottom;
	images[1] = lst->character_left;
	images[2] = lst->character_top;
	images[3] = lst->character_right;
	images[4] = lst->floor;
	images[5] = lst->wall;
	images[6] = lst->collectible;
	images[7] = lst->exit;
	images[8] = NULL;
	i = 0;
	while (images[i] != NULL)
	{
		mlx_delete_image(lst->mlx, images[i]);
		images[i] = NULL;
		i++;
	}
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
