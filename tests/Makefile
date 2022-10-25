CXX = c++
CXXFLAGS = -std=c++98 -Wall -Werror -Wextra -g
INCFLAGS=-I../ft_containers/

BIN = ./containers_tester

SRC_DIR = ./src
OBJ_DIR = ./obj

SOURCES = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(BIN)
	$(RM) -rf ./logs
	mkdir ./logs


$(BIN): TYPE=-DTYPE=int
$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $< -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(TYPE) -c $< -o $@

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
	@echo "Usage:"
	@echo "Run all Tests: make test"
	@echo "Run Test for specific Container: make test C=[Container]"
	@echo "Run specific Test for specific Container: make test C=[Container] T=[Test]"
	@echo "Run specific Test for all Containers: make test T=[Test]"

vector: C=vector
vector: test

map: C=map
map: test

set: C=set
set: test

stack: C=stack
stack: test

.PHONY: all clean fclean re test help vector map set stack
