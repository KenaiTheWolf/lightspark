/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2011-2013  Alessandro Pignotti (a.pignotti@sssup.it)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef SCRIPTING_AVM1_AVM1NET_H
#define SCRIPTING_AVM1_AVM1NET_H

#include "asobject.h"
#include "scripting/flash/net/flashnet.h"

namespace lightspark
{

class AVM1SharedObject: public SharedObject
{
public:
	AVM1SharedObject(Class_base* c):SharedObject(c){}
	static void sinit(Class_base* c);
};

class AVM1LocalConnection: public LocalConnection
{
public:
	AVM1LocalConnection(Class_base* c):LocalConnection(c){}
	static void sinit(Class_base* c);
};

}
#endif // SCRIPTING_AVM1_AVM1NET_H
