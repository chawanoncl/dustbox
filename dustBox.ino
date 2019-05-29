// Include application, user and local libraries
#include <SPI.h>
#include <TFT_22_ILI9225.h>


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

// Setup



#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include "PMS.h"
ESP8266WiFiMulti WiFiMulti;

PMS pms(Serial);
PMS::DATA data;

const char * myWriteAPIKey = "APIKEYS";
int a = data.PM_AE_UG_10_0;
char buf[4];


void setup() {
  Serial.begin(9600);
  tft.begin();
  
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  WiFiMulti.addAP("ssid", "password"); // exam "Dustbox","admin"
  randomSeed(50);

}

// Loop
void loop() {
  tft.setOrientation(3);
  /*tft.drawCircle(40, 60, 30, COLOR_BLUE);
  tft.drawCircle(40, 140, 30, COLOR_BLUE);*/
  

  
  if (pms.read(data))
  {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.println();
    tft.setFont(Terminal6x8);
  tft.drawText(83, 150, "30");
  tft.drawText(103, 150, "60");
  tft.drawText(123, 150, "90");
  tft.drawText(140, 150, "120");
  tft.drawText(165, 150, "250");
  tft.drawText(190, 150, "250+");
  tft.fillRectangle(83, 160, 103, 170, COLOR_GREEN);
  tft.fillRectangle(103, 160, 123, 170, COLOR_YELLOW);
  tft.fillRectangle(123, 160, 143, 170, COLOR_ORANGE);
  tft.fillRectangle(143, 160, 163, 170, COLOR_RED);
  tft.fillRectangle(163, 160, 183, 170, COLOR_VIOLET);
  tft.fillRectangle(183, 160, 203, 170, COLOR_DARKRED);
  tft.drawCircle(150, 90, 50, COLOR_CYAN); //old 150,100,50
  tft.drawLine(75, 30, 75, 150, COLOR_YELLOW);
  
  tft.drawRectangle(0, 0, tft.maxX() - 1, tft.maxY() - 1, COLOR_WHITE);
    tft.setFont(Terminal12x16);
    tft.drawText(117, 13, "PM 2.5");
    
    if (data.PM_AE_UG_2_5 <= 30)
    tft.drawText(140, 75, String(data.PM_AE_UG_2_5),COLOR_GREEN);
    if (data.PM_AE_UG_2_5 <= 60&&data.PM_AE_UG_2_5 > 30)
    tft.drawText(140, 75, String(data.PM_AE_UG_2_5),COLOR_YELLOW);
    if (data.PM_AE_UG_2_5 <= 90&&data.PM_AE_UG_2_5 > 60)
    tft.drawText(140, 75, String(data.PM_AE_UG_2_5),COLOR_ORANGE);
    if (data.PM_AE_UG_2_5 <= 120&&data.PM_AE_UG_2_5 > 90)
    tft.drawText(140, 75, String(data.PM_AE_UG_2_5),COLOR_RED);
     if (data.PM_AE_UG_2_5 < 250&&data.PM_AE_UG_2_5 > 120)
    tft.drawText(140, 75, String(data.PM_AE_UG_2_5),COLOR_VIOLET);
     if (data.PM_AE_UG_2_5 >= 250)
    tft.drawText(140, 75, String(data.PM_AE_UG_2_5),COLOR_DARKRED);
    
    if (data.PM_AE_UG_2_5 <= 9)
      tft.fillRectangle(152, 75, 179, 91, COLOR_BLACK);
    else if (data.PM_AE_UG_2_5 <= 99 && data.PM_AE_UG_2_5 >= 10)
      tft.fillRectangle(164, 75, 179, 91, COLOR_BLACK);
    tft.drawText(120, 110, "ug/m3");
    
    
    tft.setFont(Terminal6x8);
    tft.drawText(30, 16, "PM 1");
    tft.setFont(Terminal12x16);
    tft.drawText(35, 55, String(data.PM_AE_UG_1_0));
    if (data.PM_AE_UG_1_0 <= 9)
      tft.fillRectangle(47, 55, 74, 71, COLOR_BLACK);
    else if (data.PM_AE_UG_1_0 <= 99 && data.PM_AE_UG_10_0 >= 10)
      tft.fillRectangle(59, 55, 74, 71, COLOR_BLACK);

    tft.setFont(Terminal6x8);
    tft.drawText(30, 98, "PM 10");
    tft.setFont(Terminal12x16);
    tft.drawText(35, 135, String(data.PM_AE_UG_10_0));
    if (data.PM_AE_UG_10_0 <= 9)
      tft.fillRectangle(47, 135, 74, 151, COLOR_BLACK);
    else if (data.PM_AE_UG_10_0 <= 99 && data.PM_AE_UG_10_0 >= 10)
      tft.fillRectangle(59, 135, 74, 151, COLOR_BLACK);



    

    if ((WiFiMulti.run() == WL_CONNECTED)) {
      HTTPClient http;
      String urlTP = "thingspeak api" + String(data.PM_AE_UG_1_0) + "&field2=" + String(data.PM_AE_UG_2_5) + "&field3=" + String(data.PM_AE_UG_10_0);
      Serial.println(urlTP);
      http.begin(urlTP); //HTTP


      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
        }
      }
      else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    }


    delay(3000);
  }


}
