/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 06:00:34 by mwallis           #+#    #+#             */
/*   Updated: 2025/01/31 05:13:08 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	clear_remaining_lines_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	exit_error(const char *msg, size_t len)
{
	write(2, msg, len);
	exit(1);
}

void	exit_error_free(t_list *lst, const char *msg, size_t len)
{
	int	i;

	i = 0;
	if (lst->map)
	{
		while (lst->map[i])
			free(lst->map[i++]);
		free(lst->map);
	}
	write(2, msg, len);
	exit(1);
}

void	exit_error_close_fd(int fd, const char *msg, size_t len)
{
	close(fd);
	write(2, msg, len);
	exit(1);
}

void	exit_error_close_fd_free(t_list *lst, int fd, const char *msg, \
								size_t len)
{
	int	i;

	i = 0;
	if (lst->map)
	{
		while (lst->map[i])
			free(lst->map[i++]);
		free(lst->map);
	}
	close(fd);
	write(2, msg, len);
	exit(1);
}
