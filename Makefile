# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chonorat <chonorat@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 13:40:10 by chonorat          #+#    #+#              #
#    Updated: 2024/04/10 17:07:32 by chonorat         ###   ########.fr        #
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
INCLUDES =	-I ./Includes/				\
			-I ./Includes/Server		\
			-I ./Includes/Builders		\
			-I ./Includes/CacheManager	\
			-I ./Includes/Channel		\
			-I ./Includes/Commands		\
			-I ./Includes/Exceptions	\
			-I ./Includes/User			\
			-I ./Includes/Configuration \
			-I ./Includes/Replies

C++FLAGS = -Wall -Wextra -Werror $(INCLUDES) -std=c++98 -MD -g3
C++DFLAGS = -Wall -Wextra -Werror $(INCLUDES) -std=c++20 -MD -g3
RM = @rm -rf
DIR = @mkdir -p
PRINT = @echo
FILES =	Server/Server						\
		Configuration/Configuration			\
		Configuration/ConfigurationSection	\
		Exceptions/ChannelCacheException	\
		Exceptions/ChannelBuildException	\
		Exceptions/UserBuildException		\
		Exceptions/UserCacheException		\
		Exceptions/UserCacheExceptionString	\
		Exceptions/UserConnectionException	\
		Exceptions/ConfigurationIOException	\
		Exceptions/ServerStartingException	\
		Exceptions/ServerInitializationException	\
		Utils/PrimitivePredicate			\
		Utils/IRCPredicate					\
		Utils/StringUtils					\
		Utils/IrcLogger						\
		Utils/Colors						\
		Utils/FileUtils						\
		Models/User/User					\
		Models/User/UserProperties			\
		Models/Channel/ChannelProperties	\
		Models/Channel/Channel				\
		CacheManager/ChannelCacheManager	\
		CacheManager/UsersCacheManager		\
		Builders/UserBuilder				\
		Builders/ChannelBuilder				\
		Helpers/UserListHelper				\
		Replies/NumericReplies

MAIN_FILES =	$(FILES)	\
				main
DEBUG_FILES =	$(FILES)	\
				Tests/Tests
OBJS = $(addsuffix .o, $(addprefix Objects/, $(MAIN_FILES)))
DPDS = $(addsuffix .d, $(addprefix Objects/, $(MAIN_FILES)))
DEBUG_OBJS = $(addsuffix .o, $(addprefix Objects/, $(DEBUG_FILES)))
DEBUG_DPDS = $(addsuffix .d, $(addprefix Objects/, $(DEBUG_FILES)))

DEBUG = false

$(NAME): $(OBJS)
	$(PRINT) "\n${_YELLOW}Making $(NAME)...${_END}"
	$(CC) $(OBJS) -o $(NAME)
	$(PRINT) "${_BOLD}${_GREEN}$(NAME) done.\a${_END}"

debug: fclean $(DEBUG_OBJS)
ifeq ($(DEBUG), true)
	$(PRINT) "\n${_BOLD}${_YELLOW}DEBUG${_END}"
	$(PRINT) "\n${_YELLOW}Making $(NAME)...${_END}"
	$(CC) $(DEBUG_OBJS) -o $(NAME)
	$(PRINT) "${_BOLD}${_GREEN}$(NAME) done.\a${_END}"
else
	$(PRINT) "${_RED}DEBUG USAGE: make debug DEBUG=true${_END}"
endif

Objects/%.o: Sources/%.cpp Makefile
	$(DIR) Objects/Builders Objects/Exceptions Objects/Server Objects/Configuration Objects/Models/Channel Objects/Models/User Objects/CacheManager Objects/Utils Objects/Helpers Objects/Replies
	$(PRINT) "Compiling ${_BOLD}$<$(_END)..."
ifeq ($(DEBUG), true)
	$(DIR) Objects/Tests
	$(CC) -c $(C++DFLAGS) $< -o $@
else
	$(CC) -c $(C++FLAGS) $< -o $@
endif

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

exec : all
		./ircserv 7777 434

.PHONY: all clean fclean re

-include $(DPDS)