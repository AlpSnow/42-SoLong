/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 06:58:25 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/09 20:39:54 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long_bonus.h"

static int	is_collectible_completely_disabled(t_list *lst, \
												size_t i)
{
	int	f;

	f = 0;
	while (f < 8)
	{
		if (lst->collectible_frames[f]->instances[i].enabled == true)
			return (0);
		f++;
	}
	return (1);
}

void	animate_collectibles(void *setting)
{
	static int	frame_counter = 0;
	static int	collectible_frame = 0;
	size_t		i;
	int			old_frame;
	t_list		*lst;

	lst = (t_list *)setting;
	if (frame_counter++ < 8)
		return ;
	frame_counter = 0;
	i = 0;
	while (i < lst->collectible_frames[0]->count)
	{
		if (is_collectible_completely_disabled(lst, i) == 1)
		{
			i++;
			continue ;
		}
		old_frame = (collectible_frame + 7) % 8;
		lst->collectible_frames[collectible_frame]->instances[i].enabled = true;
		lst->collectible_frames[old_frame]->instances[i].enabled = false;
		i++;
	}
	collectible_frame = (collectible_frame + 1) % 8;
}

void	draw_all_collectible_frames(t_list *lst, int x, int y)
{
	int	frame;
	int	i;

	frame = 0;
	while (frame < 8)
	{
		put_image_to_window(lst, lst->collectible_frames[frame], x, y);
		i = lst->collectible_frames[frame]->count - 1;
		if (frame == 0)
			lst->collectible_frames[frame]->instances[i].enabled = true;
		else
			lst->collectible_frames[frame]->instances[i].enabled = false;
		frame++;
	}
}
