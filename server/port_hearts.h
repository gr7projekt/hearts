//
//  port_hearts.h
//  
//
//  Created by Johan Lipecki on 2016-04-20.
//
//

#ifndef port_hearts_h
#define port_hearts_h

#define SYN0 "hearts"
#define ACK0 "diamonds"
#define SYN1 "port"

#define GAME_SERVER "./game_server"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#include <stdio.h>
int start_game_server(int); //
int syn_ack(char *,int,int); 

#endif /* port_hearts_h */
