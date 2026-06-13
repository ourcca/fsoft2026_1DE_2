//
// Created by rodri on 07/06/2026.
//
#include "model/Time.h"
#include "exceptions/InvalidDataException.h"

Time::Time() {
    setTime(0, 0);
}

Time::Time(int hour, int minute) {
    setTime(hour, minute);
}

bool Time::isValid(int hour, int minute) {
    return hour >= 0 && hour < 24 &&
           minute >= 0 && minute < 60;
}

void Time::setTime(int hour, int minute) {
    if (!isValid(hour, minute))
    {
        throw InvalidDataException("Horário inválido.");
    }

    this->hour = hour;
    this->minute = minute;

}

void Time::getTime(int& hour, int& minute) const {
    hour = this->hour;
    minute = this->minute;
}

int Time::minutesSinceMidnight() const {
    return hour * 60 + minute;
}

bool Time::operator==(const Time& obj) const {
    return hour == obj.hour && minute == obj.minute;
}

bool Time::operator<(const Time& obj) const {
    return minutesSinceMidnight() < obj.minutesSinceMidnight();
}

bool Time::operator>(const Time& obj) const {
    return obj < *this;
}

bool Time::operator!=(const Time& obj) const {
    return !(*this == obj);
}