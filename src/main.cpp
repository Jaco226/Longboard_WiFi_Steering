#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <stdlib.h>
#include <Servo.h>

// SerialConfig


// WiFi Parameters
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);
// UDP Config
WiFiUDP Udp;                                          // UDP Object
unsigned int localUdpPort = 4210;                     // UDP port to listen on
char incomingPacket[255];                             // buffor for message
char replyPacket[] = "Hi there! Got the message :-)"; // reply message
// SERVO Config
Servo myServo;
// Timers


// constantants
const char * softApName = "SoftApByMe";
const char * pass       = "12345678";
const char d_led        = D7;
const char d_led3       = D5;
const char servoPin     = D6;

// variables

int statNum        = 0;
int statNumCurrent = 0;
int receivedPacket = 0;

// functions declaration

void howMuchClients();


// zwraca true jeżeli odebrano pakiet, wtedy do zmiennej parsed_int wpisywana jest parsowana liczba
// w przeciwnym razie false
bool  recieveUdpPacket(int * parsed_int);
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
