#include <iostream>
#include <queue>
#include <string>
#include "patient.h"
#include "PatientQueue.h"
using namespace std;
class HospitalSystem
{
private:
    PatientQueue patientQueue;

public:
    HospitalSystem() {}

    void AddPatient(const Patient &p)
    {
        patientQueue.enqueue(p);
        cout << "Patient added: " << p.getName() << endl;
    }

    void ServePatient()
    {
        if (!patientQueue.isEmpty())
        {
            Patient p = patientQueue.next();
            cout << "Serving patient: " << p.getName() << endl;
            patientQueue.dequeue();
        }
        else
        {
            cout << "No patients to serve." << endl;
        }
    }

    void ShowNextPatient()
    {
        if (!patientQueue.isEmpty())
        {
            Patient p = patientQueue.next();
            cout << "Next patient: " << p.getName()
                 << ", Age: " << p.getAge() << endl;
            p.display();
        }
        else
        {
            cout << "No patients in queue." << endl;
        }
    }

    void SearchPatient(int id)
    {
        Patient p = patientQueue.searchPatient(id);
        if (p.getId() == -1)
        {
            cout << "Patient not found." << endl;
        }
        else
        {
            cout << "Patient found: " << p.getName() << endl;
            p.display();
        }
    }

    void ShowAllPatients()
    {
        patientQueue.display();
    }
};
