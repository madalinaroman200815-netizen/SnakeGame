#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;

    // Pozitia initiala in mijlocul tablei
    x = width / 2;
    y = height / 2;

    // Pozitie aleatoare pentru fruct
    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;
}

void Draw()
{
    system("cls");

    // Partea de sus a tablei
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // Interiorul tablei
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0) cout << "#"; // perete stanga

            if (i == y && j == x)
                cout << "O"; // sarpele (capul)
            else if (i == fruitY && j == fruitX)
                cout << "F"; // fructul
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // coada
                        printTail = true;
                    }
                }
                if (!printTail) cout << " ";
            }

            if (j == width - 1) cout << "#"; // perete dreapta
        }
        cout << endl;
    }

    // Partea de jos a tablei
    for (int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl << "Scor: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a': dir = LEFT; break;
        case 'd': dir = RIGHT; break;
        case 'w': dir = UP; break;
        case 's': dir = DOWN; break;
        case 'x': gameOver = true; break; // iesire
        }
    }
}

void Logic()
{
    // Mutam coada
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    // Miscarea capului
    switch (dir)
    {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    default: break;
    }

    // Coliziuni cu peretii → game over
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // Coliziune cu coada
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // Mancam fructul
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++; // creste coada
    }
}

int main()
{
    Setup();

    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100); // viteza jocului
    }

    cout << "Game Over!" << endl;

    return 0;
}
