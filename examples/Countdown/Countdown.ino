
#include <ESP8266WiFi.h>
#include <ESP8266TimeHelper.h>

ESP8266TimeHelper timeHelper;

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PSW"

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

    Serial.println("Aquiring time from NTP server...");
    Serial.println();

    //Time Zone from GMT
    timeHelper.TZ = 3; //GMT+3

    //Daylight saving time in minutes
    timeHelper.DST_MN = 0;

    //Get time from server
    if (!timeHelper.setClock())
    {
        Serial.println("Can't set clock...");
        return;
    }

    Serial.println("Number of Days This Year (since January): " + String(timeHelper.getNumberOfDayThisYear()));
    Serial.println("Day of Week Number: " + String(timeHelper.getDayOfWeek()));
    Serial.println("Day of Week String: : " + String(timeHelper.getDayOfWeekString()));
    Serial.println("Total seconds today: : " + String(timeHelper.getCurrentSecond()));
    Serial.println();
}

void loop()
{

    if (!timeHelper.clockReady)
        return;

    //Print out current date and time
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

    uint32_t todayFromMidnightTimestamp = timeHelper.getTimestamp(y, m, d, 0, 0, 0);
    uint32_t currentTimestamp = timeHelper.getUnixTime();
    uint32_t totalSecondsFromMidnight = currentTimestamp - todayFromMidnightTimestamp;

    //Assumed we countdown until 15:00:00 everyday
    uint8_t targetSec = 0;
    uint8_t targetMin = 0;
    uint8_t targetHr = 15;
    uint32_t targetSecondsFromMidnight = targetHr * 60 * 60 + targetMin * 60 + targetSec;

    if (targetSecondsFromMidnight >= totalSecondsFromMidnight)
    {
        uint32_t diffSeconds = targetSecondsFromMidnight - totalSecondsFromMidnight;
        int remainYrs, remainMonths, remainDays, remainHr, remainMin, remainSec;
        timeHelper.getTimeFromSec(diffSeconds, remainYrs, remainMonths, remainDays, remainHr, remainMin, remainSec);
        Serial.print("Everyday countdown until 15:00:00 is ");
        Serial.print(remainHr);
        Serial.print(" Hr, ");
        Serial.print(remainMin);
        Serial.print(" Min and ");
        Serial.print(remainSec);
        Serial.println(" Sec to go.");
    }
    else
    {
        Serial.println("Everyday countdown until 15:00:00 was passed.");
    }

    //Assumed we countdown until 18/12/2019 8:30:45
    uint32_t targetTimestamp = timeHelper.getTimestamp(2019, 12, 18, 8, 30, 45);
    if (targetTimestamp >= currentTimestamp)
    {
        uint32_t diffSeconds = targetTimestamp - currentTimestamp;
        int remainYrs, remainMonths, remainDays, remainHr, remainMin, remainSec;
        timeHelper.getTimeFromSec(diffSeconds, remainYrs, remainMonths, remainDays, remainHr, remainMin, remainSec);
        Serial.print("One time countdown until 18/12/2019 8:30:45 is ");
        Serial.print(remainYrs);
        Serial.print(" Years, ");
        Serial.print(remainMonths);
        Serial.print(" Months, ");
        Serial.print(remainDays);
        Serial.print(" Days, ");
        Serial.print(remainHr);
        Serial.print(" Hr, ");
        Serial.print(remainMin);
        Serial.print(" Min and ");
        Serial.print(remainSec);
        Serial.println(" Sec to go.");
    }
    else
    {
        Serial.println("One time countdown until 18/12/2019 8:30:45 was finished.");
    }
    Serial.println();

    delay(1000);
}