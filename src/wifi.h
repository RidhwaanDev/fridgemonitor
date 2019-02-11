#pragma once 

#include <stdint.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>

namespace fridge {
const int http_request= 0x1;
const int http_response= 0x2;

struct NetworkManager { 
	void init();
	void sleep();
}

}
