#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>

#include "lab1/date.hpp"

bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

int read_number(const std::string &text, std::size_t begin, std::size_t count)
{
    int value = 0;
    for (std::size_t i = begin; i < begin + count; ++i)
    {
        value = value * 10 + (text[i] - '0');
    }
    return value;
}

bool parse_date(const std::string &text, lab1::date::Date &out)
{
    if (text.length() != 10)
    {
        return false;
    }
    if (text[4] != '-' || text[7] != '-')
    {
        return false;
    }
    for (std::size_t i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
        {
            continue;
        }
        if (!is_digit(text[i]))
        {
            return false;
        }
    }

    out.year = read_number(text, 0, 4);
    out.month = read_number(text, 5, 2);
    out.day = read_number(text, 8, 2);
    return true;
}

bool parse_int(const std::string &text, int &out)
{
    const std::size_t length = text.length();
    std::size_t start = 0;
    bool negative = false;

    if (length > 0 && text[0] == '-')
    {
        negative = true;
        start = 1;
    }
    if (start == length || length - start > 9)
    {
        return false;
    }
    for (std::size_t i = start; i < length; ++i)
    {
        if (!is_digit(text[i]))
        {
            return false;
        }
    }

    const int value = read_number(text, start, length - start);
    out = negative ? -value : value;
    return true;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Command is missing\n";
        return 2;
    }

    std::string command = argv[1];

    if (command == "validate" && argc == 3)
    {
        lab1::date::Date d;
        if (!parse_date(argv[2], d) || !lab1::date::is_valid(d))
        {
            std::cout << "INVALID\n";
            return 1;
        }
        std::cout << "OK\n";
        return 0;
    }
    if (command == "weekday" && argc == 3)
    {
        lab1::date::Date d;
        if (!parse_date(argv[2], d) || !lab1::date::is_valid(d))
        {
            std::cout << "INVALID\n";
            return 1;
        }

        const char *names[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
        std::cout << names[lab1::date::day_of_week(d)] << "\n";
        return 0;
    }
    if (command == "add" && argc == 4)
    {
        lab1::date::Date d;
        int delta = 0;
        if (!parse_date(argv[2], d) || !lab1::date::is_valid(d) ||
            !parse_int(argv[3], delta))
        {
            std::cout << "INVALID\n";
            return 1;
        }

        const lab1::date::Date result = lab1::date::add_days(d, delta);
        if (!lab1::date::is_valid(result))
        {
            std::cout << "INVALID\n";
            return 1;
        }

        std::cout << std::setfill('0') << std::setw(4) << result.year << '-'
                  << std::setw(2) << result.month << '-'
                  << std::setw(2) << result.day << "\n";
        return 0;
    }
    if (command == "diff" && argc == 4)
    {
        lab1::date::Date a;
        lab1::date::Date b;
        if (!parse_date(argv[2], a) || !lab1::date::is_valid(a) ||
            !parse_date(argv[3], b) || !lab1::date::is_valid(b))
        {
            std::cout << "INVALID\n";
            return 1;
        }

        std::cout << lab1::date::days_between(a, b) << "\n";
        return 0;
    }
     std::cerr << "Unknown command or wrong number of arguments\n";
    return 2;
}
