CC = g++
CFLAGS = -Wall -Werror -g -fsanitize=address,undefined
DEBUG = -DDEBUG
LDFLAGS = -lstdc++ -pthread -lncurses -lasan

BUILD_PATH = ./build
TESTS_PATH = ./tests
SRC = ./src

INCLUDE_SRC = $(addprefix -I, $(SRC))

sources = $(shell find $(SRC)/ -type f -name '*.cpp')
OBJS_NO_BUILD_PATH := $(patsubst %.cpp, %.o, $(sources))
OBJS = $(addprefix $(BUILD_PATH)/, $(OBJS_NO_BUILD_PATH))
TESTS = $(shell find $(TESTS_PATH)/ -type f ! -name "test-template.cpp")

#build command
main:  $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDE_SRC) $^ $(LDFLAGS)  -o $(BUILD_PATH)/$@



.PHONY: tests
# make tests TESTS="tests/binary-tree.cpp" # esempio per fare un solo test
tests: $(filter-out %main.o, $(OBJS))
	@for file in $(TESTS); 													\
	do																					\
		echo "Compilando il file : $${file}";											\
		$(CC) $(CFLAGS) $(INCLUDE_SRC) -c $${file} -o "$${file%.cpp}.o";							\
		$(CC) $(CFLAGS) $(INCLUDE_SRC) $^ "$${file%.cpp}.o" $(LDFLAGS) -o ./out; 	\
		./out;																			\
		rm $${file%.cpp}.o;																\
	done
	@rm ./out 

$(OBJS): $(BUILD_PATH)/%.o : %.cpp 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE_SRC) $< -c -o $@


# delete prev build and build
remake: clean main

# delete previus build , build the new one and run it
rerun: clean run

# remove the last build
clean:
	rm $(OBJS) || true

# build and run the program
run: main
	ASAN_OPTIONS="log_path=asan.log" $(BUILD_PATH)/$< 2> error.log
