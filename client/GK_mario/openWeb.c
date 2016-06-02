#include "openWeb.h"

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

void openWeb()
{


//koden togs från:
//http://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1044654269&id=1043284392
//2016-04-27 (15:30)

    #ifdef _WIN32
        char szPath[] = "www.kth.se";
        HINSTANCE hRet = ShellExecute(HWND_DESKTOP,"open",szPath,NULL,NULL,SW_SHOW);

  //(1)Parent window //(2)Operation to perform //(3)Path to program //(4)Parameters //(5)Default directory //(6)How to open
  /*
  The function returns a HINSTANCE (not really useful in this case)
  So therefore, to test its result, we cast it to a LONG.
  Any value over 32 represents success!
  */

        if((LONG)hRet <= 32)
            {
                MessageBox(HWND_DESKTOP,"Unable to start program","",MB_OK);
            }
    #elif _APPLE_
        printf("i openweb(), _APPLE_\n");
    #elif _linux_
        printf("i openweb(), _linux_\n");
    #elif _unix_
        printf("i openweb(), _unix_\n");
    #else
        system("open http://www.kth.se");
    #endif //
}
