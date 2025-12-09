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
    PatientQueue patientQueue;
    map<int, Person> validateId; // this to validate id to check if this id is found or not
    map<int, Doctor> doctors;    // to store all doctors in one place and it map data structure to make it easy to erase and search without looping
    map<int, Patient> patients;  // to store all doctors in one place and it map data structure to make it easy to erase and search without looping

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

    // --- Core Workflow ---
    // void treatPatient();
    // void patientsCount();
    // void doctorsCount();
    // void displayPatients();
    // void displayDoctors();

    // Main menu
    void printMainMenu();
    void patientManagement();
    void doctorManagement();
    void printExitScreen();
};

#endif