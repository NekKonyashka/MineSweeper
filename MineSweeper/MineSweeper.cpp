#include <iostream>
#include <vector>
#include "Point.h"

#define SIZE 10
#define MINES_COUNT 16

char field[SIZE][SIZE];
std::vector<Point> mineField;
std::vector<Point> checkedFields;
bool is_end = false;
bool is_failure = false;
short x, y;

void fill();
void show();
void showMines();
void spawnMines();
bool checkFieldOfMine(Point pos);
void checkAround(Point pos);

int main()
{
    setlocale(LC_ALL, "ru");
    fill();
    spawnMines();
    while (!is_end && ( checkedFields.size() < ( SIZE * SIZE ) - MINES_COUNT ))
    {
        show();
        if (scanf_s("%hu %hu", &x, &y) == 2 && x >= 0 && y >= 0 && x < SIZE && y < SIZE)
        {
            if (!checkFieldOfMine({ x,y })) {
                is_failure = true;
                is_end = true;
            }
            else {
                checkAround({ x,y });
            }
        }
        system("cls");
    }
    showMines();
    show();
    if (is_failure) {
        printf("========================YOU=LOSE========================");
    }
    else {
        printf("========================YOU=WIN========================");
    }
}

void fill() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            field[i][j] = '.';
        }
    }
}

bool isChecked(Point pos) {
    for (Point field : checkedFields) {
        if (field.x == pos.x && field.y == pos.y) {
            return true;
        }
    }
    return false;
}

void checkAround(Point pos) {
    if (!isChecked(pos)) {
        checkedFields.push_back(pos);
        short count = 0, f_x = pos.x - 1, f_y = pos.y - 1;
        for (short i = f_y; i <= pos.y + 1; i++) {
            for (short j = f_x; j <= pos.x + 1; j++) {
                if (!checkFieldOfMine({j,i})) {
                    count++;
                }
            }
        }
        field[pos.y][pos.x] = (char)(count + '0');
        if (count == 0) {
            for (short i = f_y; i <= pos.y + 1; i++) {
                for (short j = f_x; j <= pos.x + 1; j++) {
                    if (!isChecked({j,i}) && (i >= 0 && i < SIZE) && (j >= 0 && j < SIZE)) {
                        checkAround({ j,i });
                    }
                }
            }
        }
    }
}

void show() {
    printf("Для выбора клетки вводи две цифры от 0 до %d через пробел\n", SIZE - 1);
    for (int i = -1; i < SIZE; i++) {
        if (i == -1) {
            printf("      ");
        }
        else {
            printf("%d ", i);
        }
    }
    printf("\n\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d     ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ",field[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void showMines() {
    for (Point mine : mineField) {
        field[mine.y][mine.x] = '+';
    }
}

void spawnMines() {
    short x, y;
    for (int i = 0; i < MINES_COUNT; i++) {
        srand(time(NULL));
        do {
            x = rand() % SIZE;
            y = rand() % SIZE;
        } while(!checkFieldOfMine({x,y}));
        mineField.push_back({ x,y });
    }
}

bool checkFieldOfMine(Point pos) {
    for (Point mine : mineField) {
        if (mine.x == pos.x && mine.y == pos.y) {
            return false;
        }
    }
    return true;
}
