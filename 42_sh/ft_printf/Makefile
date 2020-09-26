# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/05 23:35:56 by dthan             #+#    #+#              #
#    Updated: 2020/09/26 02:51:52 by dthan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS_DIR = srcs

LIBFT_DIR = libft

SRCS_CODES = $(addprefix $(SRCS_DIR)/, core.c parsing.c printing.c \
parsing/fill_struct.c parsing/parsing_helper.c \
printing/nbr_to_str.c printing/width_control.c printing/percision_control.c \
printing/flag_control.c printing/printing_helper.c \
printing/type_c.c printing/type_di.c printing/type_f.c printing/type_o.c \
printing/type_p.c printing/type_s.c printing/type_u.c printing/type_hex.c \
printing/type_percent.c)

LIBFT_CODES = $(addprefix $(LIBFT_DIR)/, ft_isdigit.c ft_strlen.c\
ft_strchr.c ft_strdup.c ft_memset.c ft_memalloc.c ft_bzero.c \
ft_itoa.c ft_strjoin.c ft_strcpy.c ft_strcat.c ft_strnew.c ft_strcmp.c ft_strncpy.c\
ft_toupper.c ft_isalnum.c ft_strrev.c)

SRCS_OBJ = core.o parsing.o printing.o \
fill_struct.o parsing_helper.o \
nbr_to_str.o width_control.o percision_control.o flag_control.o \
printing_helper.o \
type_c.o type_di.o type_f.o type_o.o type_p.o type_s.o type_u.o type_hex.o \
type_percent.o \


LIBFT_OBJ = ft_isdigit.o ft_strlen.o\
ft_strchr.o ft_strdup.o ft_memset.o ft_memalloc.o ft_bzero.o \
ft_itoa.o ft_strjoin.o ft_strcpy.o ft_strcat.o ft_strnew.o ft_strcmp.o ft_strncpy.o\
ft_toupper.o ft_isalnum.o ft_strrev.o

INCLUDES = includes/

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -c -I$(INCLUDES) $(SRCS_CODES) $(LIBFT_CODES) -g
	@ar rc $(NAME) *.o
	@ranlib $(NAME)

clean:
	@rm -f $(SRCS_OBJ) $(LIBFT_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
