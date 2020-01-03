INCLUDES = $(wildcard ./include/*.hpp)
SOURCES = $(wildcard ./src/*.cpp)
OBJECTS = $(subst ./src/, ./obj/, $(SOURCES:.cpp=.o))
CPPFLAGS = -Wall -std=c++2a -m64 
LINK = -I ./include/ -I C:/SFML-2.5.1-64/SFML-2.5.1/include

all : $(OBJECTS)

./obj/%.o : ./src/%.cpp ./include/%.hpp
	g++ -c $< -o $@ $(CPPFLAGS) $(LINK)

clean :
	@rm -f ./obj/*.o
	@clear

again : clean all
