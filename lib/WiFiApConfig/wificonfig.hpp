#include <Arduino.h>


bool wifiSoftApSetup(char  local_IPadress, char gatewayAddress, char subnetAddress, const char * softApGivenName = "DefaultSoftAp", char * softapPassword = NULL, int channel = 0, bool isHidden = 0, int maxClients = 0);
