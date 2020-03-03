CC		:= gcc
CFLAGS	:= -Wall
INCLUDE	:= -Iinclude/

BUILD    := ./build
LIB_NAME := onhSHMc
LIB_FULL_NAME := lib$(LIB_NAME).a
OBJ_DIR  := $(BUILD)/objects
LIB_DIR  := $(BUILD)/lib
LIB_PATH := $(LIB_DIR)/$(LIB_FULL_NAME)

SRC :=							\
	$(wildcard src/*.c)			\

OBJECTS := $(SRC:%.c=$(OBJ_DIR)/%.o)

DEPS := $(OBJECTS:%.o=%.d)

-include $(DEPS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) $(CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

$(LIB_PATH): $(OBJECTS)
	ar rcs $@ $+

all: build $(OBJECTS) $(LIB_PATH)
	cd test; make all

build:
	@mkdir -p $(LIB_DIR)
	@mkdir -p $(OBJ_DIR)
	
debug: CFLAGS += -DDEBUG -g
debug: build $(OBJECTS) $(LIB_PATH)
	cd test; make debug

release: CFLAGS += -O2
release: build $(OBJECTS) $(LIB_PATH)
	cd test; make release

clean:
	-@rm -rf $(BUILD)
	cd test; make clean

install:
	-@cp -r include/$(LIB_NAME) /usr/local/include/
	-@cp $(LIB_PATH) /usr/lib/
	-@ln -s /usr/lib/$(LIB_FULL_NAME) /usr/local/lib/

uninstall:
	-@rm -rf /usr/local/include/$(LIB_NAME)
	-@rm -f /usr/local/lib/$(LIB_FULL_NAME)
	-@rm -f /usr/lib/$(LIB_FULL_NAME)
	
.PHONY: all build clean debug release

