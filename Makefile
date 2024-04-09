# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 13:40:10 by chonorat          #+#    #+#              #
#    Updated: 2024/04/05 13:42:25 by chonorat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLOR
_GREEN = \033[92m
_YELLOW = \033[33m
_RED = \033[31m

#POLICE
_END = \033[0m
_BOLD = \033[1m

NAME = ircserv
CC = @c++
C++FLAGS = -Wall -Wextra -Werror		\
 -I ./Includes/							\
 -I ./Includes/Channel					\
 -I ./Includes/Commands					\
 -I ./Includes/User						\
 -std=c++98 -MD -g3
RM = @rm -rf
DIR = @mkdir -p
PRINT = @echo
FILES = main								\
 		Server								\
		Exceptions/ChannelCreationException	\
		Exceptions/ChannelNotFoundException	\
		Exceptions/ChannelDeletionException \
		Exceptions/ChannelModificationException \
		Utils/PrimitivePredicate			\
		Utils/IRCPredicate					\
		Models/User/User					\
		Models/User/UserProperties			\
		Models/Channel/ChannelProperties	\
		Models/Channel/Channel				\
		Managers/ChannelManager
OBJS = $(addsuffix .o, $(addprefix Objects/, $(FILES)))
DPDS = $(addsuffix .d, $(addprefix Objects/, $(FILES)))

$(NAME): $(OBJS)
	$(PRINT) "\n${_YELLOW}Making $(NAME)...${_END}"
	$(CC) -I ./Includes/ $(OBJS) -o $(NAME)
	$(PRINT) "${_BOLD}${_GREEN}$(NAME) done.\a${_END}"

Objects/%.o: Sources/%.cpp Makefile
	$(DIR) Objects Objects/Exceptions Objects/Models/Channel Objects/Models/User Objects/Managers Objects/Utils Objects/Tests
	$(PRINT) "Compiling ${_BOLD}$<$(_END)..."
	$(CC) -c $(C++FLAGS) $< -o $@

all: $(NAME)

clean:
	$(PRINT) "\n${_BOLD}Cleaning Objects...${_END}"
	$(PRINT) "${_BOLD}${_GREEN}Objects cleaned.\a${_END}"

fclean:
	$(PRINT) "\n${_RED}Cleaning Objects...${_END}"
	$(PRINT) "${_RED}Deleting Objects directory...${_END}"
	$(RM) Objects
	$(PRINT) "${_RED}Deleting $(NAME)...${_END}"
	$(RM) $(NAME)
	$(PRINT) "${_GREEN}Objects cleaned.${_END}"
	$(PRINT) "${_GREEN}Objects directory deleted.${_END}"
	$(PRINT) "${_GREEN}$(NAME) deleted.\a\n${_END}"

re: fclean all

.PHONY: all clean fclean re

-include $(DPDS)