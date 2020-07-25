CC = gcc
LIBS = -lncurses

main: main.o game.o pong.o
	$(CC) -o ../tong main.o game.o pong.o $(LIBS)

game: game.o pong.o
	$(CC) -c game.o pong.o $(LIBS)

pong: pong.o
	$(CC) -c pong.o $(LIBS)

clean:
	$(RM) *.o *~