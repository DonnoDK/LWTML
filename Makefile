SOURCE_DIR := src/
SOURCES := $(wildcard $(SOURCE_DIR)*.cpp)
OBJECT_DIR := objects/
OBJECTS := $(addprefix $(OBJECT_DIR),$(notdir $(SOURCES:.cpp=.o)))
BUILD_DIR := lib/
TARGET := libLWTML.dylib
CC := clang++

all: $(TARGET)

install:
	@echo "[installing] target path: /usr/lib"
	@cp ./lib/libLWTML.dylib /usr/lib
	@mkdir -p /usr/include/LWTML
	@cp ./include/*.hpp /usr/include/LWTML

$(TARGET): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	@echo "[linking] $@"
	@clang++ -dynamiclib $(SOURCES) -o $(BUILD_DIR)$@

objects/%.o: $(SOURCE_DIR)%.cpp
	@mkdir -p $(OBJECT_DIR)
	@echo "[compiling] $<"
	@$(CC) $< -o $@

clean:
	@echo "[cleaning]"
	@rm -Rf $(BUILD_DIR) $(OBJECT_DIR)
	@rm -Rf ./release ./examples/*.o

release: ./examples/game_of_life.o
	@echo "compliling examples"
	@mkdir -p release
	@clang++ $< -o ./release/game_of_life -lLWTML

./examples/game_of_life.o: ./examples/game_of_life.cpp
	@clang++ -c $< -o ./examples/game_of_life.o
