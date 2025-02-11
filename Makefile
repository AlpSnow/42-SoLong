SRCS = so_long.c \
./parsing/map_load.c \
./parsing/map_checker_structure.c \
./parsing/map_checker_path.c \
./parsing/find_player_position.c \
error_handling.c \
./functions/ft_strrchr.c \
./functions/ft_strcmp.c \
./functions/ft_calloc.c \
./functions/ft_strdup.c \
./functions/ft_strlen.c \
./functions/ft_substr.c \
./functions/ft_strchr.c \
./functions/ft_strjoin.c \
./functions/ft_itoa.c \
./functions/get_next_line.c \
./game/init_resources.c \
./game/free_resources.c \
./game/display_map.c \
./game/input_handling.c \
./game/game_status.c

SRCSBONUS = ./bonus/so_long_bonus.c \
./bonus/parsing_bonus/map_load_bonus.c \
./bonus/parsing_bonus/map_checker_structure_bonus.c \
./bonus/parsing_bonus/map_checker_path_bonus.c \
./bonus/parsing_bonus/init_positions_bonus.c \
./bonus/error_handling_bonus.c \
./bonus/functions_bonus/ft_strrchr_bonus.c \
./bonus/functions_bonus/ft_strcmp_bonus.c \
./bonus/functions_bonus/ft_calloc_bonus.c \
./bonus/functions_bonus/ft_strdup_bonus.c \
./bonus/functions_bonus/ft_strlen_bonus.c \
./bonus/functions_bonus/ft_substr_bonus.c \
./bonus/functions_bonus/ft_strchr_bonus.c \
./bonus/functions_bonus/ft_strjoin_bonus.c \
./bonus/functions_bonus/ft_itoa_bonus.c \
./bonus/functions_bonus/get_next_line_bonus.c \
./bonus/game_bonus/init_resources_bonus.c \
./bonus/game_bonus/free_resources_bonus.c \
./bonus/game_bonus/display_map_bonus.c \
./bonus/game_bonus/input_handling_bonus.c \
./bonus/game_bonus/game_status_bonus.c \
./bonus/game_bonus/game_animation.c \
./bonus/game_bonus/enemy_movement_bonus.c

OBJS = $(SRCS:.c=.o)
OBJSBONUS = $(SRCSBONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLXPATH = ./MLX42
HEADERS = -I ./MLX42/include
MLXLIBS = $(MLXPATH)/build/libmlx42.a -ldl -lglfw -pthread -lm


NAME = so_long
NAME_BONUS = so_long_bonus

all: libmlx $(NAME)


libmlx:
	@chmod +x $(MLXPATH)/tools/compile_shader.sh
	@cmake $(MLXPATH) -B $(MLXPATH)/build && make -C $(MLXPATH)/build -j4

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLXLIBS) $(HEADERS) -o $(NAME)

bonus: libmlx $(OBJSBONUS)
	$(CC) $(OBJSBONUS) $(MLXLIBS) $(HEADERS) -o $(NAME_BONUS)

clean:
	rm -rf $(OBJS) $(OBJSBONUS)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)
	rm -rf $(MLXPATH)/build

re: fclean all


.c.o:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

.PHONY: all clean fclean re libmlx
