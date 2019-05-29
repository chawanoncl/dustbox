// Include application, user and local libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <TFT_22_ILI9225.h>

// #define TFT_RST 8
// #define TFT_RS  9
// #define TFT_CS  10  // SS
// #define TFT_SDI 11  // MOSI
// #define TFT_CLK 13  // SCK
// #define TFT_LED 3   // 0 if wired to +5V directly

#define TFT_RST D4
#define TFT_RS  D2
#define TFT_CS  D8  // SS
#define TFT_SDI D7  // MOSI
#define TFT_CLK D5  // SCK
#define TFT_LED D1   // 0 if wired to +5V directly

// Use hardware SPI (faster - on Uno: 13-SCK, 12-MISO, 11-MOSI)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);
// Use software SPI (slower)
//TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_SDI, TFT_CLK, TFT_LED);

// Variables and constants
// uint16_t x, y;
// boolean flag = false;


#define COLOR_ACACAC          RGB888_RGB565(0xACACACu)
#define COLOR_5F7883          RGB888_RGB565(0x5F7883u)

const char *ssid = ". . . .";
const char *password = ". . . .";

MDNSResponder mdns;

// Setup
void setup() {
  tft.begin();
  Serial.begin(115200);
  tft.fillRectangle(0, 0, tft.maxX(), tft.maxY(), COLOR_ACACAC); // background
  tft.drawRectangle(1, 1, tft.maxX() - 2, tft.maxY() - 2, COLOR_5F7883); // border
  tft.setOrientation(3);
  tft.setFont(Terminal11x16);
  tft.setBackgroundColor(COLOR_ACACAC);
  
}

// Loop
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    tft.fillRectangle(10, 40, 200, 56, COLOR_ACACAC);
    tft.drawText(10, 40, "Connecting to " + String(ssid), COLOR_5F7883);
    tft.fillRectangle(10, 60, 200, 76, COLOR_ACACAC);
    Serial.print(ssid);
    Serial.println("...");
    WiFi.begin(ssid, password);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
    Serial.println("WiFi connected");
    tft.fillRectangle(10, 40, 200, 56, COLOR_ACACAC);
    tft.drawText(10, 40, "Connected to " + String(ssid), COLOR_5F7883);
    Serial.print("Direccion IP: ");
    tft.fillRectangle(10, 60, 200, 76, COLOR_ACACAC);
    tft.drawText(10, 60, "IP: " + WiFi.localIP().toString(), COLOR_5F7883);
    Serial.println(WiFi.localIP());

    if (mdns.begin("tft", WiFi.localIP())) {
      Serial.println("MDNS started.");
    }

    
  }

}