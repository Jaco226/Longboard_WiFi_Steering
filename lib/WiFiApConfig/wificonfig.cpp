
#include "wificonfig.hpp"
#include <ESP8266WiFi.h>

bool wifiSoftApSetup(char  local_IPadress, char gatewayAddress, char subnetAddress, const char * softApGivenName = "DefaultSoftAp", char * softapPassword = NULL, int channel = 0, bool isHidden = 0, int maxClients = 0)
{

        bool isReady = 0;
        if((local_IPadress) && (gatewayAddress) && (subnetAddress) && (softApGivenName) && (softapPassword) && (channel) && (isHidden) && (maxClients)) {


                Serial.print("Setting soft-AP configuration ... ");
                Serial.println(WiFi.softAPConfig(local_IPadress, gatewayAddress, subnetAddress) ? "Ready" : "Failed!");

                Serial.print("Setting soft-AP ... ");
                Serial.println(WiFi.softAP(softApGivenName, softapPassword, channel, isHidden, maxClients) ? "Ready" : "Failed!");

                Serial.print("Soft-AP IP address = ");
                Serial.println(WiFi.softAPIP());
                isReady = 1;
}
else {

  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IPadress, gatewayAddress, subnetAddress) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP with default data... ");
  Serial.println(WiFi.softAP(softApGivenName) ? "Ready" : "Failed!");

}
    return isReady;
}
