#define INCL_PM

#include <os2.h>

int main(int argc, char **argv)
{
	HAB		hab;
	HMQ		hmq;
	HOBJECT	hObj;
	
	if(!argv[1])
		return -1;
		
	hab = WinInitialize(0);
	hmq = WinCreateMsgQueue(hab, 0);
	
	hObj = WinQueryObject(argv[1]);
	if(hObj)
		WinSetObjectData(hObj, "OPEN=DEFAULT");
	
	WinDestroyMsgQueue(hmq);
	WinTerminate(hab);
	
	return 0;
}
