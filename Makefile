CC = clang
CFLAGS =  -std=c++11 -Wall
CPPFLAGS = -I$(HEADERS) -lncurses -lstdc++ -lpthread

BUILD_FOLD = ./build
HEADERS = ./include
SRC = ./src

sources = $(shell find $(SRC)/ -type f -name '*.cpp')
OBJS := $(patsubst %.cpp,%.o,$(sources))

# https://stackoverflow.com/questions/54192234/recursive-search-in-vpath
VPATH := $(subst " ",:,$(shell find $(SRC) -type d)):$(subst " ",:,$(shell find $(HEADERS) -type d))

main: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(addprefix $(BUILD_FOLD)/, $(OBJS)) -o $(BUILD_FOLD)/$@

%.o : %.cpp
	mkdir -p $(BUILD_FOLD)/$(@D)
	$(CC) $(CFLAGS) $< -c -o $(BUILD_FOLD)/$@

clean:
	rm $(addprefix $(BUILD_FOLD)/, $(OBJS))

