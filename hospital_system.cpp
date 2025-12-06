#include <iostream>
#include <queue>
#include <string>
#include "patient.h"
using namespace std;
class HospitalSystem
{
private:
    queue<Patient> patientQueue;

public:
    HospitalSystem() {}

    void AddPatient(const Patient &p)
    {
        patientQueue.push(p);
        cout << "Patient added: " << p.getName() << endl;
    }

    void ServePatient()
    {
        if (!patientQueue.empty())
        {
            Patient p = patientQueue.front();
            cout << "Serving patient: " << p.getName() << endl;
            patientQueue.pop();
        }
        else
        {
            cout << "No patients to serve." << endl;
        }
    }

    void ShowNextPatient()
    {
        if (!patientQueue.empty())
        {
            Patient p = patientQueue.front();
            cout << "Next patient: " << p.getName()
                 << ", Age: " << p.getAge() << endl;
            p.display();
        }
        else
        {
            cout << "No patients in queue." << endl;
        }
    }

    void SearchPatient(const string &name)
    {
        queue<Patient> temp = patientQueue;
        bool found = false;
        while (!temp.empty())
        {
            Patient p = temp.front();
            if (p.getName() == name)
            {
                cout << "Found patient: " << p.getName()
                     << ", Age: " << p.getAge() << endl;
                p.display();
                found = true;
                break;
            }
            temp.pop();
        }
        if (!found)
        {
            cout << "Patient not found." << endl;
        }
    }

    void ShowAllPatients()
    {
        queue<Patient> temp = patientQueue;
        if (temp.empty())
        {
            cout << "No patients in queue." << endl;
            return;
        }
        cout << "All patients in queue:" << endl;
        while (!temp.empty())
        {
            Patient p = temp.front();
            cout << "- " << p.getName()
                 << ", Age: " << p.getAge() << endl;
            p.display();
            temp.pop();
        }
    }

    void TotalPatients()
    {
        cout << "Total patients in queue: " << patientQueue.size() << endl;
    }
};