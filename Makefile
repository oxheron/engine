TARGET_EXEC = libEngine.a
CC = clang++
LD = ar

DEBUG = 1

SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = bin

INC_DIR_SRC = -Isrc 
INC_DIR_LIB = -Ilib -Ilib/engine -Ilib/engine/lib/json/single_include -Ilib/engine/lib/bgfx/include -Ilib/engine/lib/bimg/include -Ilib/engine/lib/bx/include -Ilib/engine/lib/glfw/include -Ilib/engine/lib/cgltf/include -Ilib/engine/glm

DEBUGFLAGS = $(INC_DIR_SRC) $(INC_DIR_LIB) -Wall -g -DDEBUG=1 -DBX_CONFIG_DEBUG=1
RELEASEFLAGS = $(INC_DIR_SRC) $(INC_DIR_LIB) -O2 -DBX_CONFIG_DEBUG=0
ifeq ($(DEBUG), 1)
	CFLAGS = $(DEBUGFLAGS)
else
	CFLAGS = $(RELEASEFLAGS)
endif
LDFLAGS = rcs 

.PHONY: all clean  

all: clean 
	$(MAKE) -j8 bld
	$(MAKE) link

dirs:
	mkdir -p ./$(BIN)

link: $(OBJ)
	$(AR) $(LDFLAGS) $(BIN)/$(TARGET_EXEC) $^ 

bld: 
	$(MAKE) dirs
	$(MAKE) obj

obj: $(OBJ)

%.o: %.cpp
	$(CC) -std=c++20 -o $@ -c $< $(CFLAGS)

headers:
	python3 scripts/headers_to_lib.py

clean:
	clear
	rm -rf $(BIN) $(OBJ)
