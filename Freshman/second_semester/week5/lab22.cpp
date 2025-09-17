#include <iostream>
#include <cstring>

class Date
{
private:
    std::string date;
    int year, month, day;

public:
    Date() : year(1900), month(1), day(1) {}
    Date(std::string Date);

    std::string toString() const { return date; };

    int operator-(const Date &other) const;

    int count_days(const Date &date) const;
};

Date::Date(std::string date)
{
    this->date = date;

    year = std::stoi(std::strtok(&date[0], "/"));

    month = std::stoi(std::strtok(nullptr, "/"));

    day = std::stoi(std::strtok(nullptr, "/"));
}

bool leap_year(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return true;
    else
        return false;
}

int Date::count_days(const Date &date) const
{
    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int count = date.day;

    for (int i = 1; i < date.month; i++)
    {
        count += days_in_month[i];

        if (i == 2 && leap_year(date.year))
            count++;
    }

    count += (date.year - 1900) * 365;

    for (int i = 1900; i < date.year; i++)
    {
        if (leap_year(i))
            count++;
    }

    return count;
}

int Date::operator-(const Date &other) const
{
    return abs(this->count_days(*this) - other.count_days(other));
}
