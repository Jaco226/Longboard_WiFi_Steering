

#include <Arduino.h.>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);

//constantants


//functions
bool  recieveUdpPacket(int * parsed_int);
