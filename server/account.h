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
	int credit;
};
typedef struct account Account;

// Gets all accounts, returns count
int getAccounts(Account accs[]);
// Inserts new account, returns 0 on failure
int addAccount(char *usr, char *pwd);
// Gets account by ID, returns account with ID = -1 on failure
Account getAccountById(int id);
// Gets account by Username, returns account with ID = -1 on failure
Account getAccountByUsername(char *username);

#endif 

