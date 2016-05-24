all: serve_client.o game.o players.o serve_client

clean:
	rm -f *.o
	rm -f serve_client

CC= gcc -std=c99 -g -w
CFLAGS=-lpthread
DEPS = game.h players.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

serve_client: serve_client.o game.o players.o
	$(CC) -o serve_client serve_client.o game.o players.o -lpthread

players.o: players.c
	$(CC) -c players.c -lpthread

game.o: game.c
	$(CC) -c game.c

serve_client.o: serve_client.c
	$(CC) -c serve_client.c -lpthread

