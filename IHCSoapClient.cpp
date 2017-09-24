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
#include "IHCSoapClient.h"
#include "SimpleXml.h"

#include "SoapPayload.h"
const char * ihc_headerkeys[] = { "set-cookie" };
const char* idpattern = "<ns1:resourceID xsi:type=\"xsd:int\">";
const char* valuepattern = "<ns2:value xsi:type=\"xsd:boolean\">";

IHCSoapClientClass IHCSoapClient;

/*!
Initialize the soap client with a host name of the IHC controller. 
Typically used in your setup function
\param ihchostname The hostname or IP of the IHC controller
*/
void IHCSoapClientClass::Initialize(const char* ihchostname) {

	m_HostName = ihchostname;
	m_Http.end();
	m_LongPolling = false;
}

/*!
Send a authentication request to the IHC controller.
\param username The login user for the IHC controller
\param password The password for the user
*/

bool IHCSoapClientClass::Authenticate(const char* username, const char* password) {

	int size = strlen(ihc_auth_payload) + strlen(username) + strlen(password) + 1;
	if (size < 2500) size = 2500;
	char* buffer = (char*)malloc( size);
	snprintf_P(buffer, size, ihc_auth_payload, password, username);

	m_Cookie = "";
	BeginRequest("/ws/AuthenticationService", "\"authenticate\"");
	int code = m_Http.POST(buffer);
	int i = m_Http.writeToBuffer(buffer, size);
	m_Cookie = m_Http.header("set-cookie");
	m_Http.end();

	SimpleXml xml(buffer);
	String r = xml.Select("/SOAP-ENV:Envelope/SOAP-ENV:Body/ns1:authenticate2/ns1:loginWasSuccessful");

	free(buffer);
	if (code != 200 || r != "true") return false;
	m_Password = password;
	m_Username = username;
	return true;
}

/*!
\return Returns true it we have a connection to the IHC controller
*/
bool IHCSoapClientClass::ConnectedToIHC() {
	if (m_HostName.length() == 0 || m_Password.length() == 0 || m_Username.length() == 0) return false;
	if (m_Cookie.length() == 0) return false;
	return true;
}


bool IHCSoapClientClass::GetRuntimeValueBool(int resourceid) {

	int size = 1024;
	char* buffer = (char*)malloc(size);
	snprintf_P(buffer, size, ihc_getruntimevalue_payload, resourceid);

	m_Http.end();
	BeginRequest("/ws/ResourceInteractionService", "\"getResourceValue\"");
	int code = m_Http.POST(buffer);
	// We have an error
	if (code != 200) return false;
	m_Cookie = m_Http.header("set-cookie");
	m_Http.writeToBuffer(buffer, size);
	m_Http.end();
	SimpleXml xml(buffer);
	String r = xml.Select("/SOAP-ENV:Body/ns1:getRuntimeValue2/ns1:value/ns2:value");
	free(buffer);
	return r == "true";
}

int IHCSoapClientClass::GetRuntimeValueInt(int resourceid) {

	int size = 1024;
	char* buffer = (char*)malloc(size);
	snprintf_P(buffer, size, ihc_getruntimevalue_payload, resourceid);

	m_Http.end();
	BeginRequest("/ws/ResourceInteractionService", "\"getResourceValue\"");
	int code = m_Http.POST(buffer);
	// We have an error
	if (code != 200) return false;
	m_Cookie = m_Http.header("set-cookie");
	m_Http.writeToBuffer(buffer, size);
	m_Http.end();
	SimpleXml xml(buffer);
	String r = xml.Select("/SOAP-ENV:Body/ns1:getRuntimeValue2/ns1:value/ns2:integer");
	free(buffer);
	return atoi( r.c_str());
}

float IHCSoapClientClass::GetRuntimeValueFloat(int resourceid) {

	int size = 1024;
	char* buffer = (char*)malloc(size);
	snprintf_P(buffer, size, ihc_getruntimevalue_payload, resourceid);

	m_Http.end();
	BeginRequest("/ws/ResourceInteractionService", "\"getResourceValue\"");
	int code = m_Http.POST(buffer);
	// We have an error
	if (code != 200) return false;
	m_Cookie = m_Http.header("set-cookie");
	m_Http.writeToBuffer(buffer, size);
	m_Http.end();
	SimpleXml xml(buffer);
	String r = xml.Select("/SOAP-ENV:Body/ns1:getRuntimeValue2/ns1:value/ns2:floatingPointValue");
	free(buffer);
	return atof(r.c_str());
}

/*!
Set a bool runtime value of a IHC resource.
\param resourceid The IHC resource id
\param value The bool value to set
\return True if the value was set succesfully
*/
bool IHCSoapClientClass::SetRuntimeValueBool(int resourceid,bool value) {

	if (!ConnectedToIHC()) return false;
	int size = strlen(ihc_setruntimevalue_payload) + 12;
	if (size < 512) size = 512;
	char* buffer = (char*)malloc(size);
	snprintf_P(buffer, size, ihc_setruntimevalue_payload, value ? "true" : "false",resourceid);

	m_Http.end();
	BeginRequest("/ws/ResourceInteractionService", "\"setResourceValue\"");
	int code = m_Http.POST(buffer);
	m_Cookie = m_Http.header("set-cookie");
	m_Http.writeToBuffer(buffer, size);
	m_Http.end();
	SimpleXml xml(buffer);
	String r = xml.Select("/SOAP-ENV:Envelope/SOAP-ENV:Body/ns1:setResourceValue2");
	free(buffer);
	return code == 200 && r == "true";
}

/*!
Set a integer runtime value of a IHC resource.
\param resourceid The IHC resource id
\param value The integer value to set
\return True if the value was set succesfully
*/
bool IHCSoapClientClass::SetRuntimeValueInt(int resourceid, int value) {

	if (!ConnectedToIHC()) return false;
	int size = strlen(ihc_setruntimevalue_int_payload) + 12;
	if (size < 512) size = 512;
	char* buffer = (char*)malloc(size);
	snprintf_P(buffer, size, ihc_setruntimevalue_int_payload, value, resourceid);

	m_Http.end();
	BeginRequest("/ws/ResourceInteractionService", "\"setResourceValue\"");
	int code = m_Http.POST(buffer);
	m_Cookie = m_Http.header("set-cookie");
	m_Http.writeToBuffer(buffer, size);
	m_Http.end();
	SimpleXml xml(buffer);
	String r = xml.Select("/SOAP-ENV:Envelope/SOAP-ENV:Body/ns1:setResourceValue2");
	free(buffer);
	return code == 200 && r == "true";
}

/*!
Set a float runtime value of a IHC resource.
\param resourceid The IHC resource id
\param value The float value to set
\return True if the value was set succesfully
*/
bool IHCSoapClientClass::SetRuntimeValueFloat(int resourceid, float value) {

	if (!ConnectedToIHC()) return false;
	int size = strlen(ihc_setruntimevalue_float_payload) + 12;
	if (size < 512) size = 512;
	char* buffer = (char*)malloc(size);
	String f(value, 1);
	snprintf_P(buffer, size, ihc_setruntimevalue_float_payload, f.c_str(), resourceid);

	m_Http.end();
	BeginRequest("/ws/ResourceInteractionService", "\"setResourceValue\"");
	int code = m_Http.POST(buffer);
	m_Cookie = m_Http.header("set-cookie");
	m_Http.writeToBuffer(buffer, size);
	m_Http.end();
	SimpleXml xml(buffer);
	String r = xml.Select("/SOAP-ENV:Envelope/SOAP-ENV:Body/ns1:setResourceValue2");
	free(buffer);
	return code == 200 && r == "true";
}

/*!
Enable notification of a specified IHC resource id
\param resourceid The IHC resource id
\return True if the notification was enabled succesfully
*/

bool IHCSoapClientClass::EnableRuntimeValueNotifications(int resourceid) {

	if (!ConnectedToIHC()) return false;
	int size = strlen(ihc_enablenotifycation_payload) + 12;
	char* buffer = (char*)malloc(size);
	snprintf_P(buffer, size, ihc_enablenotifycation_payload, resourceid);

	BeginRequest("/ws/ResourceInteractionService", "\"enableRuntimeValueNotifications\"");
	int code = m_Http.POST(buffer);
	m_Cookie = m_Http.header("set-cookie");
//	m_Http.writeToStream(&Serial);
	m_Http.end();
	free(buffer);
	return code == 200;
}

bool IHCSoapClientClass::WaitForResourceValueChanges(fnOnChange onchange) {

	if (!ConnectedToIHC()) return false;
	OnChange = onchange;
	BeginRequest("/ws/ResourceInteractionService", "\"waitForResourceValueChanges\"");
	m_Http.setTimeout(15000);
	int code = m_Http.sendRequestEx("POST", (uint8_t*)ihc_waitfornotify_paypload, strlen(ihc_waitfornotify_paypload));
	if (code != 200) return false;
	String cookie = m_Http.header("set-cookie");
	if (cookie.length() > 0) m_Cookie = cookie;
	m_LongPolling = true;
	return true;
}

/*!
Call this in your loop function to allow IHCSoapClient to do the long polling
and callback of runtime changes
*/
bool IHCSoapClientClass::HandleLoop() {

	if (!ConnectedToIHC()) return false;
	if (!m_LongPolling) return true;
	int code = m_Http.handleHeaderResponseEx();
	if (code == 0) return true;
	m_LongPolling = false;
	if (code < 0) {
		return false;
	}
	else if (code == 200) {
		String data = m_Http.getString();
		int pos = data.indexOf(idpattern);
		if (pos > 0) {
			pos += strlen(idpattern);
			int end = data.indexOf( '<',pos);
			if (end > pos) {
				String sid = data.substring(pos, end);
				int id = atoi( sid.c_str());
				pos = data.indexOf(valuepattern);
				if (pos > 0) {
					pos += strlen(valuepattern);
					if (data.charAt(pos) == 't') {
						OnChange(id, true);
					}
					else if (data.charAt(pos) == 'f') {
						OnChange(id, false);
					}
				}
			}
		}
	}
	m_Http.end();
	return WaitForResourceValueChanges(OnChange);
}


void IHCSoapClientClass::BeginRequest(const char* service,const char* soapaction) {

	m_Http.begin(m_HostName, 80, service);
	m_Http.addHeader("Content-Type", "text/xml; charset=utf-8");
	m_Http.addHeader("SOAPAction", soapaction);
	m_Http.addHeader("Cookie", m_Cookie);
	m_Http.collectHeaders(ihc_headerkeys, 1);
}


inline unsigned char b64_lookup(char c) {
	if (c >= 'A' && c <= 'Z') return c - 'A';
	if (c >= 'a' && c <= 'z') return c - 71;
	if (c >= '0' && c <= '9') return c + 4;
	if (c == '+') return 62;
	if (c == '/') return 63;
	return -1;
}

bool IHCSoapClientClass::GetProject(WiFiClient output) {

	m_Http.end();
	BeginRequest("/ws/ControllerService", "\"getIHCProject\"");
	int code = m_Http.sendRequestEx("POST", (uint8_t*)ihc_getproject_payload, strlen(ihc_getproject_payload));
	if (code != 200) return false;
	Stream& base64(m_Http.getStream());
	if (m_Http.connected()) {
		for (int i = 0; i < 5; i++) {
			char c;
			do {
				if (!m_Http.connected() ) {
					m_Http.end();
					return false;
				}
				if (base64.available() > 0) {
					c = base64.read();
				}
				else {
					delay(1);
					c = 0;
				}
			} while (c != '>');
		}
		word base64buffer = 0;
		int readsize = 1024;
		int writesize = 1024;
		char* readbuffer = (char*)malloc(readsize);
		char* writebuffer = (char*)malloc(writesize);
		int writepos = 0;
		int bits = 0;
		bool done = false;
		while ( m_Http.connected() && ! done) {
			if (base64.available() > 0) {
				int size = base64.readBytes(readbuffer, readsize);
				for (int r = 0; r < size; r++) {
					byte ch = readbuffer[r];
					if (ch == '=' || ch == '<') {
						done = true;
						break;
					}
					byte data = b64_lookup(ch);
					base64buffer <<= 6;
					base64buffer |= data;
					bits += 6;
					if (bits >= 8) {
						ch = base64buffer >> (bits - 8);
						bits -= 8;
						writebuffer[writepos++] = ch;
						if (writepos == writesize) {
							output.write( (const uint8_t *)writebuffer, writepos);
							writepos = 0;
						}
					}
				}
			}
		}
		if (writepos > 0) output.write((const uint8_t *)writebuffer, writepos);
		free(readbuffer);
		free(writebuffer);
	}
	m_Http.end();
	return true;
}



