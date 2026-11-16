#include "lab1/date.hpp"

namespace lab1::date
{

    namespace
    {

        bool is_leap(int year)
        {
            return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        }

        int days_in_year(int year)
        {
            return is_leap(year) ? 366 : 365;
        }

        long long to_days(Date d)
        {
            long long days = 0;
            for (int y = 0; y < d.year; ++y)
            {
                days += days_in_year(y);
            }
            for (int m = 1; m < d.month; ++m)
            {
                days += days_in_month(d.year, m);
            }
            days += d.day - 1;
            return days;
        }

        Date from_days(long long n)
        {
            int year = 0;
            while (n >= days_in_year(year))
            {
                n -= days_in_year(year);
                ++year;
            }

            int month = 1;
            while (n >= days_in_month(year, month))
            {
                n -= days_in_month(year, month);
                ++month;
            }

            return Date{year, month, static_cast<int>(n) + 1};
        }

    } // namespace

    int days_in_month(int year, int m)
    {
        if (m < 1 || m > 12)
        {
            return 0;
        }
        if (m == 2)
        {
            if (is_leap(year))
            {
                return 29;
            }
            return 28;
        }
        if (m == 4 || m == 6 || m == 9 || m == 11)
        {
            return 30;
        }
        return 31;
    }

    bool is_valid(Date d)
    {
        if (d.year < 0 || d.year > 9999)
        {
            return false;
        }
        if (d.month < 1 || d.month > 12)
        {
            return false;
        }
        return d.day >= 1 && d.day <= days_in_month(d.year, d.month);
    }

    int days_between(Date a, Date b)
    {
        if (!is_valid(a) || !is_valid(b))
        {
            return 0;
        }
        return static_cast<int>(to_days(b) - to_days(a));
    }

    int day_of_week(Date d)
    {
        if (!is_valid(d))
        {
            return -1;
        }
        const long long shift = to_days(d) - to_days(Date{1970, 1, 1});
        return static_cast<int>(((shift + 3) % 7 + 7) % 7);
    }

    Date add_days(Date d, int delta)
    {
        const Date invalid{0, 0, 0};
        if (!is_valid(d))
        {
            return invalid;
        }

        const long long total = to_days(d) + delta;
        const long long last = to_days(Date{9999, 12, 31});
        if (total < 0 || total > last)
        {
            return invalid;
        }

        return from_days(total);
    }

} // namespace lab1::date
