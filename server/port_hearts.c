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


#define PARENT 1

int start_game_server(int players, int port){
     /* forka processen när spelare 0 ansluter*/
    if(!players){
        if(!(fork())){
            //Executing as child process
            execlp("bin/sh","sh","-c",GAME_SERVER,port,NULL);
            syslog(LOG_ERR,"%s",strerror(errno));
        }
        else {
            wait(0);
            return 0;
            //no waiting around for child? zombie creator?
        }
    }
    else return port;
}
int get_random_port_number(void){
    srandom(time(NULL));
    return (random()%10000 + 40000);
}
int syn_ack(char* arguments,int syn,int fd){
    pid_t child_pid;
    int static port;
    /* Duplicate this process. */
    child_pid = fork ();
    if(child_pid != 0){
        /* This is the parent process. */
        close(1);
        wait(0);
        return 1;
    }
    else {
        //child
        //Redirect stdout to socket
        close(1);
        dup(fd);
        //SYN-ACK switch
        if(!strcmp(arguments,SYN0)){
            syslog(LOG_INFO,"argument: %s, SYN0: %s", arguments, SYN0);
            if(!syn) strcpy(arguments,ACK0);
            syslog(LOG_INFO,"argument: %s, ACK0: %s", arguments, ACK0);
            return 0;
        }
        else if(strcmp(arguments,SYN1)){
            if(syn) return 0;
            syslog(LOG_INFO,"argument: %s, SYN1: %s", arguments, SYN1)
        }
        else strcpy(arguments,"it's the ping of death for you my friend!");
        /* Now execute the commands in a new session*/
        execlp("/bin/sh","bash","-c", "echo" ,arguments, NULL);
        /* The execlp function returns only if an error occurs. */
        syslog(LOG_ERR,"%s",strerror(errno));
        abort();
    }
    wait(0);
    return PARENT;
}

