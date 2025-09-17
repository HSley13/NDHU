#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

int judge(Container *c)
{
    PriorityQueue *ptr = dynamic_cast<PriorityQueue *>(c);
    return (ptr != nullptr) + 1;
}