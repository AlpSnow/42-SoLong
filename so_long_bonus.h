/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:02:30 by mwallis           #+#    #+#             */
/*   Updated: 2025/02/10 03:23:55 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# define ERROR_ARGC "\033[91mError\nThis program takes a single argument as \
parameter.\033[0m\n"
# define ERROR_BER "\033[91mError\nThis program takes a .ber map file as \
parameter.\033[0m\n"
# define ERROR_OPEN "\033[91mError\nError while opening file.\033[0m\n"
# define ERROR_INVALID_MAP "\033[91mError\nThe map format is invalid.\n\
The map must be rectangular and must not contain empty lines inside or \
around it.\033[0m\n"
# define ERROR_ALLOC "\033[91mError\nMemory allocation failed.\033[0m\n"
# define ERROR_EMPTY_MAP "\033[91mError\nThe map is empty.\033[0m\n"
# define ERROR_WALLS "\033[91mError\nThe map must be fully enclosed by \
walls (1).\033[0m\n"
# define ERROR_INVALID_SIZE "\033[91mError\nInvalid map size.\n\
The map must be at least 4x4, 3x5, or 5x3, and must not exceed \
38x20.\033[0m\n"
# define ERROR_INVALID_CHAR "\033[91mError\nThe map contains an invalid \
character.\nOnly '0' (floor), '1' (wall), 'P' (player), 'C' \
(collectible), 'E' (exit), 'T' (enemy), and 'W' (water) are allowed.\033[0m\n"
# define ERROR_NUMBER_ENEMY "\033[91mError\nInvalid number of enemies.\n\
The map must contain exactly one 'T' character, which represents the \
starting position of the enemy (threat).\033[0m\n"
# define ERROR_NUMBER_CHARACTER "\033[91mError\nInvalid number of \
players.\nThe map must contain exactly one 'P' character, \
representing the player's starting position.\033[0m\n"
# define ERROR_NUMBER_COLLECTIBLE "\033[91mError\nNo collectibles \
found.\nThe map must contain at least one 'C' collectible for the \
player to collect.\033[0m\n"
# define ERROR_NUMBER_EXIT "\033[91mError\nInvalid number of exits.\n\
The map must contain exactly one 'E' character, representing the \
exit point.\033[0m\n"
# define ERROR_NO_VALID_PATH "\033[91mError\nNo valid path found!\n\
The player must be able to reach all collectibles and the exit.\033[0m\n"
# define ERROR_MLX_INIT "\033[91mError\nFailed to initialize MLX.\n\
Ensure that your system supports MLX42 and try again.\033[0m\n"
# define ERROR_LOAD_TEXTURE "\033[91mError\nFailed to load a texture.\n\
Check the file path and ensure the image exists and is valid.\033[0m\n"
# define ERROR_LOAD_IMAGE "\033[91mError\nFailed to convert texture to image.\n\
Ensure MLX is properly initialized and your textures are valid.\033[0m\n"
# define ERROR_DISPLAY_IMAGE "\033[91mError\nFailed to display image on \
window.\nEnsure MLX is properly initialized and images are correctly \
loaded before attempting to display them.\033[0m\n"
# define INFO_EXIT "\033[94mInfo\nYou pressed Escape.\nThe window has been \
closed, and the program has exited cleanly.\033[0m\n"
# define INFO_VICTORY "\033[92mCongratulations!\nYou collected all items \
and reached the exit!\033[0m\n"
# define INFO_DEFEAT "\033[91mGame Over!\nThe enemy caught you... \
Your picking day is over!\033[0m\n"
# define INFO_DEFEAT_WATER "\033[91mGame Over!\nYou're drenched... \
Your picking day is over!\033[0m\n"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <fcntl.h>
# include "MLX42/MLX42.h"

typedef struct s_list
{
	char			**map;
	int				size_map_x;
	int				size_map_y;
	int				number_character;
	int				number_collectible;
	int				number_exit;
	mlx_t			*mlx;
	mlx_image_t		*character_bottom;
	mlx_image_t		*character_left;
	mlx_image_t		*character_top;
	mlx_image_t		*character_right;
	mlx_image_t		*floor;
	mlx_image_t		*wall;
	mlx_image_t		*collectible_frames[8];
	mlx_image_t		*exit;
	int				player_x;
	int				player_y;
	int				tile_size;
	int				move_count;
	mlx_image_t		*enemy_bottom;
	mlx_image_t		*enemy_left;
	mlx_image_t		*enemy_top;
	mlx_image_t		*enemy_right;
	int				enemy_x;
	int				enemy_y;
	int				number_enemy;
	mlx_image_t		*water;
}	t_list;

void	map_load(t_list *lst, char *argv);
void	check_map_validity(t_list *lst);
void	check_path_validity(t_list *lst);
void	find_character_position(t_list *lst);
void	find_enemy_position(t_list *lst);

void	init_game_data(t_list *lst);
void	free_game_resources(t_list *lst);
void	display_map(t_list *lst);
void	put_image_to_window(t_list *lst, mlx_image_t *image, int x, int y);
void	handle_keypress(mlx_key_data_t key_data, void *setting);
void	check_victory_or_drown(t_list *lst);
void	display_move_count(t_list *lst);
void	draw_all_collectible_frames(t_list *lst, int x, int y);
void	animate_collectibles(void *param);
void	move_enemy(void *setting);

void	clear_remaining_lines_gnl(int fd);
void	exit_error(const char *msg, size_t len);
void	exit_error_free(t_list *lst, const char *msg, size_t len);
void	exit_error_close_fd(int fd, const char *msg, size_t len);
void	exit_error_close_fd_free(t_list *lst, int fd, const char *msg, \
								size_t len);

char	*ft_strrchr(const char *str, int c);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nb_elements, size_t size_type);
char	*ft_itoa(int n);
char	*get_next_line(int fd);

#endif
