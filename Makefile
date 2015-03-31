SOURCE_DIR := src/
SOURCES := $(wildcard $(SOURCE_DIR)*.cpp)
OBJECT_DIR := objects/
OBJECTS := $(addprefix $(OBJECT_DIR),$(notdir $(SOURCES:.cpp=.o)))
BUILD_DIR := lib/
TARGET := libLWTML.dylib
CC := clang++

all: $(TARGET)

install:
	@echo "[installing] target paths: /usr/local/lib and /usr/local/include/LWTML"
	@mkdir -p /usr/local
	@mkdir -p /usr/local/lib
	@mkdir -p /usr/local/include/LWTML
	@cp ./lib/libLWTML.dylib /usr/local/lib/
	@cp ./include/*.hpp /usr/local/include/LWTML/

$(TARGET): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	@echo "[linking] $@"
	@clang++ -dynamiclib $(SOURCES) -o $(BUILD_DIR)$@

clean:
	@echo "[cleaning]"
	@rm -Rf $(BUILD_DIR) $(OBJECT_DIR)
	@rm -Rf ./release ./examples/*.o

examples: game_of_life

game_of_life: objects/game_of_life.o
	@echo "compliling examples"
	@mkdir -p release
	@clang++ $< -o ./release/game_of_life -lLWTML

objects/game_of_life.o: examples/game_of_life.cpp
	@mkdir -p objects
	@clang++ -c $< -o objects/game_of_life.o

uninstall:
	@echo "removing lib and headers"
	@rm -Rf /usr/local/lib/libLWTML.dylib
	@rm -Rf /usr/local/include/LWTML
	@rm -Rf objects release
