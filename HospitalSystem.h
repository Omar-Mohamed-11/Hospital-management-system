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
    void registerPatient();
    void deletePatient();
    void searchPatientByID();

    // --- Doctor Management ---
    void hireDoctor();
    void fireDoctor();
    void searchDoctorByID();
    void searchDoctorByDepartment();
    void showDoctorQueue();

    // Main menu
    void printMainMenu();
    void patientManagement();
    void doctorManagement();
    void printExitScreen();
    // void treatPatient();              // dequeue patient from each queue
    // void patientsCount();            // we will iterate on majors
    // void doctorsCount();             // we will iterate on majors and LinkedList
    void displayPatients(); // here we will display id , name, Major, Doctor
    void displayDoctors();  // here we will display id , name only
};

#endif