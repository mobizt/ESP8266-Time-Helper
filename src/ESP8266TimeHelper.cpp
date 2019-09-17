/*
 * ESP8266 Internet Time Helper Arduino Library v 1.0.1
 *
 * The MIT License (MIT)
 * Copyright (c) 2019 K. Suwatchai (Mobizt)
 * 
 * 
 * Permission is hereby granted, free of charge, to any person returning a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "ESP8266TimeHelper.h"

ESP8266TimeHelper::ESP8266TimeHelper()
{
}
uint32_t ESP8266TimeHelper::getUnixTime()
{
    uint32_t utime = (msec_time_diff + millis()) / 1000;
    return utime;
}

time_t ESP8266TimeHelper::getTimestamp(int year, int mon, int date, int hour, int mins, int sec)
{
    struct tm timeinfo;
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = mon -1;
    timeinfo.tm_mday = date;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = mins;
    timeinfo.tm_sec = sec;
    time_t ts = mktime(&timeinfo);
    return ts;
}

bool ESP8266TimeHelper::setClock()
{
    const char timeServer1[100] = "pool.ntp.org";
    const char timeServer2[100] = "time.nist.gov";
    configTime((TZ)*3600, (DST_MN)*60, timeServer1, timeServer2, NULL);

    now = time(nullptr);
    int cnt = 0;
    while (now < 8 * 3600 * 2 && cnt < 20)
    {
        delay(50);
        now = time(nullptr);
        cnt++;
    }

    uint64_t tmp = now;
    tmp = tmp * 1000;
    msec_time_diff = tmp - millis();

    gmtime_r(&now, &timeinfo);

    clockReady = now > 8 * 3600 * 2;
    return clockReady;
}

int ESP8266TimeHelper::getYear()
{
    setSysTime();
    return timeinfo.tm_year + 1900;
}
int ESP8266TimeHelper::getMonth()
{
    setSysTime();
    return timeinfo.tm_mon + 1;
}
int ESP8266TimeHelper::getDay()
{
    setSysTime();
    return timeinfo.tm_mday;
}

int ESP8266TimeHelper::getDayOfWeek()
{
    setSysTime();
    return timeinfo.tm_wday;
}
String ESP8266TimeHelper::getDayOfWeekString()
{
    setSysTime();
    return dow[timeinfo.tm_wday];
}

int ESP8266TimeHelper::getHour()
{
    setSysTime();
    return timeinfo.tm_hour;
}

int ESP8266TimeHelper::getMin()
{
    setSysTime();
    return timeinfo.tm_min;
}
int ESP8266TimeHelper::getSec()
{
    setSysTime();
    return timeinfo.tm_sec;
}
int ESP8266TimeHelper::getNumberOfDayThisYear()
{
    setSysTime();
    return timeinfo.tm_yday + 1;
}
void ESP8266TimeHelper::setSysTime()
{
    now = time(nullptr);
    gmtime_r(&now, &timeinfo);
}

int ESP8266TimeHelper::totalDays(int y, int m, int d)
{
    static char daytab[2][13] =
        {
            {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
            {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
    int daystotal = d;
    for (int year = 1; year <= y; year++)
    {
        int max_month = (year < y ? 12 : m - 1);
        int leap = (year % 4 == 0);
        if (year % 100 == 0 && year % 400 != 0)
            leap = 0;
        for (int month = 1; month <= max_month; month++)
        {
            daystotal += daytab[leap][month];
        }
    }
    return daystotal;
}
int ESP8266TimeHelper::getTotalDays(int year, int month, int day)
{
    return totalDays(year, month, day) - totalDays(1970, 1, 1);
}

int ESP8266TimeHelper::dayofweek(int y, int m, int d) /* 1 <= m <= 12,  y > 1752 (in the U.K.) */
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

int ESP8266TimeHelper::getCurrentSecond()
{
    return (timeinfo.tm_hour * 3600) + (timeinfo.tm_min * 60) + timeinfo.tm_sec;
}
uint64_t ESP8266TimeHelper::getCurrentTimestamp()
{
    return now;
}
void ESP8266TimeHelper::getTimeFromSec(int secCount, int &yrs, int &months, int &days, int &hr, int &min, int &sec)
{
    int _yrs = secCount / (365 * 24 * 3600);
    secCount = secCount - _yrs * (365 * 24 * 3600);
    yrs = _yrs;
    int _months = secCount / (30 * 24 * 3600);
    secCount = secCount - _months * (30 * 24 * 3600);
    months = _months;
    int _days = secCount / (24 * 3600);
    secCount = secCount - _days * (24 * 3600);
    days = _days;
    int _hr = secCount / 3600;
    secCount = secCount - _hr * 3600;
    hr = _hr;
    int _min = secCount / 60;
    secCount = secCount - _min * 60;
    min = _min;
    sec = secCount;
}
