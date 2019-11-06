/*Wifi Relay Controll





*/
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>



// Network SSID
const char* ssid = "SSID";
const char* password = "PASSWORD";

IPAddress ip(192, 168, 178, XXX);
IPAddress gateway(192, 168, 178, XXX);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 178, 1);


int Relay8 = D1;
int Relay1 = D2;
int Relay2 = D3;
int Relay3 = D4;
int Relay4 = D5;
int Relay5 = D6;
int Relay6 = D7;
int Relay7 = D8;

int RelayArray [] = {D1, D2, D3, D4, D5, D6, D7, D8};



//webserver und login

ESP8266WebServer server(80);
const char* www_username = "USERNAME";
const char* www_password = "HTML PASSCODE";



void setup() {

  Serial.begin(115200);
  delay(10);




  // pinsetup
  for (int i = 0; i <= 7; i++) {

    pinMode(RelayArray [i], OUTPUT);
    digitalWrite(RelayArray [i], HIGH);
  }



 // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Arduino Wlan");
  reconnect1(); // neuer Connectteil am Ende


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());



  // Start the server
  server.on("/", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    server.send(200, "text/plain", "Login OK");
  });

  server.on("/R1_ON", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay1, LOW);
    server.send(200, "text/plain", "Relais 1 an");
    ;
  });


  server.on("/R1_OFF", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay1, HIGH);
    server.send(200, "text/plain", "Relais 1 aus");
    ;
  });

  server.on("/R2_ON", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay2, LOW);
    server.send(200, "text/plain", "Relais 2 an");
    ;
  });


  server.on("/R2_OFF", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay2, HIGH);
    server.send(200, "text/plain", "Relais 2 aus");
    ;
  });


  server.on("/R3_ON", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay3, LOW);
    server.send(200, "text/plain", "Relais 3 an");
    ;
  });


  server.on("/R3_OFF", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay3, HIGH);
    server.send(200, "text/plain", "Relais 3 aus");
    ;
  });

  server.on("/R4_ON", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay4, LOW);
    server.send(200, "text/plain", "Relais 4 an");
    ;
  });


  server.on("/R4_OFF", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay4, HIGH);
    server.send(200, "text/plain", "Relais 4 aus");
    ;
  });


    server.on("/R5_ON", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay5, LOW);
    server.send(200, "text/plain", "Relais 5 an");
    ;
  });


  server.on("/R5_OFF", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay5, HIGH);
    server.send(200, "text/plain", "Relais 5 aus");
    ;
  });


    server.on("/R6_ON", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay6, LOW);
    server.send(200, "text/plain", "Relais 6 an");
    ;
  });


  server.on("/R6_OFF", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay6, HIGH);
    server.send(200, "text/plain", "Relais 6 aus");
    ;
  });


    server.on("/R7_ON", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay7, LOW);
    server.send(200, "text/plain", "Relais 7 an");
    ;
  });


  server.on("/R7_OFF", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay7, HIGH);
    server.send(200, "text/plain", "Relais 7 aus");
    ;
  });


    server.on("/R8_ON", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay8, LOW);
    server.send(200, "text/plain", "Relais 8 an");
    ;
  });


  server.on("/R8_OFF", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    digitalWrite(Relay8, HIGH);
    server.send(200, "text/plain", "Relais 8 aus");
    ;
  });


    






  server.begin();
  Serial.println("Server started");


  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {


  server.handleClient();
/*########### reconnect point 



*/
  if (WiFi.status() != WL_CONNECTED) {
    reconnect1();
  }

}

void reconnect1() {

  int wifi_retry = 0;
  while (WiFi.status() != WL_CONNECTED && wifi_retry < 5 ) {
    wifi_retry++;
    Serial.println("WiFi not connected. Try to reconnect");
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.mode(WIFI_STA);
    WiFi.config(ip, gateway, subnet, dns);
    WiFi.begin(ssid, password);
    delay(10000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    delay(500);
    Serial.print("..");
    Serial.println("WiFi  connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    delay(500);
    Serial.println("");
    Serial.println("WiFi not connected");
  }
}
