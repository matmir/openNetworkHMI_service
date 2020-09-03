CC		:= g++
CFLAGS	:= -Wall -std=c++17
LDFLAGS	:= -lpthread -lrt -lmodbus
INCLUDE	:= -I/usr/local/include/modbus

BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/app

TARGET   := onh_test_server2

SRC :=														\
	$(wildcard src/*.cpp)									\
	$(wildcard src/controlBits/*.cpp)						\
	$(wildcard src/utils/*.cpp)								\

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

DEPS := $(OBJECTS:%.o=%.d)

-include $(DEPS)

$(OBJ_DIR)/%.o: %.cpp
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

