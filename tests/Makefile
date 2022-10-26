CXX = c++
CXXFLAGS = -std=c++98 -Wall -Werror -Wextra -g
INCFLAGS=-I../ft_containers/

BIN = ./containers_tester

SRC_DIR = ./src
OBJ_DIR = ./obj

SOURCES = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(BIN)


$(BIN): TYPE=-DTYPE=int
$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $< -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(BENCH) $(TYPE) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	$(RM) -r $(OBJ_DIR)

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
	@printf "\t'make test':\t\t\tRun all Tests\n"
	@printf "\t'make test C=[Container]':\tRun Test for specific Container\n"
	@printf "\t'make no_bench':\t\tRun all Tests without Benchmark\n"

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
