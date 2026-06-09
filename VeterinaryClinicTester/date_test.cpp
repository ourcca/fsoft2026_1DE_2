#include "gtest/gtest.h"

#include "model/Date.h"
#include "exceptions/InvalidDataException.h"

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

TEST(DateConstructorTest, InvalidDate) {
    EXPECT_THROW(Date(31, 2, 2026), InvalidDataException);
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