CC = g++
#CC = clang
CFLAGS =  -Wall -g
#CPPFLAGS = $(HEADER_FLAGS) -lncurses -lstdc++ -lpthread
CPPFLAGS = $(HEADER_FLAGS) -lncurses -lstdc++ -pthread

BUILD_FOLD = ./build
HEADERS = ./include
SRC = ./src

headers = $(shell find $(HEADERS)/ -type d)
HEADER_FLAGS = $(addprefix -I, $(headers))

sources = $(shell find $(SRC)/ -type f -name '*.cpp')
OBJS := $(patsubst %.cpp,%.o,$(sources))

main:  $(OBJS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(addprefix $(BUILD_FOLD)/, $(OBJS)) -o $(BUILD_FOLD)/$@

%.o : %.cpp 
	@mkdir -p $(BUILD_FOLD)/$(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $(BUILD_FOLD)/$@

clean:
	rm $(addprefix $(BUILD_FOLD)/, $(OBJS))

run: main
	$(BUILD_FOLD)/$<