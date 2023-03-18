#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "main.h"
#include "queue.cpp"

using namespace std;

Queue q; // Hang cho
Stack s; // Danh sach khach trong nha hang

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
            if (count == id)
            {
                // Them khach hang vao hang cho
                if (q.size() < MAXSIZE)
                {
                    q.push(c);
                }
                return;
            }
        }
    }
    t->name = name;
    t->age = age;
    c.ID = t->ID;
    s.push(c);
}

void REG(string args, restaurant *r)
{
    int first_pos = args.find_first_of(" ");
    int last_pos = args.find_last_of(" ");

    if (first_pos == string::npos)
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
}

void CLE(string args, restaurant *r)
{
    int id = atoi(args.c_str());

    int count = r->recentTable->ID;
    table *temp_table = r->recentTable;
    while (count != id)
    {
        temp_table = temp_table->next;
        count = temp_table->ID;
    }

    if (temp_table->name != "")
    {
        Customer c(temp_table->ID, temp_table->name, temp_table->age);
        temp_table->name = "";
        temp_table->age = 0;
        s.remove(c);
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
            s.push(sub_s.pop());
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

void SQ(restaurant *r, string args)
{
    int num = atoi(args.c_str());
    if (q.size() == 0)
    {
        cout << "Empty\n";
    }
}

int main()
{
    restaurant *r = new restaurant();
    for (int i = 1; i <= MAXSIZE; i++)
    {
        r->recentTable = r->insert(r->recentTable, i, "", 0);
    }
    ifstream input("subtest.txt");
    if (!input.is_open())
    {
        cout << "File bi loi!";
    }
    string line;
    while (!input.eof())
    {
        getline(input, line);
        int pos = line.find_first_of(" ");

        if (pos == string::npos && (line != "PS" && line != "PQ"))
        {
            continue;
        }

        string command = line.substr(0, pos);
        string args = line.substr(pos + 1);

        if (command == "REG")
        {
            REG(args, r);
        }

        if (command == "CLE")
        {
            CLE(args, r);
        }

        if (command == "SIZE")
        {
            cout << SIZE(r);
        }

        if (command == "PS" || line == "PS")
        {
            PS(r, args);
        }

        if (command == "PQ" || line == "PQ")
        {
            PQ(r, args);
        }

        if (command == "SQ")
        {
        }
    }
    return 0;
}

void expandTable(table *t)
{
    table *currentTable = t->next;
    while (currentTable != t)
    {                                      // traverse the circular linked list until we get back to the original table
        t->age += currentTable->age;       // add the age of the current table to the original table
        table *temp = currentTable;        // save a pointer to the current table so we can delete it
        currentTable = currentTable->next; // move on to the next table
        delete temp;                       // delete the current table
    }
    t->next = t; // set the next pointer of the original table to itself to restore the circular linked list
}

table *mergeTables(table *firstTable, int k)
{
    table *newTable = new table(-1, "Merged Table", 0, nullptr); // create a new table to merge into
    table *currentTable = firstTable;
    for (int i = 0; i < k; i++)
    {
        if (currentTable == nullptr)
        { // if there are less than k tables in the list
            return nullptr;
        }
        newTable->age += currentTable->age; // add the age of the current table to the new table
        currentTable = currentTable->next;  // move on to the next table
    }
    newTable->ID = firstTable->ID; // set the ID of the new table to the ID of the first table
    newTable->next = currentTable; // set the next pointer of the new table to point to the next table after the merged tables
    return newTable;
}

void REGM(restaurant *r, string args)
{
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
                if (maxID == -1 || currentID > maxID)
                {
                    maxID = currentID;
                    end_table = current_table;
                }
                if (current_table->next->name == "")
                {
                    oldStart_table = start_table;
                    start_table = start_table->next;
                    current_table = start_table;
                    count--;
                }
            }
        }
        else
        {
            if (current_table->next->name == "")
            {
                current_table = current_table->next;
                count = 0;
                currentID = -1;
                continue;
            }
        }
    } while (current_table != r->recentTable);
}