#include <Servo.h>
#include "communication.hpp"


// UDP Config
WiFiUDP Udp;                                          // UDP Object
unsigned int localUdpPort = 4210;                     // UDP port to listen on
char incomingPacket[255];                             // buffor for message
char replyPacket[] = "Hi there! Got the message :-)"; // reply message


// constantants
const char * softApName = "SoftApByMe";
const char * pass       = "12345678";
const char servoPin     = D6;

//variables
int receivedPacket = 0;
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
    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP(softApName, pass, 1, false, 4) ? "Ready" : "Failed!");

    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
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
