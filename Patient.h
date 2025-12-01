#ifndef PATIENT_H
#define PATIENT_H

#include <bits/stdc++.h>
using namespace std;

// Enum for case types
enum CaseType
{
    GENERAL,
    EMERGENCY,
    ICU,
    PEDIATRIC,
    SURGICAL
};

class Patient
{
private:
    int id;
    string name;
    int age;
    CaseType caseType;

public:
    // Empty constructor
    Patient()
    {
        id = 0;
        name = "";
        age = 0;
        caseType = GENERAL;
    }

    // Parameterized constructor
    Patient(int patientId, string patientName, int patientAge, CaseType patientCaseType)
    {
        id = patientId;
        name = patientName;
        age = patientAge;
        caseType = patientCaseType;
    }

    // Display patient information
    void display() const
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

        cout << "Patient ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Case Type: " << caseTypeStr << endl;
        cout << "------------------------" << endl;
    }

    // Getters
    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    CaseType getCaseType() const
    {
        return caseType;
    }

    // Setters
    void setName(const string &newName)
    {
        name = newName;
    }

    void setAge(int newAge)
    {
        if (newAge >= 0)
        {
            age = newAge;
        }
        else
        {
            cout << "Error: Age cannot be negative!" << endl;
        }
    }

    void setCaseType(CaseType newCaseType)
    {
        caseType = newCaseType;
    }
};

#endif