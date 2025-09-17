#include <iostream>
#include <cstring>

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

Time::Time(std::string time)
{
    this->time = time;

    hour = std::stoi(std::strtok(&time[0], ":"));

    minute = std::stoi(std::strtok(nullptr, ":"));

    second = std::stoi(std::strtok(nullptr, ":"));
}

int Time::operator-(const Time &other) const
{
    return abs((this->hour * 3600 + this->minute * 60 + this->second) - (other.hour * 3600 + other.minute * 60 + other.second));
}
