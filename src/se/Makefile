CC = g++
LD = g++
CCVERSION = 2a
WARNINGS = -Wall
ARCHITECTURE = 64
LIBDIR = ../src/
MACROS = -D DEBUG
LINK = -I $(LIBDIR)
CFLAGS = -std=c++$(CCVERSION) $(WARNINGS) -m$(ARCHITECTURE) $(MACROS)
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
LIBOBJ = EventHandler.o Utilities.o Application.o UpdaterApplication.o PhyObject.o Entity.o Timeline.o State.o RectEntity.o CircleEntity.o Widget.o ImageTransformation.o Line.o PhyConst.o debug.o Thread.o ThreadAble.o Label.o RenderLayout.o ProgressBar.o BGProgressBar.o LabeledProgressBar.o Entry.o Terminal.o
LIBHEAD = $(LIBDIR)Updater.hpp $(LIBDIR)Application.hpp $(LIBDIR)UpdaterApplication.hpp $(LIBDIR)EventHandler.hpp $(LIBDIR)Timeline.hpp $(LIBDIR)Entity.hpp $(LIBDIR)RectEntity.hpp $(LIBDIR)Widget.hpp $(LIBDIR)Utilities.hpp $(LIBDIR)ImageTransformation.hpp $(LIBDIR)Line.hpp $(LIBDIR)State.hpp $(LIBDIR)PhyObject.hpp $(LIBDIR)PhyConst.hpp $(LIBDIR)PolymorphEntity.hpp $(LIBDIR)CircleEntity.hpp $(LIBDIR)ThreadEntity.hpp $(LIBDIR)debug.hpp $(LIBDIR)Thread.hpp $(LIBDIR)ThreadAble.hpp $(LIBDIR)Label.hpp $(LIBDIR)RenderLayout.hpp $(LIBDIR)ProgressBar.hpp $(LIBDIR)BGProgressBar.hpp $(LIBDIR)LabeledProgressBar.hpp $(LIBDIR)Entry.hpp $(LIBDIR)Terminal.hpp
LIBCODE = $(LIBDIR)EventHandler.cpp $(LIBDIR)Utilities.cpp $(LIBDIR)Application.cpp $(LIBDIR)UpdaterApplication.cpp $(LIBDIR)PhyObject.cpp $(LIBDIR)Entity.cpp $(LIBDIR)Timeline.cpp $(LIBDIR)State.cpp $(LIBDIR)RectEntity.cpp $(LIBDIR)CircleEntity.cpp $(LIBDIR)Widget.cpp $(LIBDIR)ImageTransformation.cpp $(LIBDIR)Line.cpp $(LIBDIR)PhyConst.cpp $(LIBDIR)debug.cpp $(LIBDIR)Thread.cpp $(LIBDIR)ThreadAble.cpp $(LIBDIR)Label.cpp $(LIBDIR)RenderLayout.cpp $(LIBDIR)ProgressBar.cpp $(LIBDIR)BGProgressBar.cpp $(LIBDIR)LabeledProgressBar.cpp $(LIBDIR)Entry.cpp $(LIBDIR)Terminal.cpp
OBJ = appTest.o EntityTest.o
HEAD = appTest.hpp EntityTest.hpp
CODE = appTest.cpp EntityTest.cpp
EXE = app
GITHUBLINK = "http://gitHub.com/DaveTilheim"

all : $(EXE)

app : main.o $(LIBOBJ) $(OBJ)
	$(LD) -o $(EXE) main.o $(LIBOBJ) $(OBJ) $(SFMLFLAGS) $(CFLAGS)
	@echo "\033[95mcompilation success\033[0m"

main.o : main.cpp
	$(CC) -c main.cpp -o main.o $(CFLAGS) $(LINK)

#lib
EventHandler.o : $(LIBDIR)EventHandler.hpp $(LIBDIR)EventHandler.cpp
	$(CC) -c $(LIBDIR)EventHandler.cpp -o EventHandler.o  $(CFLAGS)

Utilities.o : $(LIBDIR)Utilities.hpp $(LIBDIR)Utilities.cpp
	$(CC) -c $(LIBDIR)Utilities.cpp -o Utilities.o  $(CFLAGS)

Application.o : $(LIBDIR)Application.hpp $(LIBDIR)Application.cpp
	$(CC) -c $(LIBDIR)Application.cpp -o Application.o  $(CFLAGS)

UpdaterApplication.o : $(LIBDIR)UpdaterApplication.hpp $(LIBDIR)UpdaterApplication.cpp
	$(CC) -c $(LIBDIR)UpdaterApplication.cpp -o UpdaterApplication.o  $(CFLAGS)

PhyObject.o : $(LIBDIR)PhyObject.hpp $(LIBDIR)PhyObject.cpp
	$(CC) -c $(LIBDIR)PhyObject.cpp -o PhyObject.o  $(CFLAGS)

Entity.o : $(LIBDIR)Entity.hpp $(LIBDIR)Entity.cpp
	$(CC) -c $(LIBDIR)Entity.cpp -o Entity.o  $(CFLAGS)

Timeline.o : $(LIBDIR)Timeline.hpp $(LIBDIR)Timeline.cpp
	$(CC) -c $(LIBDIR)Timeline.cpp -o Timeline.o  $(CFLAGS)

State.o : $(LIBDIR)State.hpp $(LIBDIR)State.cpp
	$(CC) -c $(LIBDIR)State.cpp -o State.o  $(CFLAGS)

RectEntity.o : $(LIBDIR)RectEntity.hpp $(LIBDIR)RectEntity.cpp
	$(CC) -c $(LIBDIR)RectEntity.cpp -o RectEntity.o  $(CFLAGS)

CircleEntity.o : $(LIBDIR)CircleEntity.hpp $(LIBDIR)CircleEntity.cpp
	$(CC) -c $(LIBDIR)CircleEntity.cpp -o CircleEntity.o  $(CFLAGS)

Widget.o : $(LIBDIR)Widget.hpp $(LIBDIR)Widget.cpp
	$(CC) -c $(LIBDIR)Widget.cpp -o Widget.o  $(CFLAGS)

Line.o : $(LIBDIR)Line.hpp $(LIBDIR)Line.cpp
	$(CC) -c $(LIBDIR)Line.cpp -o Line.o  $(CFLAGS)

ImageTransformation.o : $(LIBDIR)ImageTransformation.hpp $(LIBDIR)ImageTransformation.cpp
	$(CC) -c $(LIBDIR)ImageTransformation.cpp -o ImageTransformation.o  $(CFLAGS)

PhyConst.o : $(LIBDIR)PhyConst.hpp $(LIBDIR)PhyConst.cpp
	$(CC) -c $(LIBDIR)PhyConst.cpp -o PhyConst.o  $(CFLAGS)

debug.o : $(LIBDIR)debug.hpp $(LIBDIR)debug.cpp
	$(CC) -c $(LIBDIR)debug.cpp -o debug.o $(CFLAGS)

Thread.o : $(LIBDIR)Thread.hpp $(LIBDIR)Thread.cpp
	$(CC) -c $(LIBDIR)Thread.cpp -o Thread.o $(CFLAGS)

ThreadAble.o : $(LIBDIR)ThreadAble.hpp $(LIBDIR)ThreadAble.cpp
	$(CC) -c $(LIBDIR)ThreadAble.cpp -o ThreadAble.o $(CFLAGS)

Label.o : $(LIBDIR)Label.hpp $(LIBDIR)Label.cpp
	$(CC) -c $(LIBDIR)Label.cpp -o Label.o $(CFLAGS)

RenderLayout.o : $(LIBDIR)RenderLayout.hpp $(LIBDIR)RenderLayout.cpp
	$(CC) -c $(LIBDIR)RenderLayout.cpp -o RenderLayout.o $(CFLAGS)

ProgressBar.o : $(LIBDIR)ProgressBar.hpp $(LIBDIR)ProgressBar.cpp
	$(CC) -c $(LIBDIR)ProgressBar.cpp -o ProgressBar.o $(CFLAGS)

BGProgressBar.o : $(LIBDIR)BGProgressBar.hpp $(LIBDIR)BGProgressBar.cpp
	$(CC) -c $(LIBDIR)BGProgressBar.cpp -o BGProgressBar.o $(CFLAGS)

LabeledProgressBar.o : $(LIBDIR)LabeledProgressBar.hpp $(LIBDIR)LabeledProgressBar.cpp
	$(CC) -c $(LIBDIR)LabeledProgressBar.cpp -o LabeledProgressBar.o $(CFLAGS)

Entry.o : $(LIBDIR)Entry.hpp $(LIBDIR)Entry.cpp
	$(CC) -c $(LIBDIR)Entry.cpp -o Entry.o $(CFLAGS)

Terminal.o : $(LIBDIR)Terminal.hpp $(LIBDIR)Terminal.cpp
	$(CC) -c $(LIBDIR)Terminal.cpp -o Terminal.o $(CFLAGS)

#app
appTest.o : appTest.hpp appTest.cpp
	$(CC) -c appTest.cpp -o appTest.o  $(CFLAGS) $(LINK)

EntityTest.o : EntityTest.hpp EntityTest.cpp
	$(CC) -c EntityTest.cpp -o EntityTest.o  $(CFLAGS) $(LINK)

clean :
	@rm -f *.o
	@rm -f $(EXE)
	@clear
	@echo "\033[95msuccessfuly cleared\033[0m"

again : clean all

open :
	open *.cpp *.hpp
	open $(LIBDIR)*.cpp
	open $(LIBDIR)*.hpp

git :
	@open $(GITHUBLINK)
