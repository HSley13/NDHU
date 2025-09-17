#include <iostream>

template <class T>
class LinkedList {
  private:
    void clear();
    void copyFrom(const LinkedList &other);

  public:
    class Node {
      public:
        Node() : next(nullptr) {}
        Node(T d) : next(nullptr), data(d) {}
        Node(Node *n) : next(n) {}
        Node(Node *n, T d) : next(n), data(d) {}

        T data;
        Node *next;
    };

    LinkedList() : head(nullptr) {}
    ~LinkedList();
    LinkedList(const LinkedList &other);
    LinkedList(LinkedList &&other) noexcept;

    LinkedList &operator=(const LinkedList &other);
    LinkedList &operator=(LinkedList &&other) noexcept;
    T operator[](int i) const;

    bool addFromHead(T d);
    bool addFromTail(T d);

    bool removeFromHead();
    bool removeFromTail();

    int getSize() const;
    bool searchData(T d) const;

    friend ostream &operator<<(ostream &o, const LinkedList &l) {
        Node *current = l.head;

        o << "{";
        while (current) {
            o << current->data;
            if (current->next)
                o << ", ";
            current = current->next;
        }
        o << "}";

        return o;
    }

  protected:
    Node *head;
};

template <class T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <class T>
void LinkedList<T>::clear() {
    while (head) {
        Node *temp = head;
        head = head->next;

        delete temp;
    }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList &other) : head(nullptr) {
    copyFrom(other);
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList &other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }

    return *this;
}

template <class T>
LinkedList<T>::LinkedList(LinkedList &&other) noexcept : head(other.head) {
    other.head = nullptr;
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList &&other) noexcept {
    if (this != &other) {
        clear();

        head = other.head;

        other.head = nullptr;
    }

    return *this;
}

template <class T>
void LinkedList<T>::copyFrom(const LinkedList &other) {
    if (!other.head)
        return;

    head = new Node(other.head->data);

    Node *current = head;
    Node *otherCurrent = other.head->next;

    while (otherCurrent) {
        current->next = new Node(otherCurrent->data);

        current = current->next;
        otherCurrent = otherCurrent->next;
    }
}

template <class T>
bool LinkedList<T>::addFromHead(T d) {
    if (!head)
        head = new Node(d);
    else
        head = new Node(head, d);

    return true;
}

template <class T>
bool LinkedList<T>::addFromTail(T d) {
    if (!head)
        head = new Node(d);
    else {
        Node *current = head;

        while (current->next)
            current = current->next;

        current->next = new Node(d);
    }

    return true;
}

template <class T>
bool LinkedList<T>::removeFromHead() {
    if (!head)
        return false;

    Node *temp = head;
    head = head->next;

    delete temp;

    return true;
}

template <class T>
bool LinkedList<T>::removeFromTail() {
    if (!head)
        return false;

    if (!head->next) {
        delete head;

        head = nullptr;

        return true;
    }

    Node *current = head;

    while (current->next->next)
        current = current->next;

    delete current->next;

    current->next = nullptr;

    return true;
}

template <class T>
int LinkedList<T>::getSize() const {
    int size = 0;
    Node *current = head;

    while (current) {
        size++;
        current = current->next;
    }

    return size;
}

template <class T>
bool LinkedList<T>::searchData(T d) const {
    Node *current = head;
    while (current) {
        if (current->data == d)
            return true;

        current = current->next;
    }

    return false;
}

template <class T>
T LinkedList<T>::operator[](int i) const {
    Node *current = head;
    int count = 0;

    while (current) {
        if (count == i)
            return current->data;

        count++;
        current = current->next;
    }

    throw out_of_range("Index out of range");
}

template <class T>
class Set : private LinkedList<T> {
  public:
    Set() : LinkedList<T>() {}

    bool addElement(T d);

    Set<T> *operator+(Set<T> *s);

    Set<T> *operator-(Set<T> *s);

    Set<T> *operator*(Set<T> *s);

    friend ostream &operator<<(ostream &o, Set<T> *s) {
        typename LinkedList<T>::Node *current = s->head;

        bool first = true;

        o << "{";
        while (current) {
            if (!first)
                o << ", ";
            o << current->data;
            current = current->next;

            first = false;
        }
        o << "}\n";

        return o;
    }

    bool operator==(Set<T> *s);

    bool operator>(Set<T> *s);

    bool operator<(Set<T> *s);

    bool operator>=(Set<T> *s) { return (this > s || this == s); }

    bool operator<=(Set<T> *s) { return (this < s || this == s); }
};

template <class T>
bool Set<T>::addElement(T d) {
    if (this->searchData(d))
        return false;

    this->addFromTail(d);
    return true;
}

template <class T>
Set<T> *Set<T>::operator+(Set<T> *s) {
    Set<T> *result = new Set<T>();
    typename LinkedList<T>::Node *current = this->head;

    while (current) {
        result->addElement(current->data);
        current = current->next;
    }

    current = s->head;

    while (current) {
        result->addElement(current->data);
        current = current->next;
    }

    return result;
}

template <class T>
Set<T> *Set<T>::operator-(Set<T> *s) {
    Set<T> *result = new Set<T>();
    typename LinkedList<T>::Node *current = this->head;

    while (current) {
        if (!s->searchData(current->data))
            result->addElement(current->data);

        current = current->next;
    }

    return result;
}

template <class T>
Set<T> *Set<T>::operator*(Set<T> *s) {
    Set<T> *result = new Set<T>();
    typename LinkedList<T>::Node *current = this->head;

    while (current) {
        if (s->searchData(current->data))
            result->addElement(current->data);

        current = current->next;
    }

    return result;
}

template <class T>
bool Set<T>::operator==(Set<T> *s) {
    if (this->getSize() != s->getSize())
        return false;

    typename LinkedList<T>::Node *current = this->head;

    while (current) {
        if (!s->searchData(current->data))
            return false;

        current = current->next;
    }

    return true;
}

template <class T>
bool Set<T>::operator>(Set<T> *s) {
    if (this->getSize() <= s->getSize())
        return false;

    typename LinkedList<T>::Node *current = s->head;

    while (current) {
        if (!this->searchData(current->data))
            return false;

        current = current->next;
    }

    return true;
}

template <class T>
bool Set<T>::operator<(Set<T> *s) {
    if (this->getSize() >= s->getSize())
        return false;

    typename LinkedList<T>::Node *current = this->head;

    while (current) {
        if (!s->searchData(current->data))
            return false;

        current = current->next;
    }

    return true;
}
