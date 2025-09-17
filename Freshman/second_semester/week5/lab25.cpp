#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

struct Point
{
    int x, y;
};

int find_distance(const Point &p1, const Point &p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

Point find_meeting_point(int S, int A, const std::vector<Point> &FRIENDS)
{
    int min_total_distance = std::numeric_limits<int>::max();

    Point best_meeting_point;

    for (int i = 0; i < S; i++)
    {
        for (int j = 0; j < A; j++)
        {
            Point meeting_point = {i + 1, j + 1};

            int total_distance = 0;

            for (const auto &friend_loc : FRIENDS)
                total_distance += find_distance(friend_loc, meeting_point);

            if (total_distance < min_total_distance)
            {
                min_total_distance = total_distance;
                best_meeting_point = meeting_point;
            }
        }
    }

    return best_meeting_point;
}

int main(void)
{
    int T;
    std::cin >> T;

    while (T--)
    {
        int S, A, F;
        std::cin >> S >> A >> F;

        std::vector<Point> FRIENDS(F);

        for (Point &friend_loc : FRIENDS)
            std::cin >> friend_loc.x >> friend_loc.y;

        Point meeting_point = find_meeting_point(S, A, FRIENDS);

        std::cout << "(Street: " << meeting_point.x << ", Avenue: " << meeting_point.y << ")" << std::endl;
    }
}
