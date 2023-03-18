#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "main.h"

using namespace std;

struct Customer
{
    int ID;
    string name;
    int age;
    Customer(int ID = -1, string name = "", int age = 0)
    {
        this->ID = ID;
        this->age = age;
        this->name = name;
    }

    bool operator==(const Customer &other) const
    {
        return ID == other.ID && name == other.name && age == other.age;
    }
};

ostream &operator<<(ostream &os, const Customer &customer)
{
    os << "ID: " << customer.ID << ", Name: " << customer.name << ", Age: " << customer.age;
    return os;
}

class Node
{
private:
    Customer c;
    Node *prev;
    Node *next;
    friend class DLL;

public:
    Node(Customer c, Node *prev = nullptr, Node *next = nullptr)
    {
        this->c = c;
        this->prev = prev;
        this->next = next;
    }
};

class DLL
{
protected:
    Node *head;
    Node *tail;
    int count;

public:
    DLL();
    ~DLL();
    void add(Customer c);
    void addHead(Customer c);
    Customer removeAt(int index);
    bool empty();
    int size();
    void clear();
    Customer get(int index);
    int indexOf(Customer c);
    bool contains(Customer c);
    void print();
    void print_reverse();
};

DLL::DLL()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

DLL::~DLL()
{
    clear();
}

void DLL::add(Customer e)
{
    Node *newNode = new Node(e);
    if (head == nullptr && tail == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

void DLL::addHead(Customer e)
{
    Node *newNode = new Node(e);
    if (head == nullptr && tail == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    count++;
}

Customer DLL::removeAt(int index)
{
    if (index < 0 || index > count - 1)
    {
        Customer none_customer;
        return none_customer;
    }
    else
    {
        if (index == 0)
        {
            Node *deleteNode = head;
            Customer data = deleteNode->c;
            head = head->next;
            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }
            delete deleteNode;
            count--;
            return data;
        }
        else if (index == count - 1)
        {
            Node *deleteNode = tail;
            Customer data = deleteNode->c;
            tail = tail->prev;
            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }
            delete deleteNode;
            count--;
            return data;
        }
        else
        {
            Node *tmp = head;
            for (int i = 0; i < count; i++)
            {
                if (i == index - 1)
                {
                    Node *deleteNode = tmp->next;
                    Customer data = deleteNode->c;
                    tmp->next = deleteNode->next;
                    deleteNode->next->prev = tmp;
                    delete deleteNode;
                    count--;
                    return data;
                }
                tmp = tmp->next;
            }
        }
    }
}

bool DLL::empty()
{
    return count == 0;
}

int DLL::size()
{
    return count;
}

void DLL::clear()
{
    while (head != nullptr)
    {
        Node *deleteNode = head;
        head = head->next;
        delete deleteNode;
    }
    count = 0;
    tail = nullptr;
}

Customer DLL::get(int index)
{
    if (index < 0 || index > count - 1)
    {
        Customer none_customer;
        return none_customer;
    }
    else
    {
        Node *tmp = head;
        for (int i = 0; i < count; i++)
        {
            if (i == index)
            {
                return tmp->c;
            }
        }
        Customer none_customer;
        return none_customer;
    }
}

int DLL::indexOf(Customer c)
{
    Node *tmp = head;
    int count = 0;
    while (tmp != nullptr)
    {
        if (tmp->c == c)
        {
            return count;
        }
        tmp = tmp->next;
        count++;
    }
    return -1;
}

bool DLL::contains(Customer c)
{
    return indexOf(c) != -1;
}

void DLL::print()
{
    Node *tmp = head;
    while (tmp != nullptr)
    {
        cout << tmp->c.name << endl;
        tmp = tmp->next;
    }
}

void DLL::print_reverse()
{
    if (head == nullptr && tail == nullptr)
    {
        return;
    }
    Node *tmp = tail;
    while (tmp != nullptr)
    {
        cout << tmp->c.name << endl;
        tmp = tmp->prev;
    }
}

class Queue
{
private:
    DLL list;

public:
    Queue();
    Queue(const Queue &other);
    ~Queue();
    void push(Customer item);
    Customer popFront();
    Customer popBack();
    const Customer &peek();
    bool empty();
    int size();
    void clear();
    bool remove(Customer item);
    bool contains(Customer item);
    void print();
    void print_reverse();
};

Queue::Queue()
{
}

Queue::Queue(const Queue &other)
{
    list = other.list;
}

Queue::~Queue()
{
    list.clear();
}

void Queue::push(Customer item)
{
    list.add(item);
}

Customer Queue::popFront()
{
    return list.removeAt(0);
}

Customer Queue::popBack()
{
    return list.removeAt(list.size() - 1);
}

const Customer &Queue::peek()
{
    return list.get(0);
}

bool Queue::empty()
{
    return list.empty();
}

int Queue::size()
{
    return list.size();
}

void Queue::clear()
{
    list.clear();
}

bool Queue::remove(Customer item)
{
    if (!list.contains(item))
    {
        return false;
    }
    else
    {
        return (list.removeAt(list.indexOf(item)).ID != -1);
    }
}

bool Queue::contains(Customer item)
{
    return list.contains(item);
}

void Queue::print()
{
    list.print();
}

void Queue::print_reverse()
{
    list.print_reverse();
}

class Stack
{
private:
    DLL list;

public:
    Stack();
    Stack(const Stack &other);
    ~Stack();
    void push(Customer item);
    Customer pop();
    const Customer &peek();
    bool empty();
    int size();
    void clear();
    bool remove(Customer item);
    bool contains(Customer item);
    void print();
    void print_reverse();
};

Stack::Stack()
{
}

Stack::Stack(const Stack &other)
{
    list = other.list;
}

Stack::~Stack()
{
    list.clear();
}

void Stack::push(Customer item)
{
    list.add(item);
}

Customer Stack::pop()
{
    return list.removeAt(list.size() - 1);
}

const Customer &Stack::peek()
{
    return list.get(list.size() - 1);
}

bool Stack::empty()
{
    return list.empty();
}

int Stack::size()
{
    return list.size();
}

void Stack::clear()
{
    list.clear();
}

bool Stack::remove(Customer item)
{
    if (!list.contains(item))
    {
        return false;
    }
    else
    {
        return (list.removeAt(list.indexOf(item)).ID != -1);
    }
}

bool Stack::contains(Customer item)
{
    return list.contains(item);
}

void Stack::print()
{
    list.print();
}

void Stack::print_reverse()
{
    list.print_reverse();
}