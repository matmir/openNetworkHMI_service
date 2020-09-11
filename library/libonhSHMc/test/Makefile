CC		:= g++
CFLAGS	:= -Wall -std=c++17
LDFLAGS	:= -lgtest -lpthread -lrt
INCLUDE	:= -I"../include"

BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/app

TARGET   := libOnhSHMc_test

SRC1 :=														\
	$(wildcard src/*.cpp)									\

SRC2 :=														\
	$(wildcard ../src/*.c) 									\

VPATH := $(dir $(SRC1))
VPATH += $(dir $(SRC2))
OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC1)))
OBJECTS += $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC2)))

DEPS := $(OBJECTS:%.o=%.d)

-include $(DEPS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) $(CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) $(CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(LDFLAGS)

all: build $(APP_DIR)/$(TARGET)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	
debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O2
release: all

clean:
	-@rm -rf $(BUILD)
	
.PHONY: all build clean debug release

