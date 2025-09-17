#include <iostream>
#include <cstring>

class Node
{
public:
    int data;
    Node *next;

    Node() : next(nullptr), data(0) {}
    Node(int d) : next(nullptr), data(d) {}
    Node(Node *n) : next(n), data(0) {}
    Node(Node *n, int d) : next(n), data(d) {}

    int &getData() { return data; };
    Node *&getNext() { return next; };

    friend std::ostream &operator<<(std::ostream &out, Node *n)
    {
        out << n->getData();
        return out;
    };
};

class LinkedList : public Node
{
protected:
    Node *head;

public:
    LinkedList() : head(nullptr){};

    ~LinkedList();

    Node *&getHead() { return head; };

    bool addFromHead(int d);

    bool addFromTail(int d);

    bool removeFromHead();

    bool removeFromTail();

    friend std::ostream &operator<<(std::ostream &out, LinkedList *l);

    int getSize() const;
};

LinkedList::~LinkedList()
{
    if (head != nullptr)
    {
        Node *_next = head;
        while (_next->next != nullptr)
        {
            head = _next->next;
            delete _next;

            _next = head;
        }

        delete head;
    }
};

bool LinkedList::addFromHead(int d)
{
    Node *new_node = new Node(d);
    new_node->next = head;

    head = new_node;

    return true;
};

bool LinkedList::addFromTail(int d)
{
    Node *new_node = new Node(d);
    if (head == nullptr)
    {
        head = new_node;
        return true;
    }

    Node *_next = head;
    while (_next->next != nullptr)
        _next = _next->next;

    _next->next = new_node;

    return true;
};

bool LinkedList::removeFromHead()
{
    if (head == nullptr)
        return false;

    Node *node_to_remove = head;
    head = head->next;

    delete node_to_remove;

    return true;
};

bool LinkedList::removeFromTail()
{
    if (head == nullptr)
        return false;

    if (head->next == nullptr)
    {
        delete head;

        head = nullptr;

        return true;
    }

    Node *_next = head;
    while (_next->next->next != nullptr)
        _next = _next->next;

    delete _next->next;
    _next->next = nullptr;

    return true;
};

std::ostream &operator<<(std::ostream &out, LinkedList *list)
{
    out << "{";
    if (list->getHead() != nullptr)
    {
        Node *_next = list->getHead();
        while (_next->next != nullptr)
        {
            out << _next << ", ";
            _next = _next->next;
        }
        out << _next;
    }

    out << "}" << std::endl;

    return out;
};

int LinkedList::getSize() const
{
    int size = 0;
    if (head == nullptr)
        return size;

    Node *_next = head;
    while (_next->next != nullptr)
    {
        _next = _next->next;
        size++;
    }

    return ++size;
};