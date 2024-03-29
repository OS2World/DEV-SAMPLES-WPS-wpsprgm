
/*
 * This file was generated by the SOM Compiler.
 * FileName: afolder.c.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emitc: 1.24
 */

#define aFolder_Class_Source
#include "afolder.ih"
#include "afolder.rh"


PFNWP		pfnOldProc		= NULL;
HMODULE		hmod			= NULLHANDLE;

HMODULE   SOMLINK QueryModuleHandle(aFolder *somSelf)
{
	APIRET rc;

	if(!somSelf)
		return NULLHANDLE;

    if (hmod == NULLHANDLE)
    {
     zString zsPathName;
       /*
        *   Retrieve registered pathname of our module (DLL) and query the
        *   module handle.
        */
       zsPathName =
       _somLocateClassFile( SOMClassMgrObject, SOM_IdFromString("aFolder"),
                                              aFolder_MajorVersion, aFolder_MinorVersion);

	   if(!zsPathName)
			return NULLHANDLE;
       rc = DosQueryModuleHandle( zsPathName, &hmod);
       if (rc)
			return NULLHANDLE;

    }   /* end if (hmod == NULLHANDLE) */

    return (hmod);
}



MRESULT EXPENTRY aFolderSubProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
	HACCEL		hAccel;

	switch(msg)
	{
		case WM_DESTROY:
			hAccel = WinQueryAccelTable(WinQueryAnchorBlock(hwnd), hwnd);
			if(hAccel)
				WinDestroyAccelTable(hAccel);
			break;
		case WM_COMMAND:
			switch(SHORT1FROMMP(mp1))
			{
				case IDM_EXIT:
					WinPostMsg(hwnd, WM_CLOSE, MPVOID, MPVOID);
					return (MRESULT) TRUE;
				case IDM_ARRANGE:
					if( SHORT1FROMMP(mp2) == CMDSRC_MENU)
						break;
					WinPostMsg(hwnd, WM_COMMAND, MPFROM2SHORT(IDM_ARRANGE, 0), MPFROM2SHORT(CMDSRC_MENU, TRUE) );
					return (MRESULT) TRUE;
				case IDM_SETTINGS:
					WinPostMsg(hwnd, WM_COMMAND, MPFROM2SHORT(IDM_WPSSETTINGS, 0), MPFROM2SHORT(CMDSRC_MENU, TRUE) );
					return (MRESULT) TRUE;
			}
			break;
	}
	if(pfnOldProc)
		return pfnOldProc(hwnd, msg, mp1, mp2);
	else
		return WinDefWindowProc(hwnd, msg, mp1, mp2);
}


SOM_Scope HWND   SOMLINK afolder_wpOpen(aFolder *somSelf, HWND hwndCnr, ULONG ulView, ULONG param)
{
	HWND	hwnd;
	HACCEL	hAccel;
	int		idAccel;

    aFolderMethodDebug("aFolder","afolder_wpOpen");
    
	if(!somSelf)
		return NULLHANDLE;

	hwnd = parent_wpOpen(somSelf,hwndCnr,ulView,param);
	if(!hwnd)
		return NULLHANDLE;
		
	switch(ulView)
	{
		case OPEN_CONTENTS:
		case OPEN_TREE:
		case OPEN_DETAILS:
			/*
			** Load and associate an Accelerator table.
			*/
			pfnOldProc = WinSubclassWindow(hwnd, (PFNWP) aFolderSubProc);
			if( _somRespondsTo(somSelf, SOM_IdFromString("wpIsCurrentDesktop") ) )
				idAccel = IDM_DESKFOLDER;
			else
				idAccel = IDM_AFOLDER;
				
			hAccel = WinLoadAccelTable(WinQueryAnchorBlock(hwnd), hmod, idAccel);
			if(hAccel)
				WinSendMsg(hwnd, WM_SETACCELTABLE, (MPARAM) hAccel, MPVOID);
			break;
	}
	return hwnd;
}

SOM_Scope BOOL   SOMLINK afolder_wpMenuItemSelected(aFolder *somSelf, HWND hwndFrame, ULONG ulMenuId)
{
    aFolderMethodDebug("aFolder","afolder_wpMenuItemSelected");
    
    if(ulMenuId == IDM_WPSARRANGE)
    {
    	char szBuf[256];
    	
    	strcpy(szBuf, "Arrange '");
    	strcat(szBuf, _wpQueryTitle(somSelf) );
    	strcat(szBuf, "'" );
    	if( WinMessageBox(HWND_DESKTOP, hwndFrame, "Are you sure?", szBuf, 20, MB_YESNO | MB_ICONQUESTION | MB_APPLMODAL | MB_MOVEABLE) != MBID_YES)
    		return FALSE;
    }
    
    if( ulMenuId == IDM_ARRANGE )
    	ulMenuId = IDM_WPSARRANGE;
    
    return (parent_wpMenuItemSelected(somSelf,hwndFrame,ulMenuId));
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta


#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta
SOM_Scope void   SOMLINK afolderM_wpclsInitData(M_aFolder *somSelf)
{
    M_aFolderMethodDebug("M_aFolder","afolderM_wpclsInitData");

    hmod = QueryModuleHandle(somSelf);
    
    parent_wpclsInitData(somSelf);
}
