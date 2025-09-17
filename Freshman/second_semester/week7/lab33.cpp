#include <iostream>

template <typename T>
class Set
{
private:
    T element[100];
    int count;

public:
    Set() : count(0) {}

    Set(const Set<T> &set_2);

    bool check(const T data) const;

    int add(const T data);

    int add(const Set<T> &set_2);

    void display() const;

    Set &operator+(const Set<T> &set_2);

    Set &operator=(const Set<T> &set_2);

    Set &operator-(const Set<T> &set_2);
};

template <typename T>
bool Set<T>::check(const T data) const
{
    for (int i = 0; i < this->count; i++)
    {
        if (this->element[i] == data)
            return true;
    }
    return false;
}

template <typename T>
int Set<T>::add(const T data)
{
    if (check(data) || this->count == 100)
        return 0;

    this->element[count] = data;
    count++;

    return 1;
}

template <typename T>
Set<T>::Set(const Set<T> &set_2) : count(0)
{
    for (int i = 0; i < set_2.count; i++)
        this->add(set_2.element[i]);
}

template <typename T>
int Set<T>::add(const Set<T> &set_2)
{
    int added_count = false;
    for (int i = 0; i < set_2.count; i++)
        added_count += this->add(set_2.element[i]);

    return added_count;
}

template <typename T>
void Set<T>::display() const
{
    for (int i = 0; i < this->count; i++)
        std::cout << element[i] << " ";
}

template <typename T>
Set<T> &Set<T>::operator+(const Set<T> &set_2)
{
    Set<T> temp(*this);

    temp.add(set_2);

    return temp;
}

template <typename T>
Set<T> &Set<T>::operator=(const Set<T> &set_2)
{
    this->count = 0;
    while (this->count < set_2.count)
        this->add(set_2.element[count]);

    return *this;
}

template <typename T>
Set<T> &Set<T>::operator-(const Set<T> &set_2)
{
    Set<T> difference;

    int min_count = (this->count < set_2.count) ? this->count : set_2.count;

    for (int i = 0; i < min_count; ++i)
        if (set_2.check(element[i]))
            difference.add(element[i]);

    return difference;
}
