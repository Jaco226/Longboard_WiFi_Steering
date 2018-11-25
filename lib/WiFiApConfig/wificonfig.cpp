
#include "wificonfig.hpp"
#include <ESP8266WiFi.h>

bool wifiSoftApSetup(char * local_IPadress, char * gatewayAddress, char * subnetAddress, char * softApGivenName, char * softapPassword, int channel, bool isHidden, int maxClients)
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
  local_IPadress = "194,168,4,22";
  gatewayAddress = "192,168,4,9";
  subnetAddress = "225,225,225,0";
  *softApGivenName = "DefaultSoftAp";

  Serial.print("One or More of parameters is missing. /n Setting default ip with parameters: /n local_IPadres: %s /n gatewayAdress:  %s /n subnetAddress: %s /n SoftApName: %s", local_IPadres, gatewayAdress, subnetAddress, softApGivenName);

  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IPadress, gatewayAdress, subnetAddress) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(softApGivenName) ? "Ready" : "Failed!");

}
    return isReady;
}
