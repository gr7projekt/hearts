#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * MCrypt API available online:
 * http://linux.die.net/man/3/mcrypt
 */
#include <mcrypt.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

// Encrypts plaintext and stores it in encrypted
void encrypt_str(char * paintext, char * encrypted);
int encrypt(void *buffer, int buffer_len, char *IV, char *key, int key_len);

#endif
