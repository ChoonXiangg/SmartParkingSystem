#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <string>
#include "ThingSpeak.h"
#include "secrets.h"
#include "homepage.h"
#include "reserve.h"
#include "reserve2.h"
#include "dht11.h"

//DHT11
#include <DFRobot_DHT11.h>

//Servo
#include <Servo.h>

//LCD
#include "rgb_lcd.h"

//PN532
#include <Adafruit_PN532.h>

//DHT11
#define DHT11_PIN 4

//HC-SR04
#define TRIG_PIN 5
#define ECHO_PIN 18

//LED
#define PIN_RED 33
#define PIN_GREEN 27
#define PIN_BLUE 32

//PN532
#define PN532_IRQ 25
#define PN532_RESET 26

//DHT11
DFRobot_DHT11 DHT;

//HC-SR04
long duration;
float cms;
int x;

//Servo
static const int SERVO_PIN = 13;
Servo servo1;
int posDegrees = 180;

//LCD
rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
const char* PARAM_INPUT = "numberPlate";
const char* inputMessage;

//PN532
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);
uint8_t success;
uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
uint8_t uidLength;

String getTemp() {
  DHT.read(DHT11_PIN);
  String temp = String(DHT.temperature);
  return temp;
}

String getHumidity() {
  DHT.read(DHT11_PIN);
  String hum = String(DHT.humidity);
  return hum;
}

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASSWORD;
enum STATES { FREE,
              RESERVED };
enum STATES currentState = FREE;
WiFiClient client;
unsigned long myChannelNumber = SECRET_CH_ID;
const char* myWriteAPIKey = SECRET_WRITE_APIKEY;
String temperature = getTemp();
String humidity = getHumidity();

AsyncWebServer server(80);

std::string getLED(float cms) {
  if (cms <= 10) {
    return "0";
  } else {
    return "1";
  }
}

void notFound(AsyncWebServerRequest* request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    std::string homepagePart1String(homepagePart1);
    std::string homepagePart2String(homepagePart2);
    std::string homepage = homepagePart1String + getLED(cms) + homepagePart2String;
    const char* HOMEPAGE_C_STR = homepage.c_str();
    request->send_P(200, "text/html", HOMEPAGE_C_STR);
  });
  server.on("/reserve", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", reserve);
  });
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest* request) {
    String inputMessage;
    String inputParam;
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value().c_str();
      inputParam = PARAM_INPUT;
      currentState = RESERVED;
      lcd.print(inputMessage);
      std::string reserve2Part1String(reserve2Part1);
      std::string reserve2Part2String(reserve2Part2);
      std::string inputMessageString(inputMessage.c_str());
      std::string reserve2 = reserve2Part1String + inputMessageString + reserve2Part2String;
      const char* RESERVE2_C_STR = reserve2.c_str();
      request->send_P(200, "text/html", RESERVE2_C_STR);
    } else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
  });
  server.on("/dht11", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", dht11);
  });
  server.on("/timerEnd", HTTP_GET, [](AsyncWebServerRequest* request) {
    currentState = FREE;
  });
  server.onNotFound(notFound);
  server.begin();
  Serial.println("HTTP server started");

  //HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //LED
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  //Servo
  servo1.attach(SERVO_PIN);

  //LCD
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);

  //PN532
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1)
      ;
  }
  Serial.print("Found chip PN5");
  Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. ");
  Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.');
  Serial.println((versiondata >> 8) & 0xFF, DEC);
}

void loop() {
  delay(2);
  switch (currentState) {
    case FREE:
      lcd.clear();
      if (posDegrees == 0) {
        for (posDegrees = 0; posDegrees <= 180; posDegrees++) {
          servo1.write(posDegrees);
          delay(20);
        }
      }
      digitalWrite(TRIG_PIN, LOW);
      delayMicroseconds(5);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
      duration = pulseIn(ECHO_PIN, HIGH);
      cms = (duration / 2) / 29.1;
      if (cms <= 10) {
        analogWrite(PIN_RED, 255);
        analogWrite(PIN_GREEN, 0);
        analogWrite(PIN_BLUE, 0);
      } else {
        analogWrite(PIN_RED, 0);
        analogWrite(PIN_GREEN, 255);
        analogWrite(PIN_BLUE, 0);
      }
      ThingSpeak.setField(1, temperature);
      ThingSpeak.setField(2, humidity);
      x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      temperature = getTemp();
      humidity = getHumidity();
      break;
    case RESERVED:
      analogWrite(PIN_RED, 0);
      analogWrite(PIN_GREEN, 0);
      analogWrite(PIN_BLUE, 255);
      if (posDegrees == 180) {
        for (posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        delay(20);
        }
      }
      success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 1000);
      if (success) {
        lcd.clear();
        for (posDegrees = 0; posDegrees <= 180; posDegrees++) {
          servo1.write(posDegrees);
          delay(20);
        }
        currentState = FREE;
      }
      ThingSpeak.setField(1, temperature);
      ThingSpeak.setField(2, humidity);
      x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      temperature = getTemp();
      humidity = getHumidity();
      break;
  }
}