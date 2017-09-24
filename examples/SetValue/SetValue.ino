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
-------------------------------------------------------------------------------

This example will initializse the IHCSoapClient, authenticate using a IHC
username and password, then toogle a boolean resource on and off with a 5 sec
interval.
To get the IHC resource value you can either find it manually in the IHC project
file or use the IHC Alternative Service view application You can find it on 
http://www.dingus.dk 
When you select a resource you can see the id in the lower right section
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IHCSoapClient.h>

// The define below if just to make it easier for me to have a "private" settings file
// You should open the settings.h file and change your wifi/ihc settings
#ifdef MYSETTINGSFILE
#include "examples\mysettings.h"
#else
#include "settings.h"
#endif

#define resourceid 2112786

void setup() {
	Serial.begin(115200);
	Serial.print("Start");

	WiFi.begin(ssid, wifipassword);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	IHCSoapClient.Initialize(ihchostname);
	IHCSoapClient.Authenticate( username, password);
}

void loop() {

	Serial.println("On");
	IHCSoapClient.SetRuntimeValueBool(resourceid, true);
	delay(5000);
	Serial.println("Off");
	IHCSoapClient.SetRuntimeValueBool(resourceid, false);
	delay(5000);
}