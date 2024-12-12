#pragma once

using namespace std;

struct Node { //структура узла односвязного списка
    int x;
    int y;
    Node* next;

    Node(int value, int value1) : x(value), y(value1), next(nullptr) {}
};

class snake //сущность змейки
{
private:
    Node* head;
    Node* tail;
public:
    int get_cordX_of_tail() //получение координат хвоста змейки
    {
        return tail->x;
    };
    int get_cordY_of_tail()
    {
        return tail->y;
    };
    int get_cordX_of_element(int index) //получение координат заданного элемента по индексу
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
    void set_cordX_of_element(int index, int x) //смена координат узла по индексу
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
    void push_back(int x, int y) //добавление нового узла в конец списка
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
    int get_size() //получение количества узлов в списке
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
    bool is_snake_part(int x, int y) { //проверка, являются ли координаты частью змейки
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


