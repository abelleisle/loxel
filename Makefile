SRC_DIR = src
OBJ_DIR = out
DIR_CRT = mkdir -p $(@D)

#SRC_FILES = $(wildcard **/*.cpp)
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

FLAGS = -m64 -std=c++17 -Wall -Werror -Wextra -Wpedantic -g
REL_FLAGS = -O2
LIBS = -Llib -llua5.3 -lpthread -lglfw -lGL -lGLEW -lfreetype
INCS = -Isrc -Ilib

EXEC = loxel

$(EXEC): $(OBJ_FILES)
	@echo "exec:	$@\n	$^"
	@g++ $(FLAGS) $(LIBS) $(INCS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(DIR_CRT)
	@echo "src:	$<"
	@g++ $(FLAGS) $(LIBS) $(INCS) -c $< -o $@

clean:
	rm -r $(OBJ_DIR)
