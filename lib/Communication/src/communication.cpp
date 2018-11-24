#include "communication.hpp"


// zwraca true jeżeli odebrano pakiet, wtedy do zmiennej parsed_int wpisywana jest parsowana liczba
// w przeciwnym razie false

bool  recieveUdpPacket(int * parsed_int){
    bool result    = false;
    int packetSize = Udp.parsePacket();

    if (packetSize) {
        Serial.printf("Received %d bytes from %s, port %d\n", packetSize,
          Udp.remoteIP().toString().c_str(), Udp.remotePort());
        int len = Udp.read(incomingPacket, 255);
        if (len > 0) {
            incomingPacket[len] = 0;
        }
        // pase Int
        if (parsed_int != NULL) {
            *parsed_int = atoi(incomingPacket);
        }
        result = true;
        // Send back message
        // Serial.printf("UDP packet contents: %s\n Int value is: %d \n", incomingPacket, recievedTemp);
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(replyPacket);
        Udp.endPacket();
    }
    return result;
}
