//
//  main.c
//  Test
//
//  Created by Johan Lipecki on 2016-04-01.
//  Copyright © 2016 Johan Lipecki. All rights reserved.
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

/* Change this to whatever your daemon is called */
#define DAEMON_NAME "HEARTS_SERVER"

/* Change this to the user under which to run */
#define RUN_AS_USER "Grupp_7"

#define IP_ADDRESS "130.237.84.89"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void sigchld_handlr(int);
void sigchld_handler(int);
void daemonize(const char *);
int hearts (char *,int);

int main(int argc,char const *argv[])
{
    int done, pid, s2, inet_fd;
    ssize_t r;
    socklen_t t;
    struct sockaddr_in inet, inet2;
    char arguments[100],str[10000];
    memset(arguments,'\0',sizeof(arguments));
    memset(str,'\0',sizeof(str));
    
    /* Initialize the logging interface */
    openlog(DAEMON_NAME, LOG_PID, LOG_LOCAL5 );
    syslog(LOG_INFO, "Starting_daemon" );
    
    /* Daemonize */
    daemonize( "/var/lock/" DAEMON_NAME);
    syslog(LOG_INFO, "Daemonized!\n");
    
    /* Now we are a daemon -- do the work for which we were paid */
    // Example from Beej's Guide to Network Programming:
    ////https://beej.us/guide/bgnet/output/html/multipage/sockaddr_inman.html
    
    if ((inet_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        syslog(LOG_ERR, "%s",strerror(errno));
        exit(1);
    }
    
    inet.sin_family = AF_INET;
    inet.sin_port = htons(atoi(argv[1]));
    inet_pton(AF_INET,IP_ADDRESS,&inet.sin_addr);
    
    if (bind(inet_fd, (struct sockaddr *)&inet, sizeof inet) == -1) {
        syslog(LOG_ERR,  "%s",strerror(errno));
        exit(1);
    } else syslog(LOG_INFO, "Socket bound!\n");
    
    if (listen(inet_fd, 4) == -1) {
        syslog(LOG_ERR,  "%s",strerror(errno));
        exit(1);
    }
    syslog(LOG_INFO, "listening for up to 4 connections!\n");
    
    for(;;) {
        struct sigaction sa;
        sa.sa_handler = sigchld_handlr; // reap all dead processes
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        if (sigaction(SIGCHLD, &sa, NULL) == -1) {      //WNOHANG!
            syslog(LOG_ERR,  "%s",strerror(errno));
            exit(EXIT_FAILURE);
        }
        syslog(LOG_INFO, "Waiting for a connection...\n");
        t = sizeof(inet2);
        if ((s2 = accept(inet_fd, (struct sockaddr *)&inet2, &t)) == -1) {
            syslog(LOG_ERR,  "%s",strerror(errno));
            exit(1);
        }
        /* fork efter acceptet! */
        if((pid=fork())==-1){               // fork och felhantering
            syslog(LOG_ERR,  "%s",strerror(errno));
            exit(1);
        }
        else if(!pid){                              //serverbarnet ärver accepten, socketen och fildeskriptorn.
            syslog(LOG_INFO,"Connected.\n");
            
            done = 0;
            do {
                r = recv(s2, arguments,100, 0);
                if (r <= 0) {
                    if (r < 0) perror("recv");
                    done = 1;                                   //försäkrar oss om att accept-loopen avslutas nedan ...
                }                                               //om recv returnerar 0 eller -1.
                if (!done){                                     //Inget fel eller avslut, enligt tilldelning
                    if(!(hearts(arguments,s2))){
                        strcpy(arguments,"ENDOFTRANS");
                        if (send(s2,arguments,strlen(arguments),0) < 0) {  //skicka tillbaka strängen
                            perror("send");
                            done = 1;                   //försäkrar oss om att accept-loopen avslutas
                        }
                        else done = 0;
                    }
                    //memset(arguments,'\0',sizeof(arguments));
                }
            } while (!done);                        //så länge klienten skickar data håller vi öppet 24/7
            printf("I'm server %d and my client just signed off!\n",getpid());
            syslog(LOG_NOTICE, "terminated" );
            closelog();
            exit(0);
        }
        else close(s2);
    }
    /* Finish up */
    return 0;
}

void sigchld_handlr(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

void sigchld_handler(int s)
{
    switch(s) {
        case(SIGTSTP):  exit((int)SIG_IGN);  break;/* Various TTY signals */
        case(SIGTTOU):  exit((int)SIG_IGN); break;
        case(SIGTTIN):  exit((int)SIG_IGN); break;
        case(SIGHUP):   exit((int)SIG_IGN); break;/* Ignore hangup signal */
        case SIGALRM:   exit(EXIT_FAILURE); break;
        case SIGUSR1:   exit(EXIT_SUCCESS); break;
        case SIGCHLD:   exit(EXIT_FAILURE); break;
        default:        exit((int)SIG_DFL); break;
    }
}

void daemonize(const char *lockfile)
{
    pid_t pid, sid, parent,child;
    int lfp = -1;
    struct sigaction act,old_act,act2;
    
    act.sa_handler=sigchld_handler;
    sigemptyset (&act.sa_mask);
    act.sa_flags = 0;
    
    /* already a daemon */
    if (getppid() == 1 ) {
        syslog(LOG_ERR, "already a daemon! Code = %d (%s)\n",
               errno, strerror(errno));
        return;
    }
    //printf("Ready for the lockfile!\n");
    /* Create the lock file as the current user */
    if ( lockfile && lockfile[0] ) {
        lfp = open(lockfile,O_RDWR|O_CREAT,0640);   //|O_EXCL taken care of in the start-file
        if ( lfp < 0 ) {
            syslog( LOG_ERR, "unable to create lock file %s, code=%d (%s)\n",
                   lockfile, errno, strerror(errno) );
            exit(EXIT_FAILURE);
        }
    }
    //printf("lockfile done\n");
    
    /* Drop user if there is one, and we were run as root */
    if ( getuid() == 0 || geteuid() == 0 ) {
        struct passwd *pw = getpwnam(RUN_AS_USER);
        if ( pw ) {
            syslog( LOG_NOTICE, "setting user to " RUN_AS_USER );
            setuid( pw->pw_uid );
        }
    }
    
    /*
     Trap signals that we expect to recieve,  sighandler_t signal(int signum, sighandler_t handler)
     http://www.gnu.org/software/libc/manual/html_node/Sigaction-Function-Example.html
     */
    sigaction(SIGCHLD,&act,&old_act);
    sigaction(SIGUSR1,&act,&old_act);
    sigaction(SIGALRM,&act,&old_act);
    
    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        syslog( LOG_ERR, "unable to fork daemon, code=%d (%s)",
               errno, strerror(errno) );
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then we can exit the parent process. */
    if (pid > 0) {
        
        /* Wait for confirmation from the child via SIGTERM or SIGCHLD, or
         for two seconds to elapse (SIGALRM).  pause() should not return. */
        alarm(2);
        pause();
        
        exit(EXIT_FAILURE);
    }
    
    /* At this point we are executing as the child process */
    printf("%d\n",child = getpid());        //this writes the pid to revd.pid and ensures all other data is wiped
    freopen("dev/null", "w", stdout);
    
    /* Cancel certain signals */
    sigaction(SIGCHLD,NULL,&old_act); /* A child process dies */
    sigaction(SIGTSTP,&act2,NULL); /* Various TTY signals */
    sigaction(SIGTTOU,&act2,NULL);
    sigaction(SIGTTIN,&act2,NULL);
    sigaction(SIGHUP,&act2,NULL);
    sigaction(SIGTERM,&act2,NULL);
    
    /* Change the file mode mask */
    //printf("umask!\n");
    umask(0);
    
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        syslog( LOG_ERR, "unable to create a new session, code %d (%s)",
               errno, strerror(errno) );
        exit(EXIT_FAILURE);
    }
    
    /* Change the current working directory.  This prevents the current
     directory from being locked; hence not being able to remove it. */
    if ((chdir("/")) < 0) {
        syslog( LOG_ERR, "unable to change directory to %s, code %d (%s)",
               "/", errno, strerror(errno) );
        exit(EXIT_FAILURE);
    }
    //printf("directory changed\n");
    
    /* Redirect standard files to /dev/null */
    freopen("dev/null", "r", stdin);
    freopen("dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
    
    /* Tell the parent process that we are A-okay */
    kill(parent, SIGUSR1 );
}

int hearts (char* arguments,int fd){
    pid_t child_pid;
    if(strcmp("quit",arguments)){             //Avsluta
        close(1);
        dup(fd);
        return SIGTERM;
    }
    else {
        /* Duplicate this process. */
        child_pid = fork ();
        if (child_pid != 0){
            /* This is the parent process. */
            close(1);
            wait(0);
            return 0;
        }
        
        else {
            //Redirect stdout to socket
            close(1);
            dup(fd);
            /* Now execute the commands in a new session*/
            execlp("/bin/sh","bash","-c", "echo Hello World!", NULL);
            /* The execlp function returns only if an error occurs. */
            perror("Exec\n");
            abort ();
        }
    }
    return 0;
}



