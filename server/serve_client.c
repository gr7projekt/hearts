#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include "game.h"
#include "players.h"

#define BUFLEN 512
#define NPACK 4
#define GAMEPORT 41337

void diep(char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}
// from UDP made simple at https://www.abc.se/~m6695/udp.html
int main(int argc, char *argv[]) {
	

	struct sockaddr_in si_me, si_oth,si_other[4];
	int s, i;
	socklen_t slen=sizeof(si_other);
	ssize_t len;
	FILE *fd;

	fd = fopen("/var/tmp/serve_client","w");
	char buf[BUFLEN]={"start"};
	char *trick[4];
	FF_trick(trick);

	//Game initiation, shuffling and dealing.
	Card sorted_deck[52];
	Card shuffled_deck[52];
	char *deck[52];
	new_deck(sorted_deck);
	shuffle_deck(sorted_deck,shuffled_deck);
	convert_card_struct(shuffled_deck,deck,buf);
	Game *game = malloc(sizeof(Game));
	memcpy(game->deck,deck,sizeof(deck));
	memcpy(game->buffer,buf, sizeof(buf));
	printf("Shuffled deck: \n%s\n\n",game->buffer);

	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		diep("socket");
	printf("socket open\n");
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(GAMEPORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, &si_me, sizeof(si_me))==-1)
		diep("bind");
	printf("bound\n");

	//Player initiation
	int counter[4];
	for(int i=0;i<4;i++){
		counter[i] = i;
	}

	pthread_t players[4];
	for(int i=0;i<4;i++){
		pthread_t tmp=0;
		players[i] = tmp;
	}
	//Player thread arguments are initiated
	Player player[4];
	for(int i=0;i<4;i++){
		memset((char *) &si_other[i], 0, sizeof(si_other[i]));
		Player tmp={i,&s,game,&si_me,&si_other[i]};
		memcpy(&player[i], (void *) &tmp, sizeof(tmp));
	}
	//deal cards
	for (int k = 0; k < 4; k++) {
		sprintf(player[k].game->buffer,"%s;",game->deck[k]);
		for(int j=4;j<52;j+=4) {
			strcat(player[k].game->buffer, game->deck[j+k]);
			strcat(player[k].game->buffer,";");
		}
		printf("Player %d game buffer: %s\n",k,player[k].game->buffer);
	}


	int j=0,connected=0;
	void *buffer = (void *) strdup(buf);
	bool connections[]={false,false,false,false};
	char *this_is_my_pos[4];

	do{
		printf("inet: %s\tsocket descriptor: %d\n\n",
		       inet_ntoa(player[j].si_other->sin_addr),
				 player[j].sockfd);
		if((len = recvfrom(s, buffer, BUFLEN, 0, &si_oth, &slen)) == -1) diep("recvfrom()");
		printf("addr: %d\n",si_oth.sin_addr.s_addr);

		//check given position
		separate_strings(buffer,";",this_is_my_pos,4);
		if((j=find_DD(this_is_my_pos,4))== -1) perror("not a new connection");
		if(j < 4 && j >= 0 && !connections[j]){
			connections[j]=true;
			connected += 1;
		} else perror("not a new connection");
		player[j].sockfd = s;
		player[j].si_other->sin_addr=si_oth.sin_addr;
		player[j].si_other->sin_port=si_oth.sin_port;

		printf("Received packet from IP-address: %s: Port: %d\nPosition: %d\nData: %s\nLength: %d\n",
		       inet_ntoa(si_oth.sin_addr), ntohs(si_oth.sin_port),
		       j,
		       (char *) buffer,len);
		separate_strings(buffer,";",trick,4);
		printf("received split into: %s ",trick[0]);
		for(int i=1;i<4;i++) printf(" %s",trick[i]);
		printf("\nSending packet: \n%s\nto player %d\n", player[j].game->buffer,j);
		if (sendto(s, player[j].game->buffer, 200, 0, (struct sockaddr *) &si_oth,  slen)==-1)
			diep("sendto()");

	} while (connected<4);



	/*while(strcmp(buffer,"quit")){
		printf("buffer: %s \n",player[j].game->buffer);
		if ((len = recvfrom(s, buffer, BUFLEN, 0, &si_oth, &slen)) == -1) diep("recvfrom()");
		printf("Received packet from %s:%d\nData: %s\nLength: %d\n",
		       inet_ntoa(si_oth.sin_addr), ntohs(si_oth.sin_port), (char *) buffer,len);
	*/	//counter[j] = pthread_create(&players[j], NULL, &player_waits_or_plays, (void *) &player[j]);
		//pthread_join((players[j]),NULL);

	printf("client data: %s \n",buffer);
	separate_strings(buffer,";",trick,4);
	printf("received split into: %s\n",trick[0]);
	for(int i=1;i<4;i++) printf(" %s",trick[i]);
	/*	//Receive data and start game threads for each client
		for(int j=0;j<4;j++) {
			if ((len = recvfrom(player[j].sockfd, player[j].game->buffer, BUFLEN, 0, &si_other[i], &slen)) == -1) diep("recvfrom()");
			counter[j++] = pthread_create(&players[j], NULL, &player_waits_or_plays, (void *) &player[j]);
			printf("Received packet from %s:%d\nData: %s\nLength: %d\n",
			       inet_ntoa(si_other[i].sin_addr), ntohs(si_other[i].sin_port), (char *) buffer,len);
		}

 // Jag försöker föra över detta till trådarna--------------------//
		char cards_to_send[40];
		i=0;
		sprintf(cards_to_send,"%s;",player[i].game->deck[player[i].pos]);
		for(int j=4;j<52;j+=4) {
			strcat(cards_to_send, player[i].game->deck[player[i].pos+j]);
			strcat(cards_to_send,";");
		}
		printf("Sending packet2: \n%s\n", cards_to_send);
		if (sendto(s, cards_to_send, 40, 0, (struct sockaddr *) &si_other[i],  slen)==-1)
			diep("sendto()");
	int k=0;
*/
    	close(s);
    	return 0;
}
