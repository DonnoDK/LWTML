SOURCE_DIR := src/
SOURCES := $(wildcard $(SOURCE_DIR)*.cpp)
OBJECT_DIR := objects/
OBJECTS := $(addprefix $(OBJECT_DIR),$(notdir $(SOURCES:.cpp=.o)))
RELEASE_DIR := release/
TARGET := agm

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(RELEASE_DIR)
	@echo "[linking] $@"
	@g++ $(OBJECTS) -o $(RELEASE_DIR)$@

objects/%.o: $(SOURCE_DIR)%.cpp
	@mkdir -p $(OBJECT_DIR)
	@echo "[compiling] $<"
	@g++ -c $< -o $@

clean:
	@echo "[cleaning]"
	@rm -Rf $(RELEASE_DIR) $(OBJECT_DIR)
