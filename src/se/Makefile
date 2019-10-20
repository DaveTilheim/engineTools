CC = g++
LD = g++
CCVERSION = 2a
WARNINGS = -Wall
ARCHITECTURE = 64
MACROS = -D DEBUG
CFLAGS = -std=c++$(CCVERSION) $(WARNINGS) -m$(ARCHITECTURE) $(MACROS)
LIBHEAD = $(wildcard *.hpp) $(wildcard ./network/*.cpp)
LIBCODE = $(wildcard *.cpp) $(wildcard ./network/*.cpp)
LIBOBJ = $(LIBCODE:.cpp=.o) 

GITHUBLINK = "http://gitHub.com/DaveTilheim"

all : $(LIBOBJ)
	@echo "\033[95msoft engine source code compiled successfuly\033[0m"

%.o : %.cpp %.hpp
	$(CC) -c $< -o $@ $(CFLAGS)


clean :
	@rm -f *.o
	@rm -f ./network/*.o
	@clear
	@echo "\033[95mse *.o successfuly cleared\033[0m"

again : clean all

open :
	open *.cpp ./network/*.cpp
	open *.hpp ./network/*.hpp

which :
	@echo "\033[91msoft engine internal Makefile\033[0m"

git :
	@open $(GITHUBLINK)
