#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

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
public:
    Customer c;
    Node *next;
    friend class SLL;

public:
    Node(Customer c, Node *next = nullptr)
    {
        this->c = c;
        this->next = next;
    }
};

class SLL
{
public:
    Node *head;
    Node *tail;
    int count;

public:
    SLL();
    ~SLL();
    void add(Customer c);
    Customer removeAt(int index);
    bool empty();
    int size();
    void clear();
    Customer get(int index);
    int indexOf(Customer c);
    bool contains(Customer c);
    void print();
};

SLL::SLL()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

SLL::~SLL()
{
    clear();
}

void SLL::add(Customer e)
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
        tail = newNode;
    }
    count++;
}

Customer SLL::removeAt(int index)
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
            delete deleteNode;
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
                    delete deleteNode;
                    return data;
                }
                tmp = tmp->next;
            }
        }
        count--;
    }
}

bool SLL::empty()
{
    return count == 0;
}

int SLL::size()
{
    return count;
}

void SLL::clear()
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

Customer SLL::get(int index)
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

int SLL::indexOf(Customer c)
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

bool SLL::contains(Customer c)
{
    return indexOf(c) != -1;
}

void SLL::print()
{
    Node *tmp = head;
    while (tmp != nullptr)
    {
        cout << tmp->c << endl;
        tmp = tmp->next;
    }
    cout << endl
         << endl;
}

class Queue
{
private:
    SLL list;

public:
    Queue();
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
};

Queue::Queue()
{
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

class Stack
{
public:
    SLL list;

public:
    Stack();
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
};

Stack::Stack()
{
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
    list.removeAt(list.size() - 1);
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

int main()
{
    Customer c1(1, "John", 35);
    Customer c2(2, "Nam", 10);
    Customer c3(3, "Wick", 35);
    Customer c4(4, "Tuan", 20);
    Customer c5(5, "Eddie", 45);
    Customer c7(7, "Duck", 34);
    Customer c6(6, "Epsilon", 47);
    Stack s;
    s.push(c1);
    s.push(c2);
    s.push(c3);
    s.push(c4);
    s.push(c5);
    s.push(c7);
    s.push(c6);
    s.print();
    s.list.removeAt(4);
    cout << s.list.indexOf(c5) << endl
         << endl;
    s.print();
}