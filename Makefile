# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 21:23:07 by chrrodri          #+#    #+#              #
#    Updated: 2025/02/02 23:29:43 by chrrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              Project Information                             #
# **************************************************************************** #
NAME 			= fdf

# **************************************************************************** #
#                            Compiler and Flags                                #
# **************************************************************************** #
CC 				= gcc
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address,undefined -O0
MLXi			= -L./minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm
RM				= rm -rf
MAKE			= make

# **************************************************************************** #
#                              Directories                                     #
# **************************************************************************** #
SRC_DIR 		= src
INC_DIR 		= include
LIBFT_DIR		= libft

# **************************************************************************** #
#                      File Paths and Dependencies                             #
# **************************************************************************** #
MAKEFILE 		= Makefile
HEADER 			= $(INC_DIR)/fdf.h $(INC_DIR)/fdf_macros.h \
					$(INC_DIR)/fdf_structs.h
LIBFT_A 		= $(LIBFT_DIR)/libft.a
LIBFT_H 		= $(LIBFT_DIR)/$(INC_DIR)/libft.h
LIBFT_MAKEFILE 	= $(LIBFT_DIR)/$(MAKEFILE)
DEPS 			= $(HEADER) $(MAKEFILE) $(LIBFT_MAKEFILE) $(LIBFT_SRCS) $(LIBFT_H)

# **************************************************************************** #
#                               Source File                                    #
# **************************************************************************** #
SRC 		:= $(SRC_DIR)/core/main.c \
               $(SRC_DIR)/parsing/parse.c \
               $(SRC_DIR)/parsing/parse_utils.c \
               $(SRC_DIR)/parsing/parse_strict_atoi.c \
               $(SRC_DIR)/parsing/validate_dimensions.c \
               $(SRC_DIR)/error_handling/fatal_error.c \
               $(SRC_DIR)/error_handling/free_on_error.c \
               $(SRC_DIR)/error_handling/parse_error.c \
               $(SRC_DIR)/utils/free_2d_array.c \
               $(SRC_DIR)/utils/free_map.c \
               $(SRC_DIR)/utils/free_fdf.c \
               $(SRC_DIR)/utils/handle_exit.c \
               $(SRC_DIR)/utils/find_min_max_z.c \
               $(SRC_DIR)/setup/init_fdf.c \
               $(SRC_DIR)/setup/init_window.c \
               $(SRC_DIR)/render/render.c \
               $(SRC_DIR)/render/transform_3d_to_2d.c \
               $(SRC_DIR)/render/draw_line.c \
               $(SRC_DIR)/render/handle_keys.c \
               $(SRC_DIR)/render/update_frame.c \
               $(SRC_DIR)/render/bresenham_draw.c \
               $(SRC_DIR)/render/color_utils.c \

# Object files
OBJ			= $(SRC:.c=.o)

# Libft files to use for time stamp check
LIBFT_SRCS := $(LIBFT_DIR)/$(SRC_DIR)/ft_isalpha.c $(LIBFT_DIR)/$(SRC_DIR)/ft_isdigit.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_isalnum.c $(LIBFT_DIR)/$(SRC_DIR)/ft_isascii.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_isprint.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strlen.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_memset.c $(LIBFT_DIR)/$(SRC_DIR)/ft_bzero.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_memcpy.c $(LIBFT_DIR)/$(SRC_DIR)/ft_memmove.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strlcpy.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strlcat.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_toupper.c $(LIBFT_DIR)/$(SRC_DIR)/ft_tolower.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strchr.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strrchr.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strncmp.c $(LIBFT_DIR)/$(SRC_DIR)/ft_memchr.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_memcmp.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strnstr.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_atoi.c $(LIBFT_DIR)/$(SRC_DIR)/ft_calloc.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strdup.c $(LIBFT_DIR)/$(SRC_DIR)/ft_substr.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strjoin.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strtrim.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_split.c $(LIBFT_DIR)/$(SRC_DIR)/ft_itoa.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_strmapi.c $(LIBFT_DIR)/$(SRC_DIR)/ft_striteri.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_putchar_fd.c $(LIBFT_DIR)/$(SRC_DIR)/ft_putstr_fd.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_putendl_fd.c $(LIBFT_DIR)/$(SRC_DIR)/ft_putnbr_fd.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_lstnew_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_lstadd_front_bonus.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_lstsize_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_lstlast_bonus.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_lstadd_back_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_lstdelone_bonus.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_lstclear_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_lstiter_bonus.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_lstmap_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_printf.c \
             $(LIBFT_DIR)/$(SRC_DIR)/print_format.c $(LIBFT_DIR)/$(SRC_DIR)/ft_putunbr.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_puthex.c $(LIBFT_DIR)/$(SRC_DIR)/handle_char.c \
             $(LIBFT_DIR)/$(SRC_DIR)/handle_string.c $(LIBFT_DIR)/$(SRC_DIR)/handle_pointer.c \
             $(LIBFT_DIR)/$(SRC_DIR)/handle_int.c $(LIBFT_DIR)/$(SRC_DIR)/handle_uint.c \
             $(LIBFT_DIR)/$(SRC_DIR)/handle_hex.c $(LIBFT_DIR)/$(SRC_DIR)/handle_percent.c \
             $(LIBFT_DIR)/$(SRC_DIR)/utils.c $(LIBFT_DIR)/$(SRC_DIR)/get_next_line.c \
             $(LIBFT_DIR)/$(SRC_DIR)/get_next_line_bonus.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strappend.c \
             $(LIBFT_DIR)/$(SRC_DIR)/ft_atoi_base.c $(LIBFT_DIR)/$(SRC_DIR)/ft_strtol.c \

LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

# **************************************************************************** #
#                              Targets                                         #
# **************************************************************************** #

# All rule: Compile everything
all: $(NAME)

# Build fdf executable
$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(MLXi) -I$(INC_DIR) -o $(NAME)

# Rule to rebuild libft.a
$(LIBFT_A): $(LIBFT_MAKEFILE) $(LIBFT_SRCS) $(LIBFT_H)
	$(MAKE) -C $(LIBFT_DIR)

# Pattern rule for compiling object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean object files (including bonus objects)
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean including libft.a & fdf executable
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_A)

# Rebuild everything
re: fclean all

# **************************************************************************** #
#                             Special Rules                                    #
# **************************************************************************** #

# Phony targets
.PHONY: all clean fclean re
