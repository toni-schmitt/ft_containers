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
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(TYPE) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(BIN)

re: fclean all

run: all
	$(BIN)

test: re run

.PHONY: all clean fclean re
