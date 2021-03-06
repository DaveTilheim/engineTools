CC = g++
LD = g++
CCVERSION = 2a
WARNINGS = -Wall
ARCHITECTURE = 64
MACROS =
CFLAGS = -std=c++$(CCVERSION) $(WARNINGS) -m$(ARCHITECTURE) $(MACROS)
LINK = -I ./includes/system/ -I ./includes/graphics/

GRAPHICS_INCLUDES = $(wildcard includes/graphics/*.hpp)
GRAPHICS_SRC = $(wildcard src/graphics/*.cpp)
GRAPHICS_OBJ = $(subst src/, obj/, $(GRAPHICS_SRC:.cpp=.o))

SYSTEM_INCLUDES = $(wildcard includes/system/*.hpp)
SYSTEM_SRC = $(wildcard src/system/*.cpp)
SYSTEM_OBJ = $(subst src/, obj/, $(SYSTEM_SRC:.cpp=.o))

INCLUDES = $(SYSTEM_INCLUDES) $(GRAPHICS_INCLUDES)
SRC = $(SYSTEM_SRC) $(GRAPHICS_SRC)
OBJ = $(SYSTEM_OBJ) $(GRAPHICS_OBJ)

GITHUBLINK = "http://gitHub.com/DaveTilheim"

all : $(OBJ)
	@echo "\033[95msoft engine source code compiled successfuly\033[0m"

obj/system/%.o : src/system/%.cpp includes/system/%.hpp
	$(CC) -c $< -o $@ $(CFLAGS) $(LINK)

obj/graphics/%.o : src/graphics/%.cpp includes/graphics/%.hpp
	$(CC) -c $< -o $@ $(CFLAGS) $(LINK)

clean :
	@rm -f ./obj/system/*.o
	@rm -f ./obj/graphics/*.o
	@clear
	@echo "\033[95mse obj successfuly cleared\033[0m"

again : clean all

open :
	open $(SYSTEM_SRC)
	open $(GRAPHICS_SRC)
	open $(SYSTEM_INCLUDES)
	open $(GRAPHICS_INCLUDES)
	
which :
	@echo "\033[91msoft engine internal Makefile\033[0m"

git :
	@open $(GITHUBLINK)
