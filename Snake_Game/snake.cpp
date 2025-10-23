#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <thread>
#include <ctime>
#include <vector>
#pragma comment(lib, "winmm.lib")
using namespace std;

class SnakeGame {
public:
    SnakeGame(int w = 40, int h = 15)
        : width(w), height(h), hOut(GetStdHandle(STD_OUTPUT_HANDLE)) {
        loadHighScore();
    }

    int run() {
        setup();
        while (!gameOver) {
            draw();
            input();
            logic();
            Sleep(frameMs);
        }
        saveHighScore();
        endScreen();
        return 0;
    }

private:
    // config
    const int width;
    const int height;
    const int frameMs = 40; // frame delay in ms

    // console
    HANDLE hOut;
    CONSOLE_CURSOR_INFO oldCursor{};

    // game state
    bool gameOver = false;
    int score = 0;
    int highScore = 0;

    struct Point { int x; int y; };
    Point head{};
    Point fruit{};
    vector<Point> tail;

    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
    Direction dir = STOP;

    void loadHighScore() {
        ifstream fin("highscore.txt");
        if (!(fin >> highScore)) highScore = 0;
        fin.close();
    }

    void saveHighScore() {
        ofstream fout("highscore.txt");
        fout << highScore;
        fout.close();
    }

    void setup() {
        gameOver = false;
        dir = STOP;
        head.x = width / 2;
        head.y = height / 2;
        srand(static_cast<unsigned int>(time(nullptr)));
        fruit.x = rand() % width;
        fruit.y = rand() % height;
        score = 0;
        tail.clear();

        // hide cursor
        if (GetConsoleCursorInfo(hOut, &oldCursor)) {
            CONSOLE_CURSOR_INFO cci = oldCursor;
            cci.bVisible = FALSE;
            SetConsoleCursorInfo(hOut, &cci);
        }

        // start bg music loop (optional file)
        PlaySound(TEXT("snakebg.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }

    void draw() {
        // position cursor at top-left
        COORD pos = { 0, 0 };
        SetConsoleCursorPosition(hOut, pos);

        // top wall
        SetConsoleTextAttribute(hOut, 14);
        for (int i = 0; i < width + 2; ++i) cout << "#";
        cout << '\n';

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (j == 0) { SetConsoleTextAttribute(hOut, 14); cout << "#"; }
                if (i == head.y && j == head.x) {
                    SetConsoleTextAttribute(hOut, 10); cout << "O";
                } else if (i == fruit.y && j == fruit.x) {
                    SetConsoleTextAttribute(hOut, 12); cout << "*";
                } else {
                    bool drawn = false;
                    for (const auto &p : tail) {
                        if (p.x == j && p.y == i) { SetConsoleTextAttribute(hOut, 2); cout << "o"; drawn = true; break; }
                    }
                    if (!drawn) cout << " ";
                }
                if (j == width - 1) { SetConsoleTextAttribute(hOut, 14); cout << "#"; }
            }
            cout << '\n';
        }

        // bottom wall
        SetConsoleTextAttribute(hOut, 14);
        for (int i = 0; i < width + 2; ++i) cout << "#";
        SetConsoleTextAttribute(hOut, 7);
        cout << "\nScore: " << score << "   High Score: " << highScore << endl;
    }

    void input() {
        while (_kbhit()) {
            int ch = _getch();
            if (ch == 0 || ch == 224) {
                int ch2 = _getch();
                switch (ch2) {
                    case 75: if (dir != RIGHT) dir = LEFT; break;
                    case 77: if (dir != LEFT) dir = RIGHT; break;
                    case 72: if (dir != DOWN) dir = UP; break;
                    case 80: if (dir != UP) dir = DOWN; break;
                }
            } else {
                if (ch == 'x' || ch == 'X') gameOver = true;
            }
        }

        // fallback polling
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)  if (dir != RIGHT) dir = LEFT;
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) if (dir != LEFT) dir = RIGHT;
        else if (GetAsyncKeyState(VK_UP) & 0x8000)    if (dir != DOWN) dir = UP;
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000)  if (dir != UP) dir = DOWN;
    }

    void logic() {
        // move tail
        if (!tail.empty()) {
            for (int i = static_cast<int>(tail.size()) - 1; i > 0; --i) {
                tail[i] = tail[i-1];
            }
            tail[0] = head;
        }

        switch (dir) {
            case LEFT:  --head.x; break;
            case RIGHT: ++head.x; break;
            case UP:    --head.y; break;
            case DOWN:  ++head.y; break;
            default: break;
        }

        // check wall collision
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
            gameOver = true;
            return;
        }

        // self collision
        for (const auto &p : tail) if (p.x == head.x && p.y == head.y) { gameOver = true; return; }

        // fruit
        if (head.x == fruit.x && head.y == fruit.y) {
            // play a short async beep as feedback
            std::thread([](){ Beep(1000, 70); Beep(1400, 50); }).detach();
            score += 10;
            tail.push_back({-1, -1});
            fruit.x = rand() % width;
            fruit.y = rand() % height;
            if (score > highScore) highScore = score;
        }
    }

    void endScreen() {
        // stop background music and play game over
        PlaySound(NULL, 0, 0);
        PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);

        saveHighScore();
        SetConsoleTextAttribute(hOut, 12);
        cout << "\n\nGAME OVER! Final Score: " << score << "\n";
        SetConsoleTextAttribute(hOut, 7);
        system("pause");

        // restore cursor
        SetConsoleCursorInfo(hOut, &oldCursor);
    }
};

int main() {
    SnakeGame game;
    return game.run();
}
