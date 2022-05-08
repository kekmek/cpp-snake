CC=g++
CFLAGS=-c -Wall -std=c++17 -IIncludes

all: snake

snake: clean main.o game.o gview.o human.o model.o tview.o view.o
	$(CC) main.o game.o gview.o human.o model.o tview.o view.o -o snake -lsfml-graphics -lsfml-window -lsfml-system

main.o:
	$(CC) $(CFLAGS) main.cpp

game.o:
	$(CC) $(CFLAGS) ./Source/game.cpp

gview.o:
	$(CC) $(CFLAGS) ./Source/gview.cpp

human.o:
	$(CC) $(CFLAGS) ./Source/human.cpp

model.o:
	$(CC) $(CFLAGS) ./Source/model.cpp

tview.o:
	$(CC) $(CFLAGS) ./Source/tview.cpp

view.o:
	$(CC) $(CFLAGS) ./Source/view.cpp

clean:
	rm *.o snake
