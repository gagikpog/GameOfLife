cc=g++
FLAG= -lopengl32 -lglu32 -lglut32

all: main.o game.o
	$(cc) -o main.exe main.o game.o $(FLAG)

main.o: main.cpp
	$(cc) -c main.cpp

game.o: game.cpp
	$(cc) -c game.cpp
ifeq ($(OS),Windows_NT)
clear:
	del *.o
else 
clear:
	rm *.o
endif