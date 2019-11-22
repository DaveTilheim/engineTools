CC = g++
LD = g++
CCVERSION = 2a
WARNINGS = -Wall
ARCHITECTURE = 64
MACROS = -D DEBUG
CFLAGS = -std=c++$(CCVERSION) $(WARNINGS) -m$(ARCHITECTURE) $(MACROS)
LINK = -I ./includes/system/ -I ./includes/graphics/ -I ./includes/network/ -I C:/SFML-2.5.1-64/SFML-2.5.1/include -I ./includes/

NETWORK_INCLUDES = $(wildcard ./includes/network/*.hpp)
NETWORK_SRC = $(wildcard ./src/network/*.cpp)
NETWORK_OBJ = $(subst ./src/, ./obj/, $(NETWORK_SRC:.cpp=.o))

GRAPHICS_INCLUDES = $(wildcard ./includes/graphics/*.hpp)
GRAPHICS_SRC = $(wildcard ./src/graphics/*.cpp)
GRAPHICS_OBJ = $(subst ./src/, ./obj/, $(GRAPHICS_SRC:.cpp=.o))

SYSTEM_INCLUDES = $(wildcard ./includes/system/*.hpp)
SYSTEM_SRC = $(wildcard ./src/system/*.cpp)
SYSTEM_OBJ = $(subst ./src/, ./obj/, $(SYSTEM_SRC:.cpp=.o))

INCLUDES = $(SYSTEM_INCLUDES) $(GRAPHICS_INCLUDES) $(NETWORK_INCLUDES)
SRC = $(SYSTEM_SRC) $(GRAPHICS_SRC) $(NETWORK_SRC)
OBJ = $(SYSTEM_OBJ) $(GRAPHICS_OBJ) #$(NETWORK_OBJ)

GITHUBLINK = "http://gitHub.com/DaveTilheim"

all : $(OBJ)
	@echo "\033[95msoft engine source code compiled successfuly\033[0m"


./obj/system/%.o : ./src/system/%.cpp ./includes/system/%.hpp
	$(CC) -c $< -o $@ $(CFLAGS) $(LINK)

./obj/graphics/%.o : ./src/graphics/%.cpp ./includes/graphics/%.hpp
	$(CC) -c $< -o $@ $(CFLAGS) $(LINK)

#./obj/network/%.o : ./src/network/%.cpp ./includes/network/%.hpp
#	$(CC) -c $< -o $@ $(CFLAGS) $(LINK)

app:
	g++ -o app main.cpp $(SYSTEM_OBJ) $(GRAPHICS_OBJ) $(LINK) -LC:\SFML-2.5.1-64\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

clean :
	@del .\obj\system\*.o
	@del .\obj\graphics\*.o
	@del .\obj\network\*.o
	@cls

again : clean all

which :
	@echo "\033[91msoft engine internal Makefile\033[0m"
