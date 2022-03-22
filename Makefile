CC = g++
CFLAGS =  -Wall -g -fsanitize=address,undefined
LINKER_FLAG = -lstdc++ -pthread -lncurses

BUILD_PATH = ./build
TESTS_PATH = ./tests
HEADERS = ./include
SRC = ./src

headers = $(shell find $(HEADERS)/ -type d) 
HEADER_FLAGS = $(addprefix -I, $(headers))

sources = $(shell find $(SRC)/ -type f -name '*.cpp')
OBJS_NO_BUILD_PATH := $(patsubst %.cpp, %.o, $(sources))
OBJS = $(addprefix $(BUILD_PATH)/, $(OBJS_NO_BUILD_PATH))
TESTS = $(shell find $(TESTS_PATH)/ -type f ! -name "test-template.cpp")

#build command
main:  $(OBJS) 
	$(CC) $(CFLAGS) $(HEADER_FLAGS) $^ $(LINKER_FLAG)  -o $(BUILD_PATH)/$@



.PHONY: tests
# make tests TESTS="tests/binary-tree.cpp" per fare un solo test
tests: $(filter-out %main.o, $(OBJS))
	@for file in $(TESTS); 													\
	do																					\
		echo "Compilando il file : $${file}";											\
		$(CC) $(CFLAGS) $(HEADER_FLAGS) -c $${file} -o "$${file%.cpp}.o";							\
		$(CC) $(CFLAGS) $(HEADER_FLAGS) $^ "$${file%.cpp}.o" $(LINKER_FLAG) -o ./out; 	\
		./out;																			\
		rm $${file%.cpp}.o;																\
	done
	@rm ./out 

$(OBJS): $(BUILD_PATH)/%.o : %.cpp 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_FLAGS) $< -c -o $@


# delete prev build and build
remake: clean main

# delete previus build , build the new one and run it
rerun: clean run

# remove the last build
clean:
	rm $(OBJS) || true

# build and run the program
run: main
	$(BUILD_PATH)/$<
