CC = g++
CFLAGS =  -Wall -g
LINKER_FLAG = -lstdc++ -pthread -lncurses

BUILD_PATH = ./build
HEADERS = ./include
SRC = ./src

headers = $(shell find $(HEADERS)/ -type d) 
HEADER_FLAGS = $(addprefix -I, $(headers))

sources = $(shell find $(SRC)/ -type f -name '*.cpp')
OBJS_NO_BUILD_PATH := $(patsubst %.cpp,%.o,$(sources))
OBJS = $(addprefix $(BUILD_PATH)/, $(OBJS_NO_BUILD_PATH))

#build command
main:  $(OBJS) 
	$(CC) $(CFLAGS) $(HEADER_FLAGS) $(OBJS) $(LINKER_FLAG)  -o $(BUILD_PATH)/$@

$(OBJS): $(BUILD_PATH)/%.o : %.cpp 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_FLAGS) $< -c -o $@


# delete prev build and build
remake: clean main

# delete previus build , build the new one and run it
rerun: clean run

# remove the last build
clean:
	rm $(OBJS) ||true

# build and run the program
run: main
	$(BUILD_PATH)/$<
