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
#ifndef _httpclientex_h
#define _httpclientex_h

#include "ESP8266HTTPClient.h"

/*!
Add the functionallity to do long polling requests with HTTPClient
This is a helper class for IHCSoapClient
*/
class HTTPClientEx : public HTTPClient {

public:
	HTTPClientEx();
	~HTTPClientEx();

	int sendRequestEx(const char * type, uint8_t * payload, size_t size);
	int handleHeaderResponseEx();

	int writeToBuffer(char* buffer, int size);
};

#endif
