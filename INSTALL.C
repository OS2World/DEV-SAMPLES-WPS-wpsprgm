#define INCL_PM

#include <os2.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	HAB	hab;
	HMQ hmq;
	
	hab = WinInitialize(0);
	hmq = WinCreateMsgQueue(hab, 0);
	
	if(WinRegisterObjectClass("aFolder", "afolder") )
		WinReplaceObjectClass("WPFolder", "aFolder", TRUE);
		
    WinDestroyMsgQueue(hmq);
    WinTerminate(hab);
    
    return(0);
}


