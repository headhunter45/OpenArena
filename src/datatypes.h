/***************************************************************************
 *   Copyright (C) 2006 by Tom Hicks   *
 *   tomhicks@cse.buffalo.edu   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef __datatypes_h__
#define __datatypes_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef WIN32 //Make this MSVC something
typedef unsigned __int8		uint8;
typedef unsigned __int16	uint16;
typedef unsigned __int32	uint32;
typedef unsigned __int64	uint64;
typedef			 __int8		int8;
typedef			 __int16	int16;
typedef			 __int32	int32;
typedef			 __int64	int64;
typedef signed	 __int8		sint8;
typedef signed	 __int16	sint16;
typedef signed	 __int32	sint32;
typedef signed	 __int64	sint64;

/*
typedef unsigned __int8		byte;
typedef unsigned __int16	word;
typedef unsigned __int32	dword;
typedef unsigned __int64	qword;

typedef byte	db;
typedef word	dw;
typedef dword	dd;
typedef qword	dq;
*/
#endif

#ifdef __GNUC__ //ie if we are using GCC //used to be __linux
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned long		uint32;
typedef unsigned long long	uint64;
typedef			 char		int8;
typedef			 short		int16;
typedef			 long		int32;
typedef			 long long	int64;
typedef signed	 char		sint8;
typedef signed	 short		sint16;
typedef signed	 long		sint32;
typedef signed	 long long	sint64;

/*
typedef unsigned char		byte;
typedef unsigned short		word;
typedef unsigned long		dword;
typedef unsigned long long	qword;

typedef byte	db;
typedef word	dw;
typedef dword	dd;
typedef qword	dq;
*/
#endif

#endif
