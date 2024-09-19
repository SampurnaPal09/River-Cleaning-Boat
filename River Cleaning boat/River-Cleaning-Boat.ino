#define ENA D1       // Enable/speed motors Right      GPIO(5)
#define IN_1 D2     // L298N in1 motors Right          GPIO(4)
#define IN_2 D3    // L298N in2 motors Right           GPIO(0)
#define IN_3 D4   // L298N in3 motors Left             GPIO(2)
#define IN_4 D5  // L298N in4 motors Left              GPIO(14)
#define ENB D6  // Enable/speed motors Left            GPIO(12)

#include <ESP8266WiFi.h>    //To connect the ESP8266 chip to a WiFi network
#include <WiFiClient.h>    //enables communication between the ESP8266 and other devices
#include <ESP8266WebServer.h>   //The ESP8266 to act as a web server.
String command;             //String to store app command state.
int speedCar = 1000;       // Initialize the motors speed

const char* ssid = "NodeMCU Car";   //Mobile application name
ESP8266WebServer server(80);

void setup() 
{
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
// Declaration of pin modes
Serial.begin(115200);
 
// Connecting WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}
void moveForward()
{ 
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
      //Function for forward movement
}

void moveBackward()
{ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
      //Function for backward movement
}

void turnRight()
{ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
      //Function for turn right
}

void turnLeft()
{
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
      //Function for turn left
}

void stop()
{  
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
      //Function for stop the boat
}

void loop()
{
    server.handleClient();
      command = server.arg("State");  //Get command from mobile application
      if (command == "F")            // "F" indicates forward movement command
      moveForward();                // call the moveForward function
      else if (command == "B")     // "B" indicates backward movement command
      moveBackward();             // call the moveBackward function
      else if (command == "L")    // "L" indicates turn in left command
      turnLeft();                 // call the turnLeft function
      else if (command == "R")    // "R" indicates turn in right command
      turnRight();                // call the turnRight function
      else if (command == "S")    // "S" indicates stop command
      stop();                     // call the stop function
}
void HTTP_handleRoot(void)
{
  if( server.hasArg("State") )
  {
    Serial.println(server.arg("State"));  //To print the state in Arduino IDE serial monitor
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}