#ifndef __mydefs_h__
#define __mydefs_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef WIN32	//This whole file is windows specific right now
#include <windows.h>
static HWND g_hWnd = NULL;
#endif

#endif
