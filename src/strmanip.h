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
#ifndef __strmanip_h__
#define __strmanip_h__

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>
#include <cmath>
#include "keys.h"
#include "datatypes.h"

using namespace std;

/*!
 * \brief
 * Write brief comment for Truth here.
 * 
 * \param str
 * Description of parameter str.
 * 
 * \returns
 * Write description of return value here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for Truth here.
 * 
 * \remarks
 * Write remarks for Truth here.
 * 
 * \see
 * Separate items with the '|' character.
 */
bool Truth(string str);
/*!
 * \brief
 * Write brief comment for Integer here.
 * 
 * \param str
 * Description of parameter str.
 * 
 * \returns
 * Write description of return value here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for Integer here.
 * 
 * \remarks
 * Write remarks for Integer here.
 * 
 * \see
 * Separate items with the '|' character.
 */
int Integer(string str);
/*!
 * \brief
 * Write brief comment for Floating here.
 * 
 * \param str
 * Description of parameter str.
 * 
 * \returns
 * Write description of return value here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for Floating here.
 * 
 * \remarks
 * Write remarks for Floating here.
 * 
 * \see
 * Separate items with the '|' character.
 */
float Floating(string str);

/**
 * @brief
 * Write brief comment for KeyString here.
 * 
 * @param keyCode - Description of parameter .
 * 
 * @returns
 * Write description of return value here.
 * 
 * Write detailed description for KeyString here.
 * 
 * @remarks
 * Write remarks for KeyString here.
 * 
 * @see
 * Separate items with the '|' character.
 */
string KeyString(uint8 keyCode);
/*!
 * @brief
 * Write brief comment for Right here.
 * 
 * @param 
 * Description of parameter .
 * 
 * @param 
 * Description of parameter .
 * 
 * @returns
 * Write description of return value here.
 * 
 * @throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for Right here.
 * 
 * @remarks
 * Write remarks for Right here.
 * 
 * @see
 * Separate items with the '|' character.
 */
string Right(string, uint32);
/*!
 * @brief
 * Write brief comment for Left here.
 * 
 * @param 
 * Description of parameter .
 * 
 * @param 
 * Description of parameter .
 * 
 * @returns
 * Write description of return value here.
 * 
 * @throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for Left here.
 * 
 * @remarks
 * Write remarks for Left here.
 * 
 * @see
 * Separate items with the '|' character.
 */
string Left(string, uint32);
/*!
 * \brief
 * Write brief comment for tolower here.
 * 
 * \param 
 * Description of parameter .
 * 
 * \returns
 * Write description of return value here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for tolower here.
 * 
 * \remarks
 * Write remarks for tolower here.
 * 
 * \see
 * Separate items with the '|' character.
 */
string tolower(string);
/*!
 * \brief
 * Write brief comment for toupper here.
 * 
 * \param 
 * Description of parameter .
 * 
 * \returns
 * Write description of return value here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for toupper here.
 * 
 * \remarks
 * Write remarks for toupper here.
 * 
 * \see
 * Separate items with the '|' character.
 */
string toupper(string);
/*!
 * \brief
 * Write brief comment for word here.
 * 
 * \param 
 * Description of parameter .
 * 
 * \param 
 * Description of parameter .
 * 
 * \returns
 * Write description of return value here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Write detailed description for word here.
 * 
 * \remarks
 * Write remarks for word here.
 * 
 * \see
 * Separate items with the '|' character.
 */
string word(string, uint32);

#endif
