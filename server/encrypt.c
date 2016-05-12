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
#include "encrypt.h"

void encrypt_str(char *plaintext, char *encrypted)
{
	char * bfr;
        int buffer_len = 16;
        char * IV = "AAAAAAAAAAAAAAAA";
	bfr = calloc(1, buffer_len);
        strncpy(bfr, plaintext, buffer_len);
        encrypt(bfr, buffer_len, IV, "gr7hearts", 16);
	sprintf(encrypted, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", bfr[0], bfr[1], bfr[2], bfr[3], bfr[4], bfr[5], bfr[6], bfr[7], bfr[8], bfr[9], bfr[10], bfr[11], bfr[12], bfr[13], bfr[14], bfr[15], bfr[16]);
}

int encrypt(
    void* buffer,
    int buffer_len, /* Because the plaintext could include null bytes*/
    char* IV, 
    char* key,
    int key_len 
)
{
  MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
  int blocksize = mcrypt_enc_get_block_size(td);
  if( buffer_len % blocksize != 0 ){return 1;}

  mcrypt_generic_init(td, key, key_len, IV);
  mcrypt_generic(td, buffer, buffer_len);
  mcrypt_generic_deinit (td);
  mcrypt_module_close(td);

  return 0;
}
