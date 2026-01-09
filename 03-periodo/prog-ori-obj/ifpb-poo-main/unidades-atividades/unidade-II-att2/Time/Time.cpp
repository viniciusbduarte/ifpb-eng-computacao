#include <iostream>
#include <format>
#include <ctime>
using std::cout, std::endl, std::format;


#include "Time.hpp"

Time::Time(int hr, int min, int sec)
{
    if (hr == 0 && min == 0 && sec == 0) {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        setTime(now->tm_hour, now->tm_min, now->tm_sec);
    } else {
        setTime(hr, min, sec);
    }
}


void Time::setTime(int h, int m, int s)
{
  setHour(h);
  setMinute(m);
  setSecond(s);  
}

std::string Time::toUniversal() const
{
	return format("{:02d}:{:02d}:{:02d}", hour, minute, second);
}

std::string Time::toStandard() const
{
	return format("{:02d}:{:02d}:{:02d} {}", ( (hour == 0 || hour == 12) ? 12 : hour % 12 ), minute, second, (hour < 12 ? "AM" : "PM"));
}


void Time::tick() {
    second += 1;

    if (second == 60) {
        second = 0;
        minute += 1;

        if (minute == 60) {
            minute = 0;
            hour += 1;

            if (hour == 24) {
                hour = 0;
            }
        }
    }
}
