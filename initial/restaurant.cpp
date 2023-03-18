#include "main.h"

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

    Customer &operator=(const Customer &other)
    {
        if (this != &other)
        {
            ID = other.ID;
            name = other.name;
            age = other.age;
        }
        return *this;
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
            Customer none_customer;
            return none_customer;
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
            tmp = tmp->next;
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
    Customer get(int index);
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
    Customer *p = new Customer(list.get(0));
    return *p;
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

Customer Queue::get(int index)
{
    return list.get(index);
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
    Customer get(int index);
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
    Customer *p = new Customer(list.get(list.size() - 1));
    return *p;
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

Customer Stack::get(int index)
{
    return list.get(index);
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

Queue q; // Hang cho
Stack s; // Danh sach khach trong nha hang
table *recent_table_serve = nullptr;
table *merge_table_list = nullptr;
// bool has_merge_table = false;
int start_merge_table = -1;
int end_merge_table = -1;
bool has_found_table = false;

int SIZE(restaurant *r)
{
    int count = 0;
    table *first_table = r->recentTable;
    table *temp_table = r->recentTable;
    do
    {
        if (temp_table->name != "")
        {
            count++;
        }
        temp_table = temp_table->next;
    } while (temp_table != first_table);

    return count;
}

void MOD(table *t, string name, int age, int id = -1)
{
    if (age < 16)
        return;
    Customer c(id, name, age);
    int count = t->ID;
    if (id != -1)
    {
        while (count != id)
        {
            t = t->next;
            count = t->ID;
        }
    }
    else
    {
        while (count != 1)
        {
            t = t->next;
            count = t->ID;
        }
    }
    if (t->name != "")
    {
        while (t->name != "")
        {
            t = t->next;
            count = t->ID;
            if (count == id || s.size() == MAXSIZE)
            {
                // Them khach hang vao hang cho
                if (q.size() < MAXSIZE)
                {
                    q.push(c);
                    t = recent_table_serve;
                }
                return;
            }
        }
    }
    t->name = name;
    t->age = age;
    c.ID = t->ID;
    s.push(c);
    recent_table_serve = t;
}

void REG(string args, restaurant *r)
{
    int first_pos = args.find_first_of(" ");
    int last_pos = args.find_last_of(" ");

    if (first_pos == (int)string::npos)
    {
        return;
    }

    r->recentTable = r->recentTable->next;

    if (first_pos == last_pos)
    {
        string name = args.substr(0, first_pos);
        int age = atoi(args.substr(first_pos + 1).c_str());
        MOD(r->recentTable, name, age);
    }
    else
    {
        int ID = atoi(args.substr(0, 1).c_str());
        string name = args.substr(first_pos + 1, last_pos - (first_pos + 1));
        int age = atoi(args.substr(last_pos + 1).c_str());
        MOD(r->recentTable, name, age, ID);
    }
    r->recentTable = recent_table_serve;
}

void REGM(restaurant *r, string args)
{
    if (has_found_table)
        return;
    int first_pos = args.find_first_of(" ");
    int last_pos = args.find_last_of(" ");

    string name = args.substr(0, first_pos);
    int age = atoi(args.substr(first_pos + 1, last_pos - (first_pos + 1)).c_str());
    int num = atoi(args.substr(last_pos + 1).c_str());

    table *current_table = r->recentTable;
    table *oldStart_table = nullptr;
    table *start_table = nullptr;
    table *end_table = nullptr;
    int count = 0;
    int maxID = -1;
    int currentID = -1;

    // Tìm dãy bàn trống có ID lớn nhất
    do
    {
        current_table = current_table->next;
        if (current_table->name == "")
        {
            if (currentID == -1)
            {
                currentID = current_table->ID;
                start_table = current_table;
            }
            count++;
            if (count == num)
            {
                if (start_table->ID > maxID)
                {
                    maxID = (maxID == -1) ? currentID : ++currentID;
                    end_table = current_table;
                }
                if (current_table->next->name == "")
                {
                    if (start_table->next->ID < start_table->ID)
                    {
                        start_merge_table = start_table->ID;
                        end_merge_table = end_table->ID;
                        has_found_table = true;
                        break;
                    }
                    oldStart_table = start_table;
                    start_table = start_table->next;
                    current_table = end_table;
                    count--;
                }
            }
        }
        else
        {
            if (current_table != r->recentTable)
            {
                if (current_table->next->name == "")
                {
                    if (count >= num)
                    {
                        oldStart_table = start_table;
                    }
                    count = 0;
                    currentID = -1;
                    continue;
                }
            }
            else
            {
                if (count < num && end_table != nullptr)
                {
                    start_table = oldStart_table;
                    start_merge_table = start_table->ID;
                    end_merge_table = end_table->ID;
                    has_found_table = true;
                }
                else if (end_table == nullptr)
                {
                    has_found_table = false;
                }
            }
        }
    } while (current_table != r->recentTable);

    if (has_found_table)
    {
        merge_table_list = start_table->next;
        start_table->next = end_table->next; // Merge bàn
        // has_merge_table = true;
        MOD(start_table, name, age, start_table->ID);
        r->recentTable = recent_table_serve;
    }
}

void CLE(string args, restaurant *r)
{
    int id = atoi(args.c_str());

    if (id < 1 || id > MAXSIZE)
        return;

    if (has_found_table)
    {
        if (id > start_merge_table && id <= end_merge_table)
        {
            return;
        }
    }
    int count = r->recentTable->ID;
    table *temp_table = r->recentTable;
    while (count != id)
    {
        temp_table = temp_table->next;
        count = temp_table->ID;
    }

    if (id == start_merge_table)
    {
        // has_merge_table = false;
        has_found_table = false;
        temp_table->next = merge_table_list;
        merge_table_list = nullptr;
    }

    if (temp_table->name != "")
    {
        Customer c(temp_table->ID, temp_table->name, temp_table->age);
        temp_table->name = "";
        temp_table->age = 0;
        s.remove(c);
        if (!q.empty())
        {
            c = q.popFront();
            temp_table->name = c.name;
            temp_table->age = c.age;
            s.push(c);
        }
        r->recentTable = temp_table;
    }
}

void PS(restaurant *r, string args = "PS")
{
    Stack sub_s;
    Queue sub_q;
    int num = args != "PS" ? atoi(args.c_str()) : -1;
    int count = 0;
    int num_guests = s.size() + q.size();

    if (s.size() == 0)
    {
        cout << "Empty\n";
        return;
    }
    else if (num > num_guests || num == -1)
    {
        if (!q.empty())
        {
            q.print_reverse();
        }

        if (!s.empty())
        {
            s.print_reverse();
        }
        return;
    }
    else
    {
        while (!q.empty())
        {
            Customer c = q.popBack();
            sub_s.push(c);
            cout << c.name << endl;
            count++;
            if (count == num)
            {
                break;
            }
        }
        while (!sub_s.empty())
        {
            q.push(sub_s.pop());
        }
        while (!s.empty() && count < num)
        {
            Customer c = s.pop();
            sub_s.push(c); // Add item into sub_stack to push it in stack later
            cout << c.name << endl;
            count++;
            if (count == num)
            {
                break;
            }
        }
        while (!sub_s.empty())
        {
            s.push(sub_s.pop());
        }
    }
}

void PQ(restaurant *r, string args = "PQ")
{
    Queue sub_q;
    int num = args != "PQ" ? atoi(args.c_str()) : -1;
    int count = 0;

    if (q.size() == 0)
    {
        cout << "Empty" << endl;
    }
    else if ((num > q.size() && num <= MAXSIZE) || num == -1)
    {
        q.print();
    }
    else
    {
        while (!q.empty())
        {
            Customer c = q.popFront();
            sub_q.push(c);
            cout << c.name << endl;
            count++;
            if (count == num)
            {
                break;
            }
        }
        while (!sub_q.empty())
        {
            q.push(sub_q.popFront());
        }
    }
}

void PT(restaurant *r)
{
    int first_id_in_row = r->recentTable->ID;
    table *temp_table = r->recentTable;
    int count;
    do
    {
        if (temp_table->name != "")
        {
            cout << temp_table->ID << "-" << temp_table->name << endl;
        }
        temp_table = temp_table->next;
        count = temp_table->ID;
    } while (count != first_id_in_row);
}

void SQ(restaurant *r, string args)
{
    int queue_size = q.size();
    if (queue_size == 0)
    {
        cout << "Empty\n";
        return;
    }
    int num = atoi(args.c_str());
    int count = num;
    if (num > queue_size && num <= MAXSIZE)
    {
        count = -1;
    }
    Customer c_queue[queue_size];
    for (int i = 0; i < queue_size; i++)
    {
        c_queue[i] = q.get(i);
    }
    for (int i = 0; i < queue_size - 1; i++)
    {
        int max_age = c_queue[i + 1].age;
        int index = i + 1;
        for (int j = i + 1; j < queue_size; j++)
        {
            if (c_queue[j].age > max_age)
            {
                max_age = c_queue[j].age;
                index = j;
            }
        }

        if (c_queue[i].age < c_queue[index].age)
        {
            Customer key = c_queue[index];
            for (int k = index; k > i; k--)
            {
                c_queue[k] = c_queue[k - 1];
            }
            c_queue[i] = key;
        }
        count--;
        if (count == 0)
        {
            break;
        }
    }
    q.clear();
    for (int i = 0; i < queue_size; i++)
    {
        q.push(c_queue[i]);
    }
    q.print();
}

void simulate(string filename, restaurant *r)
{
    ifstream input("test1.txt");
    if (!input.is_open())
    {
        cout << "File bi loi!";
    }
    string line;
    while (getline(input, line))
    {
        int pos = line.find_first_of(" ");

        if (pos == (int)string::npos && (line != "PS" && line != "PQ" && line != "PT"))
        {
            continue;
        }

        string command = line.substr(0, pos);
        string args = line.substr(pos + 1);

        if (command == "REG")
        {
            REG(args, r);
        }

        if (command == "REGM")
        {
            REGM(r, args);
        }

        if (command == "CLE")
        {
            CLE(args, r);
        }

        if (command == "PS" || line == "PS")
        {
            PS(r, args);
        }

        if (command == "PQ" || line == "PQ")
        {
            PQ(r, args);
        }

        if (line == "PT")
        {
            PT(r);
        }

        if (command == "SQ")
        {
            SQ(r, args);
        }
    }
}