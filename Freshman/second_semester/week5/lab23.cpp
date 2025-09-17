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

class Time
{
private:
    std::string time;
    int hour, minute, second;

public:
    Time() : hour(0), minute(0), second(0) {}
    Time(std::string time);

    std::string toString() const { return time; };

    int operator-(const Time &other) const;
};

// Only this class will be uploaded to OJ
class DateTime : public Date, public Time
{
private:
    std::string date_time;

public:
    DateTime() : Date("1900/01/01"), Time("00:00:00") {}
    DateTime(std::string date_time);

    std::string toString() const { return date_time; };
};

DateTime::DateTime(std::string date_time)
{
    this->date_time = date_time;
}