#include <WiFi.h>
#include <HTTPClient.h>

#include <ESP32Servo.h>
#include <Keypad.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte COLS = 4;
const byte ROWS = 4;

const char WIFI_SSID[] = "daa2";         // CHANGE IT
const char WIFI_PASSWORD[] = "ClusterNord"; // CHANGE IT
char API_URL[] = "http://192.168.88.26:8080"; // CHANGE IT

char hexaKeys[ROWS][COLS]={
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
};
char key;
char code[5] = "0000";
int cur = 0;
char line1[32] = "     ";
char line2[32] = "     ";
int messageTimer = 0;
int messageDuration = 100;


byte colPins[COLS] = {23,19,32,33};
byte rowPins[ROWS] = {25,26,27,14};

Keypad key_pad   = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


const int SERVO_PIN = 13;
int servo_angle = 0;
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN, 900, 1500);
  servo.write(servo_angle);

  // WIFI CONFIG
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("\nConnecting");

  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());


  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  Serial.println("Setup complete");
}

void openDoor() {
  servo.write(2000);
}

void closeDoor() {
  servo.write(1000);
}

void resetCode() {
  strcpy(code, "0000");
  cur = 0;
}

bool checkCode() {
  HTTPClient http;
  char urlstring[255] = "";
  strcat(urlstring, API_URL);
  strcat(urlstring, "/checkToken?token=");
  strcat(urlstring, code);
  http.begin(urlstring); //HTTP
  int httpCode = http.GET();
  String payload = http.getString();
  return !strcmp(payload.c_str(), "true");
}

bool useCode() {
  HTTPClient http;
  char urlstring[255] = "";
  strcat(urlstring, API_URL);
  strcat(urlstring, "/useToken?token=");
  strcat(urlstring, code);
  http.begin(urlstring);
  int httpCode = http.GET();
  String payload = http.getString();
  return !strcmp(payload.c_str(), "true");
}

void message(char* msg) {
  strcpy(line2, msg);
  messageTimer = 0;
}

void loop() {
  messageTimer++;
//  if (messageTimer > messageDuration) {
//    strcpy(line2, "     ");
//  }
  display.clearDisplay();
  display.setCursor(0, 0);
  strcpy(line1, code);
  display.println(line1);
  display.println(line2);
  key = key_pad.getKey();
  if (key) {
    Serial.println(key);
    if (isDigit(key)) {
      code[cur] = key;
      cur++;
      cur %= 4;

    } else if (key == 'A') {
      if (checkCode()) {
        message("\nPIN\nrichtig");
      } else {
        message("\nPIN falsch");
      }
    } else if (key == 'D') {
      if (useCode()) {
        openDoor();
        message("\nT\x81r\nge\224ffnet");
        resetCode();
      } else {
        message("\nPIN falsch");
      }
    } else if (key == 'B') {
      closeDoor();
      message("\nT\x81r\ngeschlossen");
    } else if (key == 'C') {
      resetCode();
      message("\nPIN\ngeleert");
    }
    Serial.println(code);
    Serial.print("cur: ");
    Serial.println(cur);
  }
  display.display();
}
