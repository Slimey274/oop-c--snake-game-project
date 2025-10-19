/**********************************************************************
 * Simple Console Snake Game (C++)
 * Works on Windows (Visual Studio)
 **********************************************************************/

#include <iostream>
#include <conio.h>      // for _kbhit() and _getch()
#include <windows.h>    // for Sleep()
#include <vector>
#include <utility>      // for std::pair
using namespace std;

// Direction enumeration
enum Dir { STOP = 0, LEFT, RIGHT, UP, DOWN };

// Global variables
bool gameOver;
const int width = 20;
const int height = 17;
int x, y;           // snake head
int fruitX, fruitY; // fruit position
int score;
Dir dir;            // current direction

// store body segments as (x, y) positions
vector<pair<int, int>> snake;

// Function declarations
void setup();
void draw();
void input();
void logic();
void changeDirection(Dir newDir);
void moveSnake();

// ---------------------------------------------------------------
// setup() – initialize game
void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    snake.clear();
    snake.push_back({ x, y });
}

// ---------------------------------------------------------------
// draw() – draw the grid, snake, and fruit
void draw() {
    system("cls"); // clear console

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";

            bool printed = false;

            // Draw snake
            for (size_t k = 0; k < snake.size(); k++) {
                if (snake[k].first == j && snake[k].second == i) {
                    if (k == 0)
                        cout << "O"; // head
                    else
                        cout << "o"; // body
                    printed = true;
                    break;
                }
            }

            if (!printed) {
                if (j == fruitX && i == fruitY)
                    cout << "F";
                else
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

// ---------------------------------------------------------------
// input() – handle keyboard input
void input() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'a': changeDirection(LEFT);  break;
        case 'd': changeDirection(RIGHT); break;
        case 'w': changeDirection(UP);    break;
        case 's': changeDirection(DOWN);  break;
        case 'x': gameOver = true;        break;
        }
    }
}

// ---------------------------------------------------------------
// changeDirection() – prevent reversing into itself
void changeDirection(Dir newDir) {
    if ((dir == LEFT && newDir != RIGHT) ||
        (dir == RIGHT && newDir != LEFT) ||
        (dir == UP && newDir != DOWN) ||
        (dir == DOWN && newDir != UP) ||
        dir == STOP)
    {
        dir = newDir;
    }
}

// ---------------------------------------------------------------
// moveSnake() – update the snake's position
void moveSnake() {
    pair<int, int> newHead = snake[0]; // start with current head

    switch (dir) {
    case LEFT:  newHead.first--;  break;
    case RIGHT: newHead.first++;  break;
    case UP:    newHead.second--; break;
    case DOWN:  newHead.second++; break;
    default: break;
    }

    // Insert new head at beginning
    snake.insert(snake.begin(), newHead);

    // Remove tail if no fruit eaten
    if (newHead.first == fruitX && newHead.second == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    else {
        snake.pop_back();
    }
}

// ---------------------------------------------------------------
// logic() – detect collisions and update game state
void logic() {
    moveSnake();

    int headX = snake[0].first;
    int headY = snake[0].second;

    // Wall collision
    if (headX >= width || headX < 0 || headY >= height || headY < 0)
        gameOver = true;

    // Self collision
    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i].first == headX && snake[i].second == headY)
            gameOver = true;
    }
}

// ---------------------------------------------------------------
// main() – main game loop
int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100); // control speed
    }

    cout << "\nGame Over! Final Score: " << score << endl;
    system("pause");
    return 0;
}
