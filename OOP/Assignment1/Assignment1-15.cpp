
#include <iostream>
#include <ctime>
using namespace std;

#define CHANCES 5
#define DISPLAY_ANSWER 0

int seed = time(NULL);

int random() {
    seed = 2937845 * seed + 86745034;
    int temp = seed % 9 + 1;
    if (temp < 0)
    {
        temp *= -1;
    }
    return temp;
}

void userInput(int user[4]) {
    char temp[5];
    cin >> temp;
    for (int i = 0; i < 4; i++)
    {
        user[i] = temp[i] - 48;
    }
    return;
}

int main()
{
    int number[4];
    int init = 0;
    while (init < 4)
    {
        number[init] = random();
        int check = 0;
        for (int i = 0; i < init; i++)
        {
            if (number[init] == number[i]) {
                check += 1;
            }
        }
        if (check == 0) {
            init++;
        }
    }

    int hits = 0;
    int blows = 0;

    for (int i = 0; i < CHANCES; i++)
    {
        cout << "Guess: ";
        int user[4] = { 0, };
        userInput(user);

        hits = 0;
        blows = 0;

        for (int j = 0; j < 4; j++)
        {
            if (number[j] == user[j]) {
                hits++;
            }
            for (int k = 0; k < 4; k++)
            {
                if (j != k && number[k] == user[j]) {
                    blows++;
                }
            }
        }
        if (DISPLAY_ANSWER) {
            for (int i = 0; i < 4; i++)
            {
                cout << number[i];
            }
        }

        cout << endl << "Hit: " << hits;
        cout << ", Blow: " << blows << endl << endl;
        cout << "-------------------" << endl << endl;

        if (hits == 4) {
            cout << "Win";
            break;
        }
    }
    if (hits != 4) {
        cout << "Lose" << endl << endl;
        cout << "the correct answer: ";
        for (int i = 0; i < 4; i++)
        {
            cout << number[i];
        }
        cout << endl;
    }
}

