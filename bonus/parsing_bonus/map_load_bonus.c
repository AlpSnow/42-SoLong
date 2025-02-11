/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <mwallis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:49:17 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/06 06:04:37 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long_bonus.h"

static void	check_map_size_validity(t_list *lst)
{
	if (!((lst->size_map_x >= 4 && lst->size_map_y >= 4)
			|| (lst->size_map_x >= 3 && lst->size_map_y >= 5)
			|| (lst->size_map_x >= 5 && lst->size_map_y >= 3)))
	{
		exit_error(ERROR_INVALID_SIZE, 103);
	}
	if (lst->size_map_x > 38 || lst->size_map_y > 20)
	{
		exit_error(ERROR_INVALID_SIZE, 103);
	}
}

static char	*add_newline_if_missing(int fd, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(line, "\n");
	if (tmp == NULL)
	{
		free(line);
		exit_error_close_fd(fd, ERROR_ALLOC, 41);
	}
	free(line);
	return (tmp);
}

static void	map_get_dimensions(int fd, t_list *lst)
{
	char	*line;
	int		line_lenght;

	line = get_next_line(fd);
	if (line == NULL)
		exit_error_close_fd(fd, ERROR_EMPTY_MAP, 33);
	line_lenght = ft_strlen(line);
	lst->size_map_x = line_lenght - 1;
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] != '\n')
			line = add_newline_if_missing(fd, line);
		lst->size_map_y = lst->size_map_y + 1;
		if ((int)ft_strlen(line) - 1 != lst->size_map_x)
		{
			free(line);
			clear_remaining_lines_gnl(fd);
			exit_error_close_fd(fd, ERROR_INVALID_MAP, 124);
		}
		free(line);
		line = get_next_line(fd);
	}
}

static void	map_initialize(int fd, t_list *lst)
{
	int		y;
	char	*line;

	lst->map = malloc(sizeof(char *) * (lst->size_map_y + 1));
	if (lst->map == NULL)
		exit_error_close_fd(fd, ERROR_ALLOC, 41);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] != '\n')
			line = add_newline_if_missing(fd, line);
		lst->map[y] = ft_strdup(line);
		if (lst->map[y] == NULL)
		{
			free(line);
			clear_remaining_lines_gnl(fd);
			exit_error_close_fd_free(lst, fd, ERROR_ALLOC, 41);
		}
		free(line);
		line = get_next_line(fd);
		y++;
	}
	lst->map[y] = NULL;
}

void	map_load(t_list *lst, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		exit_error(ERROR_OPEN, 41);
	map_get_dimensions(fd, lst);
	close(fd);
	check_map_size_validity(lst);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		exit_error(ERROR_OPEN, 41);
	map_initialize(fd, lst);
	close(fd);
}
