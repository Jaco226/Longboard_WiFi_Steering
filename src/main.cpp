#include <Servo.h>
#include "communication.hpp"


// UDP Config
WiFiUDP Udp;                                          // UDP Object
unsigned int localUdpPort = 4210;                     // UDP port to listen on
char incomingPacket[255];                             // buffor for message
char replyPacket[] = "Hi there! Got the message :-)"; // reply message


// constantants
extern const char * softApName = "SoftApByMe";
extern const char * pass       = "12345678";
extern const char servoPin     = D6;

//variables
extern int receivedPacket = 0;
int statNum        = 0;
int statNumCurrent = 0;
// SERVO Config
Servo myServo;


// functions declaration
void howMuchClients();

void setup(){
    WiFi.disconnect();

    Serial.begin(9600);
    Serial.println();
    myServo.attach(servoPin);

    Udp.begin(localUdpPort);
}

void loop(){
    howMuchClients();

    bool isPacketReceived = recieveUdpPacket(&receivedPacket);
    if (isPacketReceived) {
        Serial.println(receivedPacket);
    } else {
        // Serial.println
    }
    // myServo.write(receivedPacket);

    // if (receivedPacket != 0) { }
}

void howMuchClients(){
    statNum = WiFi.softAPgetStationNum();
    if (statNumCurrent != statNum) {
        Serial.print("Soft-AP Station numbers = ");
        Serial.println(statNum);
    }
    statNumCurrent = statNum;
}
