# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 10:40:40 by chrrodri          #+#    #+#              #
#    Updated: 2025/02/18 11:09:43 by chrrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              Project Information                             #
# **************************************************************************** #
NAME 			= philo

# **************************************************************************** #
#                            Compiler and Flags                                #
# **************************************************************************** #
CC 				= gcc
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address,undefined -O0
RM				= rm -rf
MAKE			= make

# **************************************************************************** #
#                              Directories                                     #
# **************************************************************************** #
SRC_DIR 		= src
INC_DIR 		= include

# **************************************************************************** #
#                      File Paths and Dependencies                             #
# **************************************************************************** #
MAKEFILE 		= Makefile
HEADER 			= $(INC_DIR)/philo.h
DEPS 			= $(HEADER) $(MAKEFILE)

# **************************************************************************** #
#                               Source File                                    #
# **************************************************************************** #
SRC 		:= $(SRC_DIR)/core/main.c \
               $(SRC_DIR)/parsing/parse_strict_atoi.c \
               $(SRC_DIR)/error_handling/fatal_error.c \
               $(SRC_DIR)/utils/free_2d_array.c \
               $(SRC_DIR)/utils/free_map.c \
               $(SRC_DIR)/utils/free_fdf.c \
               $(SRC_DIR)/utils/handle_exit.c \
               $(SRC_DIR)/utils/find_min_max_z.c \

# Object files
OBJ			= $(SRC:.c=.o)

# **************************************************************************** #
#                              Targets                                         #
# **************************************************************************** #

# All rule: Compile everything
all: $(NAME)

# Build fdf executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I$(INC_DIR) -o $(NAME)

# Rule to rebuild libft.a
$(LIBFT_A): $(LIBFT_MAKEFILE) $(LIBFT_SRCS) $(LIBFT_H)
	$(MAKE) -C $(LIBFT_DIR)

# Pattern rule for compiling object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean object files (including bonus objects)
clean:
	rm -f $(OBJ)

# Full clean including libft.a & fdf executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# **************************************************************************** #
#                             Special Rules                                    #
# **************************************************************************** #

# Phony targets
.PHONY: all clean fclean re
