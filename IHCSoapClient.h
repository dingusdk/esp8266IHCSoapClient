/*
(C) 2016 dingus.dk J.Ø.N.

This file is part of the IHCSoapClient library

IHCSoapClient is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

IHCSoapClient is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with IHCSoapClient.If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _IHCSOAPCLIENT_h
#define _IHCSOAPCLIENT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "WiFiClient.h"

#include "HTTPClientEx.h"

/*!
 The main class for make soap request to the IHC controller.
 IHCSoapClientClass is a singleton (Only one instance should exist)
 You do not create you own instances, You access it using "IHCSoapClient"
*/
class IHCSoapClientClass {

public:

	typedef void (*fnOnChange)(int id, bool value);

protected:

	String m_HostName;
	String m_Cookie;
	String m_Username;
	String m_Password;

	fnOnChange OnChange;

	HTTPClientEx m_Http;
	bool m_LongPolling;

	void BeginRequest(const char* service,const char* soapaction);

public:

	void Initialize(const char* IhcHostName);
	bool HandleLoop();
	bool ConnectedToIHC();

	bool Authenticate(const char* username, const char* password);
	bool EnableRuntimeValueNotifications( int resourceid);
	bool WaitForResourceValueChanges(fnOnChange onchange);

	bool GetRuntimeValueBool(int resourceid);
	int GetRuntimeValueInt(int resourceid);
	float GetRuntimeValueFloat(int resourceid);

	bool SetRuntimeValueBool(int resourceid, bool value);
	bool SetRuntimeValueInt(int resourceid, int value);
	bool SetRuntimeValueFloat(int resourceid, float value);

	bool GetProject( WiFiClient output);

};

extern IHCSoapClientClass IHCSoapClient;

#endif

