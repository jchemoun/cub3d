# Executable name
NAME				=	cub3D
NAME_BONUS			=	cub3D

# Compilation
CC					=	gcc -Wall -Wextra -Werror -flto -O2 -march=native
MLX					=	-I minilibx -lmlx -framework OpenGL -framework AppKit

# Name
SRC_NAME            =	ft_atoi.c 					\
						ft_bzero.c 					\
						ft_calloc.c					\
						ft_isalnum.c				\
						ft_isalpha.c				\
						ft_isascii.c				\
						ft_isdigit.c				\
						ft_isprint.c				\
						ft_itoa.c					\
						ft_memccpy.c				\
						ft_memchr.c					\
						ft_memcmp.c					\
						ft_memcpy.c					\
						ft_memmove.c				\
						ft_memset.c					\
						ft_putchar_fd.c				\
						ft_putendl_fd.c				\
						ft_putnbr_fd.c				\
						ft_putnbr_base.c			\
						ft_putstr_fd.c				\
						ft_split.c					\
						ft_strchr.c					\
						ft_strdup.c					\
						ft_strjoin.c				\
						ft_strlcat.c				\
						ft_strlcpy.c				\
						ft_strlen.c					\
						ft_strmapi.c				\
						ft_strncmp.c				\
						ft_strnstr.c				\
						ft_strrchr.c				\
						ft_strtrim.c				\
						ft_substr.c					\
						ft_tolower.c				\
						ft_toupper.c				\
						ft_isinset.c				\
						ft_macro.c					\
						ft_print_nbr.c				\
						ft_print_unbr.c				\
						ft_print_unbr_utils.c		\
						ft_print_cs.c				\
						ft_print_n.c				\
						ft_printf.c					\
						get_next_line_map.c			\
						get_next_line_utils_map.c	\
						get_next_line.c				\
						get_next_line_utils.c		\
						check_map.c					\
						parse_color.c				\
						parse_map.c					\
						parse_wall.c				\
						parse.c						\
						dda.c						\
						draw_map.c					\
						draw.c						\
						draw_sprite.c				\
						init_text.c					\
						key_hook.c					\
						line.c						\
						move.c						\
						ray.c						\
						ray_utils.c					\
						rotate.c					\
						destroy.c					\
						parse_utils.c				\
						save.c						\
						main.c						\

SRC_BONUS_NAME		=	ft_lstadd_back_bonus.c 	\
						ft_lstadd_front_bonus.c	\
						ft_lstclear_bonus.c		\
						ft_lstdelone_bonus.c	\
						ft_lstiter_bonus.c		\
						ft_lstlast_bonus.c		\
						ft_lstmap_bonus.c		\
						ft_lstnew_bonus.c		\
						ft_lstsize_bonus.c		\

INCLUDE_NAME		=	libft.h					\
						ft_printf.h				\
						ft_cube3d.h				\
						get_next_line.h			\
						get_next_line_map.h		\

# Path
SRC_PATH			=	./src/
OBJ_PATH			=	./obj/
INCLUDE_PATH		=	./include/

# Name + Path
SRC					=	$(addprefix $(SRC_PATH),		$(SRC_NAME))
SRC_BONUS			=	$(addprefix $(SRC_PATH),		$(SRC_BONUS_NAME))
OBJ					=	$(patsubst	$(SRC_PATH)%.c,		$(OBJ_PATH)%.o, $(SRC))
OBJ_BONUS			=	$(patsubst	$(SRC_PATH)%.c,		$(OBJ_PATH)%.o, \
						$(SRC_BONUS))
INCLUDE				=	$(addprefix $(INCLUDE_PATH),	$(INCLUDE_NAME))

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) -I $(INCLUDE_PATH) $(OBJ) $(MLX)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCLUDE)
	@mkdir -p $(OBJ_PATH)
	@$(CC) -I $(INCLUDE_PATH) -c $< -o $@

bonus: $(OBJ) $(OBJ_BONUS)
	@$(CC) -o $(NAME_BONUS) -I $(INCLUDE_PATH) $(OBJ) $(OBJ_BONUS) $(MLX)

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all