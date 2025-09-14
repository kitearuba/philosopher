# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 10:40:40 by chrrodri          #+#    #+#              #
#    Updated: 2025/09/14 23:12:05 by chrrodri         ###   ########.fr        #
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
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -rf
THREADS			= -pthread

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
			   $(SRC_DIR)/init/init_philos.c \
               $(SRC_DIR)/init/safe_atoi.c \
               $(SRC_DIR)/simulation/launch.c \
               $(SRC_DIR)/simulation/monitor.c \
               $(SRC_DIR)/simulation/simulation_end.c \
               $(SRC_DIR)/simulation/routine.c \
               $(SRC_DIR)/simulation/fork_handling.c \
			   $(SRC_DIR)/simulation/cycle.c \
               $(SRC_DIR)/utils/time.c \
               $(SRC_DIR)/utils/print.c \
               $(SRC_DIR)/utils/ft_usleep.c \
               $(SRC_DIR)/utils/cleanup.c

# Object files
OBJ			= $(SRC:.c=.o)

# **************************************************************************** #
#                              Targets                                         #
# **************************************************************************** #

# All rule: Compile everything
all: $(NAME)

# Build philo executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I$(INC_DIR) $(THREADS) -o $(NAME)

# Pattern rule for compiling object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(THREADS) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJ)

# Full clean
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

debug: CFLAGS += -g -fsanitize=thread -O2
debug: re

asan: CFLAGS += -g -fsanitize=address,undefined -O2
asan: re

# **************************************************************************** #
#                             Special Rules                                    #
# **************************************************************************** #

# Phony targets
.PHONY: all clean fclean re debug asan
