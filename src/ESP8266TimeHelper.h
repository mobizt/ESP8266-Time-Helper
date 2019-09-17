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

#ifndef ESP_TIME_HELPER_h
#define ESP_TIME_HELPER_h
#include <time.h>
#include <Arduino.h>

class ESP8266TimeHelper
{
  public:
    ESP8266TimeHelper();
    uint32_t getUnixTime();
    time_t getTimestamp(int year, int mon, int date, int hour, int mins, int sec);
    bool setClock();
    int getYear();
    int getMonth();
    int getDay();
    int getDayOfWeek();
    String getDayOfWeekString();
    int getHour();
    int getMin();
    int getSec();
    int getNumberOfDayThisYear();
    int getTotalDays(int year, int month, int day);
    int dayofweek(int y, int m, int d);
    int getCurrentSecond();
    uint64_t getCurrentTimestamp();
    void setSysTime();
    void getTimeFromSec(int secCount, int &yrs, int &months, int &days, int &hr, int &min, int &sec);

    time_t now;
    uint64_t msec_time_diff = 0;
    struct tm timeinfo;
    uint8_t TZ = 0;
    uint8_t DST_MN = 0;
    bool clockReady = false;

  private:
    int totalDays(int y, int m, int d);  
    const char *dow[20] = {"sunday", "monday", "tuesday", "wednesday", "thurseday", "friday", "saturday"};
};

#endif
