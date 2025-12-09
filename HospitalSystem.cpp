// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine
#include "HospitalSystem.h"
#include "SafeInput.h"

// ================= CONSTRUCTOR & DESTRUCTOR (Memory management) =================

HospitalSystem::HospitalSystem() // allocate memory (create list of doctors for each Major)
{
    doctorsByMajor[GENERAL] = new DoctorList();
    doctorsByMajor[EMERGENCY] = new DoctorList();
    doctorsByMajor[ICU] = new DoctorList();
    doctorsByMajor[PEDIATRIC] = new DoctorList();
    doctorsByMajor[SURGICAL] = new DoctorList();
}

HospitalSystem::~HospitalSystem() // save memory leak
{
    cout << "System shutting down... Cleaning up memory." << endl;
    for (auto const &[key, listPtr] : doctorsByMajor)
    {
        delete listPtr;
    }
}

// ================= PATIENT MANAGEMENT =================

// void HospitalSystem::addPatient()
// {
//     cout << "\n=== REGISTER NEW PATIENT ===" << endl;

//     int id;
//     cout << "Enter ID: ";
//     cin >> id;

//     string name;
//     cout << "Enter Name: ";
//     cin.ignore(); // Clears the "Enter" key from the buffer
//     getline(cin, name);

//     int age;
//     cout << "Enter Age: ";
//     cin >> age;

//     int type;
//     cout << "Select Case Type:\n1:General, 2:Emergency, 3:ICU, 4:Pediatric, 5:Surgical\nChoice: ";
//     type = safe_input_int(1, 5);

//     Patient p(id, name, age, (CaseType)type);
//     patientQueue.enqueue(p);

//     cout << "Success: Patient " << name << " added to Waiting Room." << endl;
// }

// void HospitalSystem::deletePatient()
// {
//     if (patientQueue.isEmpty())
//     {
//         cout << "Waiting room is empty." << endl;
//         return;
//     }

//     int id;
//     cout << "Enter Patient ID to remove from Waiting Room: ";
//     cin >> id;

//     Patient p = patientQueue.removeById(id);

//     if (p.getId() != 0)
//     {
//         cout << "Patient " << p.getName() << " removed successfully." << endl;
//     }
// }

// void HospitalSystem::showWaitingRoom()
// {
//     cout << "\n=== WAITING ROOM STATUS ===" << endl;
//     patientQueue.display();
// }

// // ================= DOCTOR MANAGEMENT =================

// void HospitalSystem::addDoctor()
// {
//     cout << "\n=== HIRE NEW DOCTOR ===" << endl;

//     int id;
//     cout << "Enter ID: ";
//     cin >> id;

//     string name;
//     cout << "Enter Name: ";
//     cin.ignore();
//     getline(cin, name);

//     int age;
//     cout << "Enter Age: ";
//     cin >> age;

//     int type;
//     cout << "Select Specialization:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
//     cin >> type;

//     CaseType major = (CaseType)type;
//     Doctor d(id, name, age, major);

//     doctorsByMajor[major]->addDoctor(d);
//     cout << "Doctor " << name << " assigned to " << type << " department." << endl;
// }

// void HospitalSystem::showDoctors()
// {
//     int type;
//     cout << "Select Department to View:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
//     cin >> type;

//     cout << "\n--- DOCTOR LIST (" << type << ") ---" << endl;
//     doctorsByMajor[(CaseType)type]->display();
// }

// // ================= CORE WORKFLOW =================

// void HospitalSystem::assignPatient()
// {
//     if (patientQueue.isEmpty())
//     {
//         cout << "No patients in the waiting room." << endl;
//         return;
//     }

//     Patient nextP = patientQueue.next();
//     CaseType neededMajor = nextP.getCaseType();

//     cout << "\n=== ASSIGN PATIENT TO DOCTOR ===" << endl;
//     cout << "Patient: " << nextP.getName() << " (Needs Dept: " << neededMajor << ")" << endl;

//     DoctorList *deptList = doctorsByMajor[neededMajor];

//     if (deptList->isEmpty())
//     {
//         cout << "CRITICAL: No doctors available in this department!" << endl;
//         return;
//     }

//     cout << "Available Doctors in this Department:" << endl;
//     deptList->display();

//     int docId;
//     cout << "Enter Doctor ID to assign: ";
//     cin >> docId;

//     PatientQueue *docQueue = deptList->SearchById(docId);

//     if (docQueue != nullptr)
//     {
//         Patient p = patientQueue.dequeue();
//         docQueue->enqueue(p);
//         cout << "Success: Patient transferred to Dr. ID " << docId << endl;
//     }
//     else
//     {
//         cout << "Error: Invalid Doctor ID." << endl;
//     }
// }

// void HospitalSystem::treatPatient()
// {
//     cout << "\n=== DOCTOR TREATMENT PORTAL ===" << endl;

//     int type;
//     cout << "Select Department:\n0:General, 1:Emergency, 2:ICU, 3:Pediatric, 4:Surgical\nChoice: ";
//     cin >> type;

//     DoctorList *list = doctorsByMajor[(CaseType)type];

//     if (list->isEmpty())
//     {
//         cout << "No doctors in this department." << endl;
//         return;
//     }

//     list->display();

//     int docId;
//     cout << "Enter Doctor ID performing the treatment: ";
//     cin >> docId;

//     list->treatPatient(docId);
// }

// ================= PATIENT MANAGEMENT =================
void HospitalSystem::registerPatient() {}
void HospitalSystem::deletePatient() {}
void HospitalSystem::searchPatientByID() {}

// ================= DOCTOR MANAGEMENT =================
void HospitalSystem::hireDoctor() {}
void HospitalSystem::fireDoctor() {}
void HospitalSystem::searchDoctorByID() {}
void HospitalSystem::searchDoctorByDepartment() {}
void HospitalSystem::showDoctorQueue() {}

// ================= MAIN MENU & PATIENT MENU & DOCTOR MENU & closing =================

void HospitalSystem::printMainMenu() // welcome menu
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|                 HOSPITAL SYSTEM                  |\n";
    cout << "+==================================================+\n";
    cout << "|                                                  |\n";
    cout << "|   1) Patient Management                          |\n";
    cout << "|   2) Doctor Management                           |\n";
    cout << "|   3) Treat Patient                               |\n";
    cout << "|   5) doctors Count                               |\n";
    cout << "|   6) Patient Count                               |\n";
    cout << "|   7) display All doctors                         |\n";
    cout << "|   8) display All patients                        |\n";
    cout << "|                                                  |\n";
    cout << "|   0) Exit                                        |\n";
    cout << "|                                                  |\n";
    cout << "+==================================================+\n";
    cout << "Choose an option: ";
}
void HospitalSystem::printExitScreen() // exit menu
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|                                                  |\n";
    cout << "|        THANK YOU FOR USING THE SYSTEM!           |\n";
    cout << "|                                                  |\n";
    cout << "|              System shutting down...             |\n";
    cout << "|                                                  |\n";
    cout << "+==================================================+\n";
}

void HospitalSystem::patientManagement() // this menu to to manage patients
{
    int choice;

    while (true)
    {
        cout << "\n";
        cout << "+==================================================+\n";
        cout << "|              PATIENT MANAGEMENT MENU             |\n";
        cout << "+==================================================+\n";
        cout << "|                                                  |\n";
        cout << "|   1) Register Patient                            |\n";
        cout << "|   2) Delete Patient                              |\n";
        cout << "|   3) Search Patient by ID                        |\n";
        cout << "|                                                  |\n";
        cout << "|   0) Back to Main Menu                           |\n";
        cout << "|                                                  |\n";
        cout << "+==================================================+\n";
        cout << "Choose an option: ";

        choice = safe_input_int(0, 3); // safe input

        switch (choice)
        {
        case 1:
            registerPatient();
            break;

        case 2:
            deletePatient();
            break;

        case 3:
            searchPatientByID();
            break;

        case 0:
            return; // go back to main menu

        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}

void HospitalSystem::doctorManagement() // this to manage doctor
{
    int choice;

    while (true)
    {
        cout << "\n";
        cout << "+==================================================+\n";
        cout << "|               DOCTOR MANAGEMENT MENU             |\n";
        cout << "+==================================================+\n";
        cout << "|                                                  |\n";
        cout << "|   1) Hire Doctor                                 |\n";
        cout << "|   2) Fire Doctor                                 |\n";
        cout << "|   3) Search Doctor by ID                         |\n";
        cout << "|   4) Search Doctor by Department                 |\n";
        cout << "|   5) Show Doctor's Patient Queue                 |\n";
        cout << "|                                                  |\n";
        cout << "|   0) Back to Main Menu                           |\n";
        cout << "|                                                  |\n";
        cout << "+==================================================+\n";
        cout << "Choose an option: ";

        choice = safe_input_int(0, 5);

        switch (choice)
        {
        case 1:
            hireDoctor();
            break;

        case 2:
            fireDoctor();
            break;

        case 3:
            searchDoctorByID();
            break;

        case 4:
            searchDoctorByDepartment();
            break;

        case 5:
            showDoctorQueue();
            break;

        case 0:
            return; // go back to main menu

        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}

void HospitalSystem::run()
{
    int choice;

    while (true)
    {
        printMainMenu();
        choice = safe_input_int(0, 8);

        switch (choice)
        {
        case 1:
            patientManagement();
            break;

        case 2:
            doctorManagement();
            break;

        case 0:
            printExitScreen();
            return;

        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}
