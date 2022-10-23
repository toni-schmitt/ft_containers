CXX = c++
CXXFLAGS = -std=c++98 -Wall -Werror -Wextra

FT_BIN = ./ft
STD_BIN = ./std

SRC_DIR = ./src
OBJ_DIR = ./obj

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

all: ft_containers std_containers

ft_containers:
	@$(MAKE) clean
	@$(MAKE) $(FT_BIN)

std_containers:
	@$(MAKE) clean
	@$(MAKE) $(STD_BIN)

$(FT_BIN): TYPE=-DTYPE=int
$(FT_BIN): NAMESPACE=-DFT=1
$(FT_BIN): INCFLAGS=-I../ft_containers/
$(FT_BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $< -o $@

$(STD_BIN): NAMESPACE=-DSTD=1
$(STD_BIN): TYPE=-DTYPE=int
$(STD_BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(TYPE) $(NAMESPACE) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(FT_BIN)
	$(RM) $(STD_BIN)

re: fclean all

.PHONY: all ft_containers std_containers clean fclean re
