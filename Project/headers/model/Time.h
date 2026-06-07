//
// Created by rodri on 07/06/2026.
//

#ifndef VETERINARYCLINIC_MODEL_TIME_H
#define VETERINARYCLINIC_MODEL_TIME_H

class Time {
private:
    int hour{};
    int minute{};

    static bool isValid(int hour, int minute);

public:
    Time();
    Time(int hour, int minute);

    void setTime(int hour, int minute);
    void getTime(int& hour, int& minute) const;

    bool operator==(const Time& obj) const;
    bool operator<(const Time& obj) const;
    bool operator>(const Time& obj) const;
    bool operator!=(const Time& obj) const;

    int minutesSinceMidnight() const;
};

#endif