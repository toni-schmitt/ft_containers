# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tschmitt <tschmitt@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 19:38:06 by tschmitt          #+#    #+#              #
#    Updated: 2022/10/26 19:55:40 by tschmitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


##################################################
# Configure this to your ft_containers Directory #
	INCFLAGS=-I../ft_containers/
##################################################

CXX = c++
CXXFLAGS = -std=c++98 -Wall -Werror -Wextra -g

BIN = ./containers_tester

SRC_DIR = ./src
BUILD_DIR = ./build

SOURCES = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
DEPENDS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.d, $(SOURCES))

all: $(BIN)

-include $(DEPENDS)

$(BIN): TYPE=-DTYPE=int
$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $< -o $@


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP $(INCFLAGS) $(BENCH) $(TYPE) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(BIN)

.NOTPARALLEL:
re: fclean all

run: all
	$(BIN)

test: all
	$(BIN) $(C) $(CONTAINER) $(T) $(TEST)

help:
	@printf "Usage:\n"
	@printf "\t'make test':\t\t\t\tRun all Tests\n"
	@printf "\t'make test C=[Container]':\t\tRun Test for specific Container\n"
	@printf "\t'make test C=[Container] T=[Test]':\tRun specific Test for specific Container\n"
	@printf "\t'make no_bench':\t\t\tRun all Tests without Benchmark\n"

vector: C=vector
vector: test

map: C=map
map: test

set: C=set
set: test

stack: C=stack
stack: test

no_bench: BENCH=-DNO_BENCH
no_bench: re test

.PHONY: all clean fclean re test help vector map set stack no_bench
