all: clean account.o gameserver.o encrypt.o gameserver

clean:
	rm -f *.o
	rm -f gameserver

account.o: 
	gcc -c `mysql_config --cflags --libs` -lmysql account.c

encrypt.o:
	gcc -c -lmcrypt encrypt.c

gameserver.o:
	gcc -c `sdl2-config --cflags` `mysql_config --cflags --libs` gameserver.c

gameserver:
	gcc -o gameserver gameserver.o encrypt.o account.o `sdl2-config --libs` `mysql_config --libs` -lSDL2_net -lmysqlclient -lmcrypt -lpthread
