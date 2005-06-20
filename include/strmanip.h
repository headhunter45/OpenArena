#ifndef __strmanip_h__
#define __strmanip_h__

#include <string>
#include <cmath>
#ifdef WIN32
#include <windows.h>//WTF why did I need all of these
#endif
#include "keys.h"
#include "datatypes.h"

using namespace std;

bool Truth(string str);
int Integer(string str);
float Floating(string str);
uint8 KeyName(string str);
string KeyString(uint8);
string Right(string, uint32);
string Left(string, uint32);
string tolower(string);
string toupper(string);
string word(string, uint32);

#endif
