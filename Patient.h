// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine
#ifndef PATIENT_H
#define PATIENT_H

#include <bits/stdc++.h>
#include <iomanip>
#include "Person.h"
using namespace std;

#define nl '\n'

class Patient : public Person
{
public:
    // Empty Constructor
    Patient() : Person() {}

    // Parameterized Constructor: Passes data up to the Person constructor
    Patient(int id, string name, int age, CaseType caseType)
    {
        this->id = id;
        this->name = name;
        this->age = age;
        this->caseType = caseType;
    }

    // Override Display
    void display() const override
    {
        string caseTypeStr;
        switch (caseType)
        {
        case GENERAL:
            caseTypeStr = "GENERAL";
            break;
        case EMERGENCY:
            caseTypeStr = "EMERGENCY";
            break;
        case ICU:
            caseTypeStr = "ICU";
            break;
        case PEDIATRIC:
            caseTypeStr = "PEDIATRIC";
            break;
        case SURGICAL:
            caseTypeStr = "SURGICAL";
            break;
        default:
            caseTypeStr = "UNKNOWN";
        }

        cout << left;
        cout << "  ID        : " << id << "\n";
        cout << "  Name      : " << name << "\n";
        cout << "  Age       : " << age << "\n";
        cout << "  Case Type : " << caseTypeStr << "\n";
    }
};

#endif