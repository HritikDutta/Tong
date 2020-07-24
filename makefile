CC = gcc
LIBS = -lncurses

TARGET = tong

default: main

main: main.c menu.o
	$(CC) main.c -o $(TARGET) menu.o $(LIBS)

menu.o: ./source/menu.c
	$(CC) -c ./source/menu.c $(LIBS)

clean:
	$(RM) tong *.o *~