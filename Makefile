CC := g++
FLAGS := -std=c++11 -g
INC_DIR := include
SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/FamilyTree: $(BUILD_DIR)/FamilyTree.o $(BUILD_DIR)/FamilyManager.o
	mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@

$(BUILD_DIR)/FamilyTree.o: $(SRC_DIR)/FamilyTree.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $^ -c -o $@

$(BUILD_DIR)/FamilyManager.o: $(SRC_DIR)/FamilyManager.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $^ -c -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
