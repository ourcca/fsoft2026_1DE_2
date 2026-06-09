#include "gtest/gtest.h"

#include "model/Time.h"
#include "exceptions/InvalidDataException.h"

TEST(TimeConstructorTest, ValidTime) {
    Time time(14, 30);

    int hour;
    int minute;

    time.getTime(hour, minute);

    EXPECT_EQ(hour, 14);
    EXPECT_EQ(minute, 30);
}

TEST(TimeConstructorTest, InvalidHour) {
    EXPECT_THROW(Time(25, 30), InvalidDataException);
}

TEST(TimeConstructorTest, InvalidMinute) {
    EXPECT_THROW(Time(14, 70), InvalidDataException);
}

TEST(TimeOperatorTest, EqualTimes) {
    Time time1(14, 30);
    Time time2(14, 30);

    EXPECT_TRUE(time1 == time2);
}

TEST(TimeOperatorTest, DifferentTimes) {
    Time time1(14, 30);
    Time time2(15, 30);

    EXPECT_TRUE(time1 != time2);
}

TEST(TimeOperatorTest, LessThanTime) {
    Time time1(14, 30);
    Time time2(15, 30);

    EXPECT_TRUE(time1 < time2);
}

TEST(TimeOperatorTest, GreaterThanTime) {
    Time time1(16, 30);
    Time time2(15, 30);

    EXPECT_TRUE(time1 > time2);
}

TEST(TimeMinutesTest, MinutesSinceMidnight) {
    Time time(1, 30);

    EXPECT_EQ(time.minutesSinceMidnight(), 90);
}
