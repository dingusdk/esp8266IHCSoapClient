# Introduction

This is an Arduino library for making a soap connection to an IHC controller
(IHC controller is a home automation controller made by LK)
The library has been made for ESP8266

The library implements:

* Authentication
* Get runtime values
* Set runtime values
* Notification when a resource changes. (Currently the library only support notification of boolean resources)

## Examples

See the examples folder.

For more infomation about this library and my other IHC projects look at

https://www.dingus.dk

Here you can also find my dingswicth project that was made with the IHCSoapClient library. 

The IHCAlternative service view application - is an easy way to find resource ids:

http://www.dingus.dk/updated-ihc-alternative-service-view/


# License

IHCSoapClient is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

IHCSoapClient is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ArduinoIHC.  If not, see <http://www.gnu.org/licenses/>.

