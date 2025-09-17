#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

class Node
{
    int data;
    Node *next;

public:
    Node() : data(0), next(nullptr){};
    Node(int _data) : data(_data), next(nullptr){};
    int getData() { return data; };
    void setData(int _data) { data = _data; };

    Node *&getNext() { return next; };
    void setNext(Node *node) { next = node; };
};

class Stack : public Container
{
private:
    Node *head;

public:
    Stack() : head(nullptr){};
    ~Stack()
    {
        while (!empty())
            pop();
    };

    virtual void push(int data) override;

    virtual void pop() override;

    virtual int top() const override;

    virtual bool empty() const override { return (head == nullptr); };

    virtual Node *getTop() const { return head; };

    void setHead(Node *newHead) { head = newHead; };
};

void Stack::push(int data)
{
    Node *newNode = new Node(data);
    if (empty())
        head = newNode;

    else
    {
        newNode->setNext(head);
        head = newNode;
    }
};

void Stack::pop()
{
    if (empty())
        throw std::out_of_range("List empty");

    Node *temp = head;
    head = head->getNext();
    delete temp;
};

int Stack::top() const
{
    if (empty())
        throw std::out_of_range("List empty");

    return head->getData();
};

class PriorityQueue : public Stack
{
public:
    PriorityQueue() : Stack(){};

    virtual void push(int data) override;
};

void push(int data)
{
    Node *head = getTop();
    Node *newNode = new Node(data);
    if (empty())
        setHead(newNode);

    else if (head->getNext() == nullptr)
    {
        if (data < head->getData())
            head->setNext(newNode);
        else
        {
            newNode->setNext(head);
            setHead(newNode);
        }
    }
    else
    {
        Node *temp = head;
        if (data > head->getData())
        {
            newNode->setNext(head);
            setHead(newNode);
        }
        else
        {
            while (temp->getNext() != nullptr)
            {
                if (temp->getNext()->getData() < data)
                    break;
                temp = temp->getNext();
            };

            newNode->setNext(temp->getNext());
            temp->setNext(newNode);
        }
    }
};
