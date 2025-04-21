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
CC 				= cc
CFLAGS			= -Wall -Wextra -Werror #-g -fsanitize=address,undefined -O0
RM				= rm -rf

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
               $(SRC_DIR)/init/init.c \
               $(SRC_DIR)/init/safe_atoi.c \
               $(SRC_DIR)/simulation/ft_usleep.c \
               $(SRC_DIR)/simulation/monitor.c \
               $(SRC_DIR)/simulation/print.c \
               $(SRC_DIR)/simulation/routine.c \
               $(SRC_DIR)/simulation/time.c \
               $(SRC_DIR)/simulation/simulation_end.c \
               $(SRC_DIR)/utils/cleanup.c \

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

# Pattern rule for compiling object files
$%.o: $%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJ)

# Full clean
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

# **************************************************************************** #
#                             Special Rules                                    #
# **************************************************************************** #

# Phony targets
.PHONY: all clean fclean re
