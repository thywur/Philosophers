# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alermolo <alermolo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 19:17:58 by alermolo          #+#    #+#              #
#    Updated: 2024/03/22 11:57:54 by alermolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--variables-------------------------------------------------------------------#

NAME		=	philo
DEBUG		=	no
BONUS		=	no

#--includes & libraries--------------------------------------------------------#

INC_DIR			=	includes/
B_INC_DIR		=	bonus/includes_bonus/
HEADERS 		=	includes/philosophers.h

#--sources & objects-----------------------------------------------------------#

SRC_DIR		=		srcs/
B_SRC_DIR	=		bonus/srcs_bonus
OBJ_DIR		=		.objects
SOURCES 	=		srcs/main.c			\
					srcs/init.c	\
					srcs/free.c		\
					srcs/utils.c		\
					srcs/routine.c	\
					srcs/death_check.c	\
					srcs/eat_sleep.c	\
					srcs/time.c

#--compilator------------------------------------------------------------------#

CC			=	gcc

#--flags-----------------------------------------------------------------------#

CFLAGS		=	-Wall -Wextra -Werror -pthread -O3 -I $(INC_DIR)

DFLAGS		=	-g3 -fsanitize=thread

#--debug & define flags--------------------------------------------------------#

ifeq ($(DEBUG), yes)
CFLAGS 		+=	$(DFLAGS)
endif

#--objects---------------------------------------------------------------------#

OBJECTS	=	$(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

#--global rules----------------------------------------------------------------#

.DEFAULT_GOAL = all

#--compilation rules-----------------------------------------------------------#

all:
	$(MAKE) $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $^ $(CFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#--libs, debugs & bonus--------------------------------------------------------#

debug:
	$(MAKE) re DEBUG=yes

#--re, clean & fclean----------------------------------------------------------#

re:
	$(MAKE) fclean
	$(MAKE) all

clean:
	$(RM) -rf $(OBJECTS)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)

#--PHONY-----------------------------------------------------------------------#

.PHONY: all debug re clean fclean
