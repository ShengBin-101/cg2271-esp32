// Summary:
// This code sets up an ESP32 to connect to a Wi-Fi network and act as a web server. 
// It listens for HTTP requests to control an LED connected to GPIO 26. 
// The LED can be turned on or off with different colors (Red, Green, Blue) based on the request.

#include <WiFi.h>

#define RXD2 16
#define TXD2 17

void setLEDState(int state, String msg, byte serialCmd);
void handleRequest(String req);

const char* ssid = "leftoverice";
const char* password = "whereisrouter";

WiFiServer server(80);

String response, ip_address;
String output26State = "off";
const int output26 = 26;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;
int wait30 = 30000;

IPAddress local_IP(192, 168, 27, 189); 
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4); 

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(output26, OUTPUT);
  digitalWrite(output26, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  ip_address = WiFi.localIP().toString();
  Serial.println("IP address: " + ip_address);
  server.begin();
}

void loop() {
  if ((WiFi.status() != WL_CONNECTED) && (millis() > wait30)) {
    Serial.println("Trying to reconnect WiFi...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    wait30 = millis() + 30000;
  } 

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  Serial.print("New client: ");
  Serial.println(client.remoteIP());
   
  String req = client.readStringUntil('\r');
  Serial.println(req);

  handleRequest(req);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println(response);

  client.flush();
  client.stop();
  Serial.println("Client disconnected.");
}

void handleRequest(String req) {
  if(req.indexOf("status") != -1) {
    response = "WiFi Connected: " + ip_address;
  } else if(req.indexOf("redOn") != -1) {
    setLEDState(HIGH, "RED LED ON", 0x31);
    // print the response to the serial monitor
    Serial.println("RED LED ON");
  } else if(req.indexOf("redOff") != -1) {
    setLEDState(LOW, "RED LED OFF", 0x30);
    Serial.println("RED LED OFF");
  } else if(req.indexOf("greenOn") != -1) {
    setLEDState(HIGH, "GREEN LED ON", 0x33);
    Serial.println("GREEN LED ON");
  } else if(req.indexOf("greenOff") != -1) {
    setLEDState(LOW, "GREEN LED OFF", 0x32);
    Serial.println("GREEN LED OFF");
  } else if(req.indexOf("blueOn") != -1) {
    setLEDState(HIGH, "BLUE LED ON", 0x35);
    Serial.println("BLUE LED ON");
  } else if(req.indexOf("blueOff") != -1) {
    setLEDState(LOW, "BLUE LED OFF", 0x34);
    Serial.println("BLUE LED OFF");
  }
}

void setLEDState(int state, String msg, byte serialCmd) {
  digitalWrite(output26, state);
  response = msg;
  Serial2.write(serialCmd);
}
