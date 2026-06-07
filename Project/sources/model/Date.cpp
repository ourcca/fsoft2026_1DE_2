#include "model/Date.h"
#include <chrono>
#include <ctime>
#include <cstdlib>

Date::Date()
    :day(1), month(1),year(1900) { //Throw exception em vez deste fallback

}

Date::Date(int day, int month, int year) {
    setDate(day, month, year);
}

Date::Date(const Date& date) {
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
}

bool Date::isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

bool Date::isValid(int day, int month, int year) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    int maxDay;
    switch (month) {
        case 2:
            maxDay = isLeapYear(year) ? 29 : 28;
            break;
        case 4: case 6: case 9: case 11:
            maxDay = 30;
            break;
        default:
            maxDay = 31;
    }

    return day >= 1 && day <= maxDay;
}

void Date::setDate(int day, int month, int year) {
    if (isValid(day, month, year)) {
        this->day = day;
        this->month = month;
        this->year = year;
    } else {
        this->day = 1;
        this->month = 1;
        this->year = 2000;
    }
}

void Date::getDate(int& day, int& month, int& year) const {
    day = this->day;
    month = this->month;
    year = this->year;
}

bool Date::operator==(const Date& obj) const {
    return this->day == obj.day && this->month == obj.month && this->year == obj.year;
}

bool Date::operator>(const Date& obj) const {
    return obj < *this;
}

bool Date::operator<(const Date& obj) const {
    if (year != obj.year) return year < obj.year;
    if (month != obj.month) return month < obj.month;
    return day < obj.day;
}

bool Date::operator!=(const Date& obj) const {
    return !(*this == obj);
}

Date getTodayDate() {
    using namespace std::chrono;
    system_clock::time_point today = system_clock::now();
    time_t today_time = system_clock::to_time_t(today);
    tm* today_tm = localtime(&today_time);

    return Date(today_tm->tm_mday, today_tm->tm_mon + 1, today_tm->tm_year + 1900);
}

int Date::daysBetween(const Date& other) const
{
    time_t t1 = this->toTimeT();
    time_t t2 = other.toTimeT();

    return std::abs(
        static_cast<int>(
            (t1, t2) / (60 * 60 * 24)
        )
    );
}

