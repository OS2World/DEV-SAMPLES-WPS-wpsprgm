include <wpfolder.sc>

#
#   Define the new class
#

class: aFolder,
       external stem   = afolder,
       local,
       external prefix = afolder_,
       classprefix     = afolderM_,
       major version   = 1,
       minor version   = 2;


#
#   Specify the parent class
#
parent: WPFolder;

passthru: C.ih;

#define INCL_WIN
#define INCL_DOS
#define INCL_GPIBITMAPS
#include <os2.h>

#define INCL_WPCLASS
#define INCL_WPFOLDER

#include <pmwp.h>

#define DebugBox(title, text) \
                                    \
                 WinMessageBox(     \
                    HWND_DESKTOP,   \
                    HWND_DESKTOP,   \
                    (PSZ) text,     \
                    (PSZ) title,    \
                    20,             \
                    MB_OK | MB_INFORMATION | MB_MOVEABLE)


endpassthru;   /* .ih */

#******************************************************************************
#   Define methods
#******************************************************************************

methods:

#******************************************************************************
#   Specify methods being overridden
#******************************************************************************

override wpOpen;

override wpMenuItemSelected;

override wpclsInitData, class;

