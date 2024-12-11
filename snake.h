#pragma once

using namespace std;

struct Node {
    int x;
    int y;
    Node* next;

    Node(int value, int value1) : x(value), y(value1), next(nullptr) {}
};

class snake
{
private:
    Node* head;
    Node* tail;
public:
    int get_cordX_of_tail()
    {
        return tail->x;
    };
    int get_cordY_of_tail()
    {
        return tail->y;
    };
    int get_cordX_of_element(int index)
    {
        Node* current = head;
        int count = 0;
        while (current)
        {
            if (count == index)
                return current->x;
            current = current->next;
            count++;
        }
        return -1;
    };
    int get_cordY_of_element(int index)
    {
        Node* current = head;
        int count = 0;
        while (current)
        {
            if (count == index)
                return current->y;
            current = current->next;
            count++;
        }
        return -1;
    };
    void set_cordX_of_element(int index, int x)
    {
        Node* current = head;
        int count = 0;
        while (current != nullptr)
        {
            if (count == index)
            {
                current->x = x;
                return;
            }
            current = current->next;
            count++;
        }
    };
    void set_cordY_of_element(int index, int y)
    {
        Node* current = head;
        int count = 0;
        while (current != nullptr)
        {
            if (count == index)
            {
                current->y = y;
                return;
            }
            current = current->next;
            count++;
        }
    };
    void push_back(int x, int y)
    {
        Node* current = new Node(x, y);

        if (head == nullptr)
        {
            head = current;
            tail = current;
        }
        else
        {
            tail->next = current;
            tail = current;
        }
    };
    int get_size()
    {
        int count = 0;
        Node* current = head;
        while (current)
        {
            current = current->next;
            count++;
        }
        return count;
    };
    bool is_snake_part(int x, int y) {
        if (head->next)
        {
            Node* current = head->next;
            while (current) {
                if (current->x == x && current->y == y)
                    return true;
                current = current->next;
            }
        }
        return false;
    }
};


