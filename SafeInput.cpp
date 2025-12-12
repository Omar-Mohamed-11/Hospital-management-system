// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine
#include <bits/stdc++.h>
#include "SafeInput.h"
#define sp " "
using namespace std;

int safe_input_int(int min, int max)
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cout << "Invalid input! Expected an integer.\n";
            cout << "Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice < min || choice > max)
        {
            cout << "Out of range, please try again.\n";
            cout << "Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        return choice;
    }
}

double sallary_generator(int yearsOfExperience)
{
    // we will calc sallary based on years of experience
    return double(8000 + 1200.0 * sqrt(yearsOfExperience));
}
