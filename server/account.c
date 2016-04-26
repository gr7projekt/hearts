#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"


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