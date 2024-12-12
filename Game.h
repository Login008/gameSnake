#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h> 
#include "snake.h"

using namespace std;

class Game
{
private:
    // размеры игрового поля
    const int width = 20;
    const int height = 20;

    // для управления игрой
    snake Snake; //сама змейка
    int fruitX, fruitY; // координаты фрукта
    int score; // очки
    bool gameOver; // флаг окончания игры
    int dir; //направление

public:
    void Start_Game() //Запуск игры
    {
        Setup();
        while (!gameOver) {
            if (dir != 0) //не проверяем логику до тех пор, пока змея не сдвинется с места
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
    // для инициализации игры
    void Setup() {
        gameOver = false;
        dir = 0; // змея стоит на месте
        Snake.push_back(width / 2, height / 2); //задаём змее изначально 3 узла
        Snake.push_back(Snake.get_cordX_of_tail(), Snake.get_cordY_of_tail() + 1);
        Snake.push_back(Snake.get_cordX_of_tail(), Snake.get_cordY_of_tail() + 1);
        fruitX = rand() % width; // случайная позиция фрукта
        fruitY = rand() % height;
        score = 0;
    };

    // для отрисовки поля
    void Draw() {
        system("cls"); // очистка экрана

        // верхняя граница
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        // игровое поле
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0) // левая граница
                    cout << "#";

                if (j == Snake.get_cordX_of_element(0) && i == Snake.get_cordY_of_element(0)) // голова змейки
                    cout << "O";
                else if (i == fruitY && j == fruitX) // фрукт
                    cout << "F";
                else if (Snake.is_snake_part(j, i)) // проверка, являются ли данные координаты частью змеи
                    cout << "o";
                else
                    cout << " ";

                if (j == width - 1) // правая граница
                    cout << "#";
            }
            cout << endl;
        }

        // нижняя граница
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        // очки
        cout << "Score: " << score << endl;
    };

    // для обработки ввода
    void Input() {
        if (_kbhit()) { // проверка нажатия клавиши
            if (dir == 0) // проверка на текущее движение змейки, чтобы она не могла идти сразу в противоположную сторону от стороны движения
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

    // для обновления логики игры
    void Logic() {
        //сохранение координатов змейки
        int x = Snake.get_cordX_of_element(0);
        int y = Snake.get_cordY_of_element(0);
        int x1, y1;


        // движение головы змейки
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

        //движение всего остального тела
        for (int i = 1; i < Snake.get_size(); i++)
        {
            x1 = Snake.get_cordX_of_element(i);
            y1 = Snake.get_cordY_of_element(i);
            Snake.set_cordX_of_element(i, x);
            Snake.set_cordY_of_element(i, y);
            x = x1;
            y = y1;
        }

        // проверка на столкновение с границами, в случае столкновения игра закончена
        if (Snake.get_cordX_of_element(0) >= width)
            gameOver = true;
        else if (Snake.get_cordX_of_element(0) < 0)
            gameOver = true;

        if (Snake.get_cordY_of_element(0) >= height)
            gameOver = true;
        else if (Snake.get_cordY_of_element(0) < 0)
            gameOver = true;

        // проверка на врез в самого себя
        for (int i = 1; i < Snake.get_size(); i++) {
            if (Snake.get_cordX_of_element(i) == Snake.get_cordX_of_element(0) && Snake.get_cordY_of_element(i) == Snake.get_cordY_of_element(0))
                gameOver = true;
        }

        // проверка на был ли сожран фрукт
        if (Snake.get_cordX_of_element(0) == fruitX && Snake.get_cordY_of_element(0) == fruitY) {
            score += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;
            Snake.push_back(Snake.get_cordX_of_tail(), Snake.get_cordY_of_tail());
        }
    };
};

