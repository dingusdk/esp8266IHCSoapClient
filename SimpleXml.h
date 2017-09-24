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
#ifndef _simplexml_h
#define _simplexml_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <string>
#define String std::string
#endif


/*!
A class to do a simple search for specific a XML element in a XML document
This is a helper class for IHCSoapClient to parse the reponse from from the soap requests.
*/
class SimpleXml {

protected:

	const char* Xml; 
	
public:
	SimpleXml(const char* xml);

	String Select(const char* xpath);
};


#endif



