#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "encrypt.h"



Account getAccountByUsername(char *username)
{
	Account accs[100];
	int cnt = getAccounts(accs);
	int i;
	for (i = 0; i < cnt; i++)
		if (strcmp(accs[i].username, username) == 0) return accs[i];
	Account error_acc;
	error_acc.id = -1;	
	return error_acc;
}

Account getAccountById(int id)
{
	Account accs[100];
	int cnt = getAccounts(accs);
	int i;
	for (i = 0; i < cnt; i++) 
		if (accs[i].id == id) return accs[i];
	Account error_acc;
	error_acc.id = -1;
	return error_acc;
}

void display(char* ciphertext, int len){
  int v;
  for (v=0; v<len; v++){
    printf("%d ", ciphertext[v]);
  }
  printf("\n");
}

int addAccount(char *usr, char *pwd)
{

      MYSQL *conn;
      MYSQL_ROW row;
      char *server = "localhost";
      char *user = "root";
      char *password = "grupp7"; /* set me first */
      char *database = "hearts";
      conn = mysql_init(NULL);
      /* Connect to database */
      if (!mysql_real_connect(conn, server,
            user, password, database, 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return 0;
      }
      /* send SQL query */
      char *query;
      char buffer[200];
      int cx;
      MCRYPT td, td2;
      char * bfr;

      	int buffer_len = 16;
      	char * IV = "AAAAAAAAAAAAAAAA";
      	bfr = calloc(1, buffer_len);
      	strncpy(bfr, pwd, buffer_len);
      	encrypt(bfr, buffer_len, IV, "gr7hearts", 16);
	display(bfr, buffer_len);
      	char * newpass = (char *) malloc(200);
      	strcpy(newpass, bfr);
	printf("%c\n%c", bfr[0], newpass[0]);
      cx = sprintf(buffer, "insert into accounts (username, password) values ('%s', '%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d')", usr, bfr[0], bfr[1], bfr[2], bfr[3], bfr[3], bfr[4], bfr[5], bfr[6], bfr[7], bfr[8], bfr[9], bfr[10], bfr[11], bfr[12], bfr[13], bfr[14], bfr[15]);

      if (mysql_query(conn, buffer)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return 1;
      }
}


//Gets all accounts, and returns account count
int getAccounts(Account accs[]) {
      MYSQL *conn;
      MYSQL_RES *res;
      MYSQL_ROW row;
      char *server = "localhost";
      char *user = "root";
      char *password = "grupp7"; /* set me first */
      char *database = "hearts";
      conn = mysql_init(NULL);
      /* Connect to database */
      if (!mysql_real_connect(conn, server,
            user, password, database, 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
      }
      /* send SQL query */
      if (mysql_query(conn, "select * from accounts")) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
      }
      res = mysql_use_result(conn);
      /* output table name */
      int rowcount = -1;
      int count = 0;
      while ((row = mysql_fetch_row(res)) != NULL)
	{
		accs[count].username = (char *) malloc(20);
		accs[count].password = (char *) malloc(20);
		accs[count].id = atoi(row[0]);
		strcpy(accs[count].username, row[1]);
		strcpy(accs[count].password, row[2]);
		count++;
	}
      mysql_free_result(res);
      mysql_close(conn);
      return count;
}
