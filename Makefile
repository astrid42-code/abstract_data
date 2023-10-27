# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 12:29:31 by asgaulti          #+#    #+#              #
#    Updated: 2022/10/26 17:24:51 by asgaulti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	containers

CXX			=	c++

CXXFLAGS	=	-Wall -Wextra -Werror -MMD -MP --std=c++98 -g3 # MMD MP -> linkage
# CXXFLAGS	+=	-fsanitize=address 

M_STD		=	-D STD
M_FT		=	-D FT


RM			=	rm -f

# SRCS		= 	main_deque.cpp
SRCS		=	main.cpp
# SRCS		=	main_mmap.cpp
# SRCS		=	main_map.cpp
# SRCS		=	main_vector.cpp
# SRCS		=	main_stack.cpp
# SRCS		=	main_set.cpp
# SRCS		=	main42.cpp

INC			=	includes

OBJS_FILE	=	$(SRCS:.cpp=.o)
DEPS_FILE	=	$(SRCS:.cpp=.d)

.c.o:
			$(CXX) $(CXXFLAGS) -I $(INC) -g -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS_FILE)
			$(CXX) $(CXXFLAGS) $(OBJS_FILE) -o $(NAME)

all:		$(NAME)

std:
			$(eval CXXFLAGS += $(M_STD))
			$(CXX) $(CXXFLAGS) -I $(INC) -g -c $(SRCS) -o $(OBJS_FILE)
			$(CXX) $(CXXFLAGS) $(OBJS_FILE) -o $(NAME)

ft:			$(OBJS_FILE)
			$(eval CXXFLAGS += $(M_FT))
			$(CXX) $(CXXFLAGS) -I $(INC) -g -c $(SRCS) -o $(OBJS_FILE)
			$(CXX) $(CXXFLAGS) $(OBJS_FILE) -o $(NAME) 

clean:
			$(RM) $(OBJS_FILE) $(DEPS_FILE) test_std test_ft

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

-include : $(DEPS_FILE)

.PHONY:		all clean fclean re