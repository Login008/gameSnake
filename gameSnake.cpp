#include <iostream>
#include <conio.h>
#include <windows.h> 
#include "snake.h"

using namespace std;

// размеры игрового поля
const int width = 20;
const int height = 20;

// для управления игрой
snake Snake;
int fruitX, fruitY; // координаты фрукта
int score; // очки
bool gameOver; // флаг окончания игры
int dir; //направление

// для инициализации игры
void Setup() {
    gameOver = false;
    dir = 0; // змея стоит на месте
    Snake.push_back(width / 2, height / 2);
    fruitX = rand() % width; // случайная позиция фрукта
    fruitY = rand() % height;
    score = 0;
}

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
            else if (Snake.is_snake_part(j, i))
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
}

// для обработки ввода
void Input() {
    if (_kbhit()) { // проверка нажатия клавиши
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
        case 's':
            dir = 3;
            break;
        default:
            break;
        }
    }
}

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

    for (int i = 1; i < Snake.get_size(); i++)
    {
        x1 = Snake.get_cordX_of_element(i);
        y1 = Snake.get_cordY_of_element(i);
        Snake.set_cordX_of_element(i, x);
        Snake.set_cordY_of_element(i, y);
        x = x1;
        y = y1;
    }

    // проверка на столкновение с границами
    if (Snake.get_cordX_of_element(0) >= width)
        Snake.set_cordX_of_element(0, 0);
    else if (Snake.get_cordX_of_element(0) < 0)
        Snake.set_cordX_of_element(0, width - 1);

    if (Snake.get_cordY_of_element(0) >= height)
        Snake.set_cordY_of_element(0, 0);
    else if (Snake.get_cordY_of_element(0) < 0)
        Snake.set_cordY_of_element(0, height - 1);

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
}

// глав функция
int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // для плавности игры
    }
    return 0;
}
