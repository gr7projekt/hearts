#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account
{
	int id;
	char *username;
	char *password;
};
typedef struct account Account;

int getAccounts(Account accs[]);
int addAccount(char *usr, char *pwd);
#endif 
