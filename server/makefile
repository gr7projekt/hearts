all: clean account.o gameserver.o encrypt.o InetS3.o port_hearts.o players.o game.o gameserver InetS3 

clean:
	rm -f *.o
	rm -f gameserver
	rm -f inets3

account.o: 
	gcc -c `mysql_config --cflags --libs` -lmysql account.c

encrypt.o:
	gcc -c -lmcrypt encrypt.c

gameserver.o:
	gcc -c `sdl2-config --cflags` `mysql_config --cflags --libs` gameserver.c

players.o:
	gcc -c `sdl2-config --cflags` players.c

game.o:
	gcc -c game.c

gameserver:
	gcc -o gameserver gameserver.o encrypt.o account.o players.o game.o `sdl2-config --libs` `mysql_config --libs` -lSDL2_net -lmysqlclient -lmcrypt -lpthread

port_hearts.o:
	gcc -c `mysql_config --cflags --libs` port_hearts.c

InetS3.o:
	gcc -c InetS3.c `mysql_config --cflags --libs` -lmysqlclient

InetS3:
	gcc -o InetS3 InetS3.o account.o encrypt.o -lmysqlclient

