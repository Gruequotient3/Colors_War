PROG = main

CC = g++
CXXFLAGS = -Wall -Wextra -O3
CXXFLAGS += -Ilib/glad/include
CXXFLAGS += -Ilib/glm/
CXXFLAGS += -Ilib/glfw/include
CXXFLAGS += -Ilib/stb
CXXFLAGS += -Ilib/freetype/include

LDFLAGS = -lm
LDFLAGS += -lGL -lX11 -lpthread -lXrandr -lXi -ldl 
LDFLAGS += -Llib/glad/
LDFLAGS += -Llib/stb/
LDFLAGS += -Llib/glfw/src/
LDFLAGS += -Llib/glm/glm/
LDFLAGS += -Llib/freetype/objs/.libs
LDFLAGS += -lglad -lstb_image -lglfw3 -lglm -lfreetype

DEBUG= -fsanitize=address

SOURCES = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)

OBJ = $(SOURCES:.cpp=.o)

RM = rm -rf

all: $(PROG)

debug: $(OBJ)
	$(CC) $(DEBUG) $(OBJ) $(LDFLAGS) -o $(PROG)

$(PROG): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROG)

libs:
	@cd lib/glm && cmake . -DCGLM_STATIC=ON && make
	@cd lib/glfw && cmake . && make
	@cd lib/freetype && make

%.o: %.cpp %.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(PROG)
