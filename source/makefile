CC = gcc
LIBS = -lncurses -lm

main: main.o game.o pong.o misc.o menu.o
	$(CC) -o ../tong main.o game.o pong.o misc.o menu.o $(LIBS)

game: game.o pong.o misc.o
	$(CC) -c game.o pong.o misc.o $(LIBS)

pong: pong.o misc.o
	$(CC) -c pong.o misc.o $(LIBS)

misc: misc.o
	$(CC) -c misc.o $(LIBS)

menu: menu.o
	$(CC) -c menu.o $(LIBS)

clean:
	$(RM) *.o *~