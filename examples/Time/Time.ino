#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "ESP8266TimeHelper.h"

ESP8266TimeHelper timeHelper;

#define WIFI_SSID "WIFI_SSID"
#define WIFI_PASSWORD "WIFI_PSW"

void setup()
{

    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.println("Aquiring time...");
    Serial.println();

    //Time Zone from GMT
    timeHelper.TZ = 3; //GMT+3

    //Daylight saving time in minutes
    timeHelper.DST_MN = 0;

    //Get time from server
    timeHelper.setClock();

    Serial.println("Number of Days This Year (since January): " + String(timeHelper.getNumberOfDayThisYear()));
    Serial.println("Day of Week Number: " + String(timeHelper.getDayOfWeek()));
    Serial.println("Day of Week String: : " + String(timeHelper.getDayOfWeekString()));
    Serial.println("Total seconds today: : " + String(timeHelper.getCurrentSecond()));
}

void loop()
{

    //Print out the time
    uint32_t timestamp = timeHelper.getUnixTime();
    Serial.println("Current Timestamp (GMT+3): " + String(timestamp));

    int d = timeHelper.getDay();
    int m = timeHelper.getMonth();
    int y = timeHelper.getYear();
    int hr = timeHelper.getHour();
    int min = timeHelper.getMin();
    int sec = timeHelper.getSec();
    Serial.print("Current Time (GMT+3): ");
    Serial.print(d);
    Serial.print("/");
    Serial.print(m);
    Serial.print("/");
    Serial.print(y);
    Serial.print(" ");
    Serial.print(hr);
    Serial.print(":");
    Serial.print(min);
    Serial.print(":");
    Serial.println(sec);
    Serial.println();

    delay(1000);
}