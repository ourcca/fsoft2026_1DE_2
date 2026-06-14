#include "gtest/gtest.h"

#include "model/Date.h"
#include "exceptions/InvalidDataException.h"

TEST(DateConstructorTest, DefaultDateIsValid) {
    Date date;

    int day;
    int month;
    int year;

    date.getDate(day, month, year);

    EXPECT_EQ(day, 1);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(year, 1900);
}

TEST(DateConstructorTest, ValidDate) {
    Date date(20, 5, 2026);

    int day;
    int month;
    int year;

    date.getDate(day, month, year);

    EXPECT_EQ(day, 20);
    EXPECT_EQ(month, 5);
    EXPECT_EQ(year, 2026);
}

TEST(DateConstructorTest, ValidLeapYearDate) {
    Date date(29, 2, 2024);

    int day;
    int month;
    int year;

    date.getDate(day, month, year);

    EXPECT_EQ(day, 29);
    EXPECT_EQ(month, 2);
    EXPECT_EQ(year, 2024);
}

TEST(DateConstructorTest, InvalidFebruaryDateThrowsException) {
    EXPECT_THROW(Date(31, 2, 2026), InvalidDataException);
}

TEST(DateConstructorTest, InvalidLeapYearDateThrowsException) {
    EXPECT_THROW(Date(29, 2, 2026), InvalidDataException);
}

TEST(DateConstructorTest, InvalidDayZeroThrowsException) {
    EXPECT_THROW(Date(0, 5, 2026), InvalidDataException);
}

TEST(DateConstructorTest, InvalidMonthZeroThrowsException) {
    EXPECT_THROW(Date(20, 0, 2026), InvalidDataException);
}

TEST(DateConstructorTest, InvalidMonthThirteenThrowsException) {
    EXPECT_THROW(Date(20, 13, 2026), InvalidDataException);
}

TEST(DateConstructorTest, InvalidYearTooLowThrowsException) {
    EXPECT_THROW(Date(20, 5, 1899), InvalidDataException);
}

TEST(DateConstructorTest, InvalidYearTooHighThrowsException) {
    EXPECT_THROW(Date(20, 5, 2101), InvalidDataException);
}

TEST(DateSetterTest, SetValidDateUpdatesDate) {
    Date date;

    date.setDate(25, 12, 2026);

    int day;
    int month;
    int year;

    date.getDate(day, month, year);

    EXPECT_EQ(day, 25);
    EXPECT_EQ(month, 12);
    EXPECT_EQ(year, 2026);
}

TEST(DateSetterTest, SetInvalidDateThrowsExceptionAndKeepsOldDate) {
    Date date(20, 5, 2026);

    EXPECT_THROW(date.setDate(31, 2, 2026), InvalidDataException);

    int day;
    int month;
    int year;

    date.getDate(day, month, year);

    EXPECT_EQ(day, 20);
    EXPECT_EQ(month, 5);
    EXPECT_EQ(year, 2026);
}

TEST(DateOperatorTest, EqualDates) {
    Date date1(20, 5, 2026);
    Date date2(20, 5, 2026);

    EXPECT_TRUE(date1 == date2);
}

TEST(DateOperatorTest, DifferentDates) {
    Date date1(20, 5, 2026);
    Date date2(21, 5, 2026);

    EXPECT_TRUE(date1 != date2);
}

TEST(DateOperatorTest, LessThanDate) {
    Date date1(20, 5, 2026);
    Date date2(21, 5, 2026);

    EXPECT_TRUE(date1 < date2);
}

TEST(DateOperatorTest, GreaterThanDate) {
    Date date1(22, 5, 2026);
    Date date2(21, 5, 2026);

    EXPECT_TRUE(date1 > date2);
}

TEST(DateOperatorTest, LessThanUsesMonthAndYear) {
    Date date1(31, 12, 2025);
    Date date2(1, 1, 2026);

    EXPECT_TRUE(date1 < date2);
}

TEST(DateDaysBetweenTest, CalculatesAbsoluteDifferenceInDays) {
    Date date1(1, 1, 2026);
    Date date2(11, 1, 2026);

    EXPECT_EQ(date1.daysBetween(date2), 10);
    EXPECT_EQ(date2.daysBetween(date1), 10);
}

TEST(DateDaysBetweenTest, SameDateReturnsZeroDays) {
    Date date1(20, 5, 2026);
    Date date2(20, 5, 2026);

    EXPECT_EQ(date1.daysBetween(date2), 0);
}

TEST(DateTodayTest, GetTodayDateReturnsValidDate) {
    Date today = getTodayDate();

    int day;
    int month;
    int year;

    today.getDate(day, month, year);

    EXPECT_NO_THROW(Date(day, month, year));
    EXPECT_GE(year, 1900);
    EXPECT_LE(year, 2100);
}