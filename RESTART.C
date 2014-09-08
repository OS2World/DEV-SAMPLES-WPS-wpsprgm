#define INCL_PM

#include <os2.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

static char szSys[] = "c:\\os2\\os2sys.ini";
static char szUser[] = "c:\\os2\\os2.ini";

int main(int argc, char **argv)
{
	HAB			hab;
	HMQ			hmq;
	PRFPROFILE	prf;
	
	hab = WinInitialize(0);
	hmq = WinCreateMsgQueue(hab, 0);
	
	memset(&prf, '\0', sizeof(prf));
	
	prf.cchUserName = strlen(szUser);
	prf.pszUserName = szUser;
	prf.cchSysName = strlen(szSys);
	prf.pszSysName = szSys;
	
	PrfReset(hab, &prf);
	
	WinDestroyMsgQueue(hmq);
	WinTerminate(hab);
	
	return 0;
}
