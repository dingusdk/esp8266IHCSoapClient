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
#include <string.h>
#include "SimpleXml.h"

#define MAXTAGSIZE 32

SimpleXml::SimpleXml(const char* xml) {

	Xml = xml;
}


const char* SkipNL(const char* s) {

	while (*s == '\r' || *s == '\n') s++;
	return s;
}

bool GetTag(const char* ntag, char* tag) {

	if (*ntag != '/') return false;
	const char* end = strchr(ntag + 1, '/');
	int l;
	if (end == NULL) {
		l = strlen(ntag);
	}
	else
		l = end - ntag;
	if (l > MAXTAGSIZE - 1) return false;
	memcpy(tag, ntag, l);
	tag[0] = '<';
	tag[l] = 0;
	return true;
}

void MakeEndTag(char* tag) {

	int l = strlen(tag);
	if ( l + 2 > MAXTAGSIZE) return;
	memmove(tag + 1, tag, l);
	tag[1] = '/';
	tag[l+1] = '>';
	tag[l+2] = 0;
}

String SimpleXml::Select(const char* xpath) {

	const char* start = Xml;
	// skip the xml header
	if (strncmp(Xml, "<?xml", 5) == 0) {
		start = strchr(Xml, '>');
		if (start == NULL) return "";
		start++;
		start = SkipNL(start);
	}
	char tag[MAXTAGSIZE];
	const char* ntag = xpath;
	const char* p = start;
	do {
		if (!GetTag(ntag, tag)) return "";
		p = strstr(Xml, tag);
		if (p == NULL) return "";
		p = const_cast<const char*>( strchr(p, '>'));
		if (p == NULL) return "";
		p++;
		ntag += strlen(tag);
	} while (*ntag != 0);
	start = p;
	MakeEndTag(tag);
	p = strstr(start, tag);
	if (p == NULL) return "";
	int l = p - start;
	String data;
	data.reserve(l + 1);
	while (start != p) data += *start++;
	return data;
}
