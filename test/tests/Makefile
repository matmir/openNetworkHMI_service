CC		:= g++
CFLAGS	:= -Wall -std=c++17
LDFLAGS	:= -lgtest -lpthread -lrt -lmodbus `mariadb_config --cflags --libs`
INCLUDE	:= -I/usr/include/mariadb -I/usr/local/include/modbus
INCLUDE += -I"../../src/onh" -I"../test_server1/src/controlBits" -I"../test_server2/src/controlBits"

BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/app

TARGET   := openNetworkHMI_test

SRC :=														\
	$(wildcard src/*.cpp)									\
	$(wildcard ../../src/onh/db/*.cpp) 						\
	$(wildcard ../../src/onh/db/objs/*.cpp) 				\
	$(wildcard ../../src/onh/driver/*.cpp) 					\
	$(wildcard ../../src/onh/driver/Modbus/*.cpp) 			\
	$(wildcard ../../src/onh/driver/SHM/*.cpp) 				\
	$(wildcard ../../src/onh/thread/Alarming/*.cpp) 		\
	$(wildcard ../../src/onh/thread/DriverPolling/*.cpp) 	\
	$(wildcard ../../src/onh/thread/ProcessUpdater/*.cpp)	\
	$(wildcard ../../src/onh/thread/Script/*.cpp) 			\
	$(wildcard ../../src/onh/thread/Socket/Parser/*.cpp) 	\
	$(wildcard ../../src/onh/thread/Socket/*.cpp) 			\
	$(wildcard ../../src/onh/thread/TagLogger/*.cpp) 		\
	$(wildcard ../../src/onh/thread/*.cpp) 					\
	$(wildcard ../../src/onh/utils/*.cpp) 					\

VPATH := $(dir $(SRC))
OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC)))

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

