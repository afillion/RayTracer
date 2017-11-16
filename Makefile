#!/usr/bin/make -f

NAME			=	RTv1
PUNCHLINE		=	simulate new universe

SRC_BASE		=	$(shell find src | grep '\.c' | cut -c 5- | sort)

CC				=	gcc

FLAGS			= -O3
FLAGS			+=	-Wall -Wextra -Werror

SRC_DIR			=	src/
INC_DIR			=	includes/
OBJ_DIR			=	objs/

SRCS			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))

LIBFT_DIR		=	libft/
LIBFT_LIB		=	$(LIBFT_DIR)libft.a
LIBFT_INC		=	$(LIBFT_DIR)includes/

MLX				=	libmlx/libmlx.a -framework OpenGL -framework AppKit
MLX_INC			=	libmlx/

all:
					@printf "\n["
					@make -s -C $(MLX_INC)
					@make -s -C $(LIBFT_DIR)
					@make -s -j $(NAME)
					@printf "]\n"
					@printf "\n=> \x1B[32m$(NAME) ready to $(PUNCHLINE) ! ( ͡° ͜ʖ ͡°) \x1B[37m\n"

$(NAME):			$(MLX_INC) $(LIBFT_LIB) $(OBJ_DIR) $(OBJS)
					@$(CC) $(FLAGS) $(OBJS) -o $(NAME) -I $(INC_DIR) -I $(LIBFT_INC) $(LIBFT_LIB) $(MLX)

$(LIBFT_LIB):
					make -C $(LIBFT_DIR)

$(MLX_INC):
					make -C $(MLX_INC)

$(OBJ_DIR):
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c | $(OBJ_DIR) $(INC_DIR)
					@$(CC) $(FLAGS) -MMD -c $< -o $@ -I $(INC_DIR) -I $(LIBFT_INC) -I $(MLX_INC)
					@printf "\x1B[32m▒\e[0m"

clean:
					@printf "=> \x1B[31mDeleting $(NAME) .obj files...\x1B[37m\n"
					@rm -rf $(OBJ_DIR)
					@printf "=> \x1B[31mDeleting libft .obj files...\x1B[37m\n"
					@make -C $(LIBFT_DIR) clean

fclean:				clean
					@printf "=> \x1B[31mDeleting $(NAME)...\x1B[37m\n"
					@rm -f $(NAME)
					@printf "=> \x1B[31mDeleting libft.a.. \x1B[37m\n"
					@make -C $(LIBFT_DIR) fclean
					@make -C $(MLX_INC) clean

re:					fclean all

norme:
					@norminette $(INC_DIR)/*
					@norminette $(SRC_DIR)/*

.PHONY:				all clean fclean re norme
