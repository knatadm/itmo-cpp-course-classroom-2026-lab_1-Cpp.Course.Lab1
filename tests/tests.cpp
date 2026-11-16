#include <catch2/catch_all.hpp>

#include "lab1/date.hpp"

using namespace lab1::date;

namespace
{

bool same_date(Date a, Date b)
{
    return a.year == b.year && a.month == b.month && a.day == b.day;
}

} // namespace

TEST_CASE("days_in_month", "[date]")
{
    REQUIRE(days_in_month(2023, 2) == 28);
    REQUIRE(days_in_month(2024, 2) == 29);
    REQUIRE(days_in_month(1900, 2) == 28);
    REQUIRE(days_in_month(2000, 2) == 29);
    REQUIRE(days_in_month(2024, 4) == 30);
    REQUIRE(days_in_month(2024, 1) == 31);
    REQUIRE(days_in_month(2024, 0) == 0);
    REQUIRE(days_in_month(2024, 13) == 0);
}

TEST_CASE("is_valid", "[date]")
{
    REQUIRE(is_valid(Date{2024, 2, 29}));
    REQUIRE(is_valid(Date{0, 1, 1}));
    REQUIRE(is_valid(Date{9999, 12, 31}));
    REQUIRE_FALSE(is_valid(Date{2023, 2, 29}));
    REQUIRE_FALSE(is_valid(Date{2024, 13, 1}));
    REQUIRE_FALSE(is_valid(Date{2024, 4, 31}));
    REQUIRE_FALSE(is_valid(Date{2024, 1, 0}));
    REQUIRE_FALSE(is_valid(Date{-1, 1, 1}));
    REQUIRE_FALSE(is_valid(Date{10000, 1, 1}));
}

TEST_CASE("day_of_week", "[date]")
{
    REQUIRE(day_of_week(Date{1970, 1, 1}) == 3);
    REQUIRE(day_of_week(Date{2024, 2, 29}) == 3);
    REQUIRE(day_of_week(Date{2000, 1, 1}) == 5);
    REQUIRE(day_of_week(Date{1969, 12, 31}) == 2);
    REQUIRE(day_of_week(Date{9999, 12, 31}) == 4);
    REQUIRE(day_of_week(Date{2023, 2, 29}) == -1);
}

TEST_CASE("days_between", "[date]")
{
    REQUIRE(days_between(Date{2020, 1, 1}, Date{2020, 1, 31}) == 30);
    REQUIRE(days_between(Date{2020, 1, 31}, Date{2020, 1, 1}) == -30);
    REQUIRE(days_between(Date{2020, 1, 1}, Date{2020, 1, 1}) == 0);
    REQUIRE(days_between(Date{2023, 12, 31}, Date{2024, 1, 1}) == 1);
    REQUIRE(days_between(Date{2024, 2, 28}, Date{2024, 3, 1}) == 2);
    REQUIRE(days_between(Date{2023, 2, 28}, Date{2023, 3, 1}) == 1);
    REQUIRE(days_between(Date{2023, 2, 29}, Date{2023, 3, 1}) == 0);
}

TEST_CASE("add_days", "[date]")
{
    REQUIRE(same_date(add_days(Date{2020, 3, 1}, -1), Date{2020, 2, 29}));
    REQUIRE(same_date(add_days(Date{2020, 2, 28}, 1), Date{2020, 2, 29}));
    REQUIRE(same_date(add_days(Date{2020, 12, 31}, 1), Date{2021, 1, 1}));
    REQUIRE(same_date(add_days(Date{2020, 1, 1}, 0), Date{2020, 1, 1}));
    REQUIRE(same_date(add_days(Date{2024, 1, 31}, 30), Date{2024, 3, 1}));
    REQUIRE(same_date(add_days(Date{2000, 1, 1}, 366), Date{2001, 1, 1}));
}

TEST_CASE("add_days out of range", "[date]")
{
    const Date invalid{0, 0, 0};
    REQUIRE(same_date(add_days(Date{9999, 12, 31}, 1), invalid));
    REQUIRE(same_date(add_days(Date{0, 1, 1}, -1), invalid));
    REQUIRE(same_date(add_days(Date{2023, 2, 29}, 1), invalid));
    REQUIRE(same_date(add_days(Date{9999, 12, 31}, 0), Date{9999, 12, 31}));
}
