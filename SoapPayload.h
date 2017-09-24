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

/*
 This file contains the soap data to be send for each soap request
*/

const PROGMEM char ihc_auth_payload[] = {
"<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">"
"<s:Body>"
"<authenticate1 xmlns=\"utcs\" xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\">"
"<password>%s</password>"
"<username>%s</username>"
"<application>treeview</application>"
"</authenticate1>"
"</s:Body>"
"</s:Envelope>" };

const PROGMEM char ihc_enablenotifycation_payload[] = {
"<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">"
"<s:Body>"
"<enableRuntimeValueNotifications1 xmlns=\"utcs\" xmlns:a=\"http://www.w3.org/2001/XMLSchema\" xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\">"
"<a:arrayItem>%u</a:arrayItem>"
"</enableRuntimeValueNotifications1></s:Body></s:Envelope>" };

const char* ihc_waitfornotify_paypload =
"<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">"
"<s:Body><waitForResourceValueChanges1 xmlns=\"utcs\">10</waitForResourceValueChanges1>"
"</s:Body></s:Envelope>";

const PROGMEM char ihc_getruntimevalue_payload[] = {
	"<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">"
	"<s:Body>"
	"<getRuntimeValue1 xmlns=\"utcs\">%u</getRuntimeValue1>"
	"</s:Body></s:Envelope>" };


const PROGMEM char ihc_setruntimevalue_payload[] = {
	"<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">"
	"<s:Body>"
	"<setResourceValue1 xmlns=\"utcs\" xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\">"
	"<value i:type=\"a:WSBooleanValue\" xmlns:a=\"utcs.values\">"
	"<a:value>%s</a:value></value>"
	"<typeString/>"
	"<resourceID>%u</resourceID>"
	"<isValueRuntime>true</isValueRuntime>"
	"</setResourceValue1>"
	"</s:Body>"
	"</s:Envelope>" };

const PROGMEM char ihc_setruntimevalue_int_payload[] = {
	"<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">"
	"<s:Body>"
	"<setResourceValue1 xmlns=\"utcs\" xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\">"
	"<value i:type=\"a:WSIntegerValue\" xmlns:a=\"utcs.values\">"
	"<a:integer>%i</a:integer></value>"
	"<typeString/>"
	"<resourceID>%u</resourceID>"
	"<isValueRuntime>true</isValueRuntime>"
	"</setResourceValue1>"
	"</s:Body>"
	"</s:Envelope>" };

const PROGMEM char ihc_setruntimevalue_float_payload[] = {
	"<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\">"
	"<s:Body>"
	"<setResourceValue1 xmlns=\"utcs\" xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\">"
	"<value i:type=\"a:WSFloatingPointValue\" xmlns:a=\"utcs.values\">"
	"<a:floatingPointValue>%s</a:floatingPointValue></value>"
	"<typeString/>"
	"<resourceID>%u</resourceID>"
	"<isValueRuntime>true</isValueRuntime>"
	"</setResourceValue1>"
	"</s:Body>"
	"</s:Envelope>" };

const PROGMEM char ihc_getproject_payload[] = {
	"<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"><s:Body/></s:Envelope>"
};

