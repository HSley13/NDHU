#include <iostream>
#include <set>
#include <sstream>
#include <vector>

class date_range {
  public:
    int start;
    int end;

    date_range(int start, int end) : start(start), end(end) {}

    static bool is_leap_year(int year) { return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)); }

    static int count_days(int date);

    static std::string days_to_date(int days);
};

int date_range::count_days(int date) {
    int year = date / 10000;
    int month = (date % 10000) / 100;
    int day = date % 100;

    int days = day;

    static const int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int i = 1; i < month; i++) {
        days += days_in_month[i];

        if (i == 2 && is_leap_year(year))
            days++;
    }

    for (int i = 1700; i < year; i++)
        days += 365 + is_leap_year(i);

    return days;
}

std::string date_range::days_to_date(int days) {
    int year = 1700;
    while (days > 365 + is_leap_year(year)) {
        days -= 365 + is_leap_year(year);
        year++;
    }

    static const int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int month = 1;
    while (days > days_in_month[month] + (month == 2 && is_leap_year(year))) {
        days -= days_in_month[month] + (month == 2 && is_leap_year(year));
        month++;
    }

    int day = days;

    std::stringstream date;
    date << month << '/' << day << '/' << year;
    return date.str();
}

class quote_manager {
  private:
    std::vector<date_range> existing_ranges;
    std::vector<date_range> requested_ranges;
    std::set<int> new_dates;
    std::vector<date_range> new_ranges;

  public:
    void add_existing_range(int start, int end) { existing_ranges.emplace_back(date_range::count_days(start), date_range::count_days(end)); }

    void add_requested_range(int start, int end) { requested_ranges.emplace_back(date_range::count_days(start), date_range::count_days(end)); }

    void find_new_ranges();

    void merge_new_ranges();

    void print_new_ranges(int case_number);
};

void quote_manager::find_new_ranges() {
    std::set<int> covered_dates;

    for (const date_range &range : existing_ranges) {
        for (int day = range.start; day <= range.end; day++)
            covered_dates.insert(day);
    }

    for (const date_range &range : requested_ranges) {
        for (int day = range.start; day <= range.end; day++) {
            if (covered_dates.find(day) == covered_dates.end())
                new_dates.insert(day);
        }
    }

    merge_new_ranges();
}

void quote_manager::merge_new_ranges() {
    if (new_dates.empty())
        return;

    std::set<int>::iterator it = new_dates.begin();

    int start = *it;
    int end = *it;

    for (++it; it != new_dates.end(); ++it) {
        if (*it == end + 1)
            end = *it;
        else {
            new_ranges.emplace_back(start, end);
            start = *it;
            end = *it;
        }
    }

    new_ranges.emplace_back(start, end);
}

void quote_manager::print_new_ranges(int case_number) {
    std::cout << "Case " << case_number << ":\n";

    if (new_ranges.empty())
        std::cout << "No additional quotes are required.\n";

    else {
        for (const date_range &range : new_ranges) {
            if (range.start == range.end)
                std::cout << date_range::days_to_date(range.start) << '\n';
            else
                std::cout << date_range::days_to_date(range.start) << " to " << date_range::days_to_date(range.end) << '\n';
        }
    }
}

int main(void) {
    int NX, NR;
    int case_number = 0;
    while (std::cin >> NX >> NR, NX || NR) {
        quote_manager manager;

        for (int i = 0; i < NX; i++) {
            int start, end;
            std::cin >> start >> end;

            manager.add_existing_range(start, end);
        }

        for (int i = 0; i < NR; i++) {
            int start, end;
            std::cin >> start >> end;

            manager.add_requested_range(start, end);
        }

        manager.find_new_ranges();
        manager.print_new_ranges(++case_number);
    }
}
