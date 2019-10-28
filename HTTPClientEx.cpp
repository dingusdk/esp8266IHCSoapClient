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
#include "HTTPClientEx.h"


HTTPClientEx::HTTPClientEx() {
}


HTTPClientEx::~HTTPClientEx() {
}

int HTTPClientEx::sendRequestEx(const char * type, uint8_t * payload, size_t size) {

	// connect to server
	if (!connect()) {
		return returnError(HTTPC_ERROR_CONNECTION_REFUSED);
	}

	if (payload && size > 0) {
		addHeader(F("Content-Length"), String(size));
	}

	// send Header
	if (!sendHeader(type)) {
		return returnError(HTTPC_ERROR_SEND_HEADER_FAILED);
	}

	// send Payload if needed
	if (payload && size > 0) {
		if ( _client->write(&payload[0], size) != size) {
			return returnError(HTTPC_ERROR_SEND_PAYLOAD_FAILED);
		}
	}
	return 200;
}

int HTTPClientEx::handleHeaderResponseEx() {

	if (!connected()) {
		return HTTPC_ERROR_NOT_CONNECTED;
	}
	if (_client->available() <= 0) return 0;
	return handleHeaderResponse();
}


int HTTPClientEx::writeToBuffer(char* buffer, int size) {

	int pos = 0;
	while (connected() && pos < size - 1) {
		size_t sizeAvailable = _client->available();
		if (sizeAvailable == 0) {
			delay(10);
			sizeAvailable = _client->available();
			if (sizeAvailable == 0)
				break;
		}
		if (sizeAvailable >= size - pos) return -1;
		int bytesRead = _client->readBytes(buffer + pos, sizeAvailable);
		pos += bytesRead;
	}
	buffer[pos] = 0;
	return pos;
}
