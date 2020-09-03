CC		:= g++
CFLAGS	:= -Wall -std=c++17
LDFLAGS	:= -lpthread -lrt -lmodbus `mariadb_config --cflags --libs`
INCLUDE	:= -I/usr/include/mariadb -I/usr/local/include/modbus

BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/app

TARGET   := openNetworkHMI

SRC :=														\
	$(wildcard src/*.cpp)									\
	$(wildcard src/onh/db/*.cpp)							\
	$(wildcard src/onh/db/objs/*.cpp)						\
	$(wildcard src/onh/driver/*.cpp)						\
	$(wildcard src/onh/driver/Modbus/*.cpp)					\
	$(wildcard src/onh/driver/SHM/*.cpp)					\
	$(wildcard src/onh/thread/Alarming/*.cpp)				\
	$(wildcard src/onh/thread/DriverPolling/*.cpp)			\
	$(wildcard src/onh/thread/ProcessUpdater/*.cpp)			\
	$(wildcard src/onh/thread/Script/*.cpp)					\
	$(wildcard src/onh/thread/Socket/Parser/*.cpp)			\
	$(wildcard src/onh/thread/Socket/*.cpp)					\
	$(wildcard src/onh/thread/TagLogger/*.cpp)				\
	$(wildcard src/onh/thread/*.cpp)						\
	$(wildcard src/onh/utils/*.cpp)							\

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

DEPS := $(OBJECTS:%.o=%.d)

-include $(DEPS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) $(CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

all: build $(APP_DIR)/$(TARGET)
	cd test/tests; make all
	cd test/test_server1; make all
	cd test/test_server2; make all

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	
debug: CFLAGS += -DDEBUG -g
debug: build $(APP_DIR)/$(TARGET)
	cd test/tests; make debug
	cd test/test_server1; make debug
	cd test/test_server2; make debug

release: CFLAGS += -O2
release: build $(APP_DIR)/$(TARGET)
	cd test/tests; make release
	cd test/test_server1; make release
	cd test/test_server2; make release

clean:
	-@rm -rf $(BUILD)
	cd test/tests; make clean
	cd test/test_server1; make clean
	cd test/test_server2; make clean
	
.PHONY: all build clean debug release

