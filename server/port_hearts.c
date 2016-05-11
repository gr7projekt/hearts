//
//  port_hearts.c
//  
//
//  Created by Johan Lipecki on 2016-04-20.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <pwd.h>
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include "port_hearts.h"
#include "account.h"

long assign_guid(void);  //hur ska vi göra detta?
int start_game_server(char *port[], char *guid[]){
    char static hearts_start[200];
    sprintf(hearts_start, "%s %s %s %s %s %s", GAME_SERVER, port, guid[0],guid[1],guid[2],guid[3]);
    return system(hearts_start);
}
int get_random_port_number(void){
    srandom(time(NULL));
    return (random()%10000 + 40000);
}
int syn_ack(char* arguments, int *i,int sd, char *port, int connection_no){
    if(strcmp(arguments,"ENDOFTRANS")){
        syslog(LOG_INFO, "syn-ack argument %d: %s",*i, arguments);
        
        if (!strcmp(arguments, "hearts") && !(*i)) strcpy(arguments,"diamonds");
        
        else if(!(strcmp(arguments, "port")) && (*i)){
            
            sprintf(arguments, "%s %d", port, connection_no);
        }
        else strcpy(arguments, "This incident will be reported!");
        
        //skicka tillbaka strängen
        if (send(sd,arguments,100,0) < 0) {
            syslog(LOG_ERR, "%s", strerror(errno));
        }
    return 0;
    }
}
Account prompt_for_login(int *socketDescriptor){
    static Account account;
    if (send(*socketDescriptor,"account",sizeof("account"),0) < 0) {
        syslog(LOG_ERR,"%s",strerror(errno));
        return -1;
    }
    if (recv(*socketDescriptor, account,100, 0) < 0) {
        syslog(LOG_ERR,"%s",strerror(errno));
        return -2;
    }
    return account;
}

