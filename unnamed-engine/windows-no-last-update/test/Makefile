CC = g++
LD = g++
CCVERSION = 2a
WARNINGS = -Wall 
ARCHITECTURE = 64
ENGINE_PATH = ../engine/

MACROS =
LINK = -I $(ENGINE_PATH)include/ -I C:\SFML-2.5.1-64\SFML-2.5.1\include

CFLAGS = -std=c++$(CCVERSION) $(WARNINGS) -m$(ARCHITECTURE) $(MACROS)

SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -LC:\SFML-2.5.1-64\SFML-2.5.1\lib

HEAD = $(wildcard *.hpp)
CODE = $(wildcard *.cpp)
OBJ = $(CODE:.cpp=.o)
EXE = app

all : eng $(EXE)

eng :
	@(cd $(ENGINE_PATH) && $(MAKE))

.PHONY : $(EXE) main.o

$(EXE) : $(OBJ)
	$(LD) -o $(EXE) $(wildcard $(ENGINE_PATH)obj/*.o) $(OBJ) $(SFMLFLAGS) $(CFLAGS)

%.o : %.cpp %.hpp
	$(CC) -c $< -o $@ $(CFLAGS) $(LINK)

main.o : main.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(LINK)

clean :
	@rm -f *.o
	@rm -f $(EXE)
	@clear
	@(cd $(ENGINE_PATH) && $(MAKE) $@)
	@echo "\033[95msuccessfuly cleared\033[0m"

again : clean all

run: all
	@./$(EXE)

