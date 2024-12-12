#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h> 
#include "snake.h"

using namespace std;

class Game
{
private:
    // ������� �������� ����
    const int width = 20;
    const int height = 20;

    // ��� ���������� �����
    snake Snake; //���� ������
    int fruitX, fruitY; // ���������� ������
    int score; // ����
    bool gameOver; // ���� ��������� ����
    int dir; //�����������

public:
    void Start_Game() //������ ����
    {
        Setup();
        while (!gameOver) {
            if (dir != 0) //�� ��������� ������ �� ��� ���, ���� ���� �� ��������� � �����
            {
                Draw();
                Input();
                Logic();
                Sleep(100);
            }
            else
            {
                Draw();
                Input();
                Sleep(100);
            }
        }
    }
private:
    // ��� ������������� ����
    void Setup() {
        gameOver = false;
        dir = 0; // ���� ����� �� �����
        Snake.push_back(width / 2, height / 2); //����� ���� ���������� 3 ����
        Snake.push_back(Snake.get_cordX_of_tail(), Snake.get_cordY_of_tail() + 1);
        Snake.push_back(Snake.get_cordX_of_tail(), Snake.get_cordY_of_tail() + 1);
        fruitX = rand() % width; // ��������� ������� ������
        fruitY = rand() % height;
        score = 0;
    };

    // ��� ��������� ����
    void Draw() {
        system("cls"); // ������� ������

        // ������� �������
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        // ������� ����
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0) // ����� �������
                    cout << "#";

                if (j == Snake.get_cordX_of_element(0) && i == Snake.get_cordY_of_element(0)) // ������ ������
                    cout << "O";
                else if (i == fruitY && j == fruitX) // �����
                    cout << "F";
                else if (Snake.is_snake_part(j, i)) // ��������, �������� �� ������ ���������� ������ ����
                    cout << "o";
                else
                    cout << " ";

                if (j == width - 1) // ������ �������
                    cout << "#";
            }
            cout << endl;
        }

        // ������ �������
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        // ����
        cout << "Score: " << score << endl;
    };

    // ��� ��������� �����
    void Input() {
        if (_kbhit()) { // �������� ������� �������
            if (dir == 0) // �������� �� ������� �������� ������, ����� ��� �� ����� ���� ����� � ��������������� ������� �� ������� ��������
            {
                switch (_getch()) {
                case 'a':
                    dir = 2;
                    break;
                case 'd':
                    dir = 4;
                    break;
                case 'w':
                    dir = 1;
                    break;
                default:
                    break;
                }
            }
            else if (dir == 2)
            {
                switch (_getch()) {
                case 'a':
                    dir = 2;
                    break;
                case 'w':
                    dir = 1;
                    break;
                case 's':
                    dir = 3;
                    break;
                default:
                    break;
                }
            }
            else if (dir == 4)
            {
                switch (_getch()) {
                case 'd':
                    dir = 4;
                    break;
                case 'w':
                    dir = 1;
                    break;
                case 's':
                    dir = 3;
                    break;
                default:
                    break;
                }
            }
            else if (dir == 1)
            {
                switch (_getch()) {
                case 'a':
                    dir = 2;
                    break;
                case 'd':
                    dir = 4;
                    break;
                case 'w':
                    dir = 1;
                    break;
                default:
                    break;
                }
            }
            else if (dir == 3)
            {
                switch (_getch()) {
                case 'a':
                    dir = 2;
                    break;
                case 'd':
                    dir = 4;
                    break;
                case 's':
                    dir = 3;
                    break;
                default:
                    break;
                }
            }
        }
    };

    // ��� ���������� ������ ����
    void Logic() {
        //���������� ����������� ������
        int x = Snake.get_cordX_of_element(0);
        int y = Snake.get_cordY_of_element(0);
        int x1, y1;


        // �������� ������ ������
        switch (dir) {
        case 2:
            Snake.set_cordX_of_element(0, Snake.get_cordX_of_element(0) - 1);
            break;
        case 4:
            Snake.set_cordX_of_element(0, Snake.get_cordX_of_element(0) + 1);
            break;
        case 1:
            Snake.set_cordY_of_element(0, Snake.get_cordY_of_element(0) - 1);
            break;
        case 3:
            Snake.set_cordY_of_element(0, Snake.get_cordY_of_element(0) + 1);
            break;
        default:
            break;
        }

        //�������� ����� ���������� ����
        for (int i = 1; i < Snake.get_size(); i++)
        {
            x1 = Snake.get_cordX_of_element(i);
            y1 = Snake.get_cordY_of_element(i);
            Snake.set_cordX_of_element(i, x);
            Snake.set_cordY_of_element(i, y);
            x = x1;
            y = y1;
        }

        // �������� �� ������������ � ���������, � ������ ������������ ���� ���������
        if (Snake.get_cordX_of_element(0) >= width)
            gameOver = true;
        else if (Snake.get_cordX_of_element(0) < 0)
            gameOver = true;

        if (Snake.get_cordY_of_element(0) >= height)
            gameOver = true;
        else if (Snake.get_cordY_of_element(0) < 0)
            gameOver = true;

        // �������� �� ���� � ������ ����
        for (int i = 1; i < Snake.get_size(); i++) {
            if (Snake.get_cordX_of_element(i) == Snake.get_cordX_of_element(0) && Snake.get_cordY_of_element(i) == Snake.get_cordY_of_element(0))
                gameOver = true;
        }

        // �������� �� ��� �� ������ �����
        if (Snake.get_cordX_of_element(0) == fruitX && Snake.get_cordY_of_element(0) == fruitY) {
            score += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;
            Snake.push_back(Snake.get_cordX_of_tail(), Snake.get_cordY_of_tail());
        }
    };
};

