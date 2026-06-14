#include "gtest/gtest.h"

#include "model/Time.h"
#include "exceptions/InvalidDataException.h"

TEST(TimeConstructorTest, DefaultTimeIsMidnight) {
    Time time;

    int hour;
    int minute;

    time.getTime(hour, minute);

    EXPECT_EQ(hour, 0);
    EXPECT_EQ(minute, 0);
}

TEST(TimeConstructorTest, ValidTime) {
    Time time(14, 30);

    int hour;
    int minute;

    time.getTime(hour, minute);

    EXPECT_EQ(hour, 14);
    EXPECT_EQ(minute, 30);
}

TEST(TimeConstructorTest, MidnightIsValid) {
    Time time(0, 0);

    int hour;
    int minute;

    time.getTime(hour, minute);

    EXPECT_EQ(hour, 0);
    EXPECT_EQ(minute, 0);
}

TEST(TimeConstructorTest, LastMinuteOfDayIsValid) {
    Time time(23, 59);

    int hour;
    int minute;

    time.getTime(hour, minute);

    EXPECT_EQ(hour, 23);
    EXPECT_EQ(minute, 59);
}

TEST(TimeConstructorTest, InvalidNegativeHourThrowsException) {
    EXPECT_THROW(Time(-1, 30), InvalidDataException);
}

TEST(TimeConstructorTest, InvalidHourThrowsException) {
    EXPECT_THROW(Time(25, 30), InvalidDataException);
}

TEST(TimeConstructorTest, TwentyFourZeroZeroIsInvalid) {
    EXPECT_THROW(Time(24, 0), InvalidDataException);
}

TEST(TimeConstructorTest, InvalidNegativeMinuteThrowsException) {
    EXPECT_THROW(Time(14, -1), InvalidDataException);
}

TEST(TimeConstructorTest, InvalidMinuteThrowsException) {
    EXPECT_THROW(Time(14, 70), InvalidDataException);
}

TEST(TimeSetterTest, SetValidTimeUpdatesTime) {
    Time time;

    time.setTime(16, 45);

    int hour;
    int minute;

    time.getTime(hour, minute);

    EXPECT_EQ(hour, 16);
    EXPECT_EQ(minute, 45);
}

TEST(TimeSetterTest, SetInvalidTimeThrowsExceptionAndKeepsOldTime) {
    Time time(14, 30);

    EXPECT_THROW(time.setTime(25, 0), InvalidDataException);

    int hour;
    int minute;

    time.getTime(hour, minute);

    EXPECT_EQ(hour, 14);
    EXPECT_EQ(minute, 30);
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

TEST(TimeMinutesTest, MidnightHasZeroMinutesSinceMidnight) {
    Time time(0, 0);

    EXPECT_EQ(time.minutesSinceMidnight(), 0);
}

TEST(TimeMinutesTest, LastMinuteOfDayHasCorrectMinutesSinceMidnight) {
    Time time(23, 59);

    EXPECT_EQ(time.minutesSinceMidnight(), 1439);
}