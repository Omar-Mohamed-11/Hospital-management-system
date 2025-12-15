// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine
#ifndef HOSPITALSYSTEM_H
#define HOSPITALSYSTEM_H

#include <iostream>
#include <bits/stdc++.h>
#include "Patient.h"
#include "PatientQueue.h"
#include "Doctor.h"
#include "DoctorList.h"
#include "Person.h"
#include "SafeInput.h"

using namespace std;

class HospitalSystem
{
private:
    map<CaseType, DoctorList *> doctorsByMajor;
    PatientQueue waiting;        // this if there is no doctor of any major we will add patient herer
    map<int, Person> validateId; // this map to validate id to check if this id is found or not

public:
    HospitalSystem();
    ~HospitalSystem();

    void run();

    // --- Patient Management ---
    void registerPatient();   // done
    void deletePatient();     // done
    void searchPatientByID(); // done

    // --- Doctor Management ---
    void hireDoctor();               // done
    void fireDoctor();               // done
    void searchDoctorByID();         // done
    void searchDoctorByDepartment(); // done
    void showDoctorQueue();          // done

    // Main menu
    void printMainMenu();     // done
    void patientManagement(); // done
    void doctorManagement();  // done
    void printExitScreen();   // done
    void treatPatient();      // under work // dequeue patient from each queue
    void patientsCount();     // done // we will iterate on majors
    void doctorsCount();      // done // we will iterate on majors and LinkedList
    void displayPatients();   // done  // here we will display id , name, Major, Doctor
    void displayDoctors();    // done  // here we will display id , name only
};

#endif