// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine
#include "HospitalSystem.h"
#include "SafeInput.h"

// ================= helper functions =================

// reading caseType
static CaseType readCaseType()
{
    cout << "Select Case Type:\n";
    cout << "  1) GENERAL\n";
    cout << "  2) EMERGENCY\n";
    cout << "  3) ICU\n";
    cout << "  4) PEDIATRIC\n";
    cout << "  5) SURGICAL\n";
    int c = safe_input_int(1, 5);
    switch (c)
    {
    case 1:
        return GENERAL;
    case 2:
        return EMERGENCY;
    case 3:
        return ICU;
    case 4:
        return PEDIATRIC;
    default:
        return SURGICAL;
    }
}
// this functions to read name with space like -> OMar Adel Youssif
static string readName()
{
    string s;
    std::getline(cin, s);
    if (s.size() == 0)
        std::getline(cin, s);
    return s;
}

string caseTypeTostring(CaseType caseType) // this to conver case type to string
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

    return caseTypeStr;
}

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

// reading line like name of patient or doctor
static string readLineTrimmed()
{
    string s;
    std::getline(cin, s);
    if (s.size() == 0)
        std::getline(cin, s);
    return s;
}

// ================= PATIENT MANAGEMENT =================
void HospitalSystem::registerPatient()
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|                REGISTER NEW PATIENT              |\n";
    cout << "+==================================================+\n";
    cout << "Enter Patient ID (integer): ";
    int id = safe_input_int(1, INT_MAX);
    if (validateId.count(id))
    {
        cout << "This Patient ID already exists! Registration cancelled.\n";
        return;
    }

    cout << "Enter Patient Name: ";
    string name = readLineTrimmed();

    cout << "Enter Age: ";
    int age = safe_input_int(0, 150);

    CaseType ct = readCaseType();

    Patient p(id, name, age, ct);

    DoctorList *list = doctorsByMajor[ct];

    if (list == nullptr || list->isEmpty())
    {
        cout << "No doctors availalbe  in the department!" << nl;
        cout << "Patient will be pushed into the WAITING LIST.\n";
        waiting.enqueue(p);
        cout << name << " added to WATTING LIST." << nl;
        return;
    }

    cout << "\n+==================================================+\n";
    cout << "|         AVAILABLE DOCTORS IN THIS DEPARTMENT     |\n";
    cout << "+==================================================+\n";
    ListNode *curr = list->getHead();
    while (curr != nullptr)
    {
        cout << "Doctor ID : " << curr->doctor.getId() << "\n";
        cout << "Name      : " << curr->doctor.getName() << "\n";
        cout << "Queue     : " << curr->Patients.getQueueCount() << " waiting\n";
        cout << "------------------------------------------\n";

        curr = curr->next;
    }
    cout << "Enter Doctor ID to assign the patient: ";
    int choId = safe_input_int(1, INT_MAX);
    ListNode *doc = list->SearchById(choId);

    if (doc == nullptr)
    {
        cout << "Invalid Doctor ID! Patient moved to WAITING LIST.\n";
        waiting.enqueue(p);
        return;
    }

    doc->Patients.enqueue(p);
    validateId[id] = p;

    cout << "\nPatient " << p.getName()
         << " assigned to Dr. " << doc->doctor.getName() << "'s queue.\n";

    cout << "+==================================================+\n";
}
void HospitalSystem::deletePatient() {}     // sanad
void HospitalSystem::searchPatientByID() {} // moza

// ================= DOCTOR MANAGEMENT =================
void HospitalSystem::hireDoctor() {}
void HospitalSystem::fireDoctor() {}
void HospitalSystem::searchDoctorByID() {}
void HospitalSystem::searchDoctorByDepartment() {}
void HospitalSystem::showDoctorQueue() {} // sanad
// ================= DOCTOR MANAGEMENT =================
void HospitalSystem::displayPatients()
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|                 ALL PATIENTS LIST                |\n";
    cout << "+==================================================+\n";

    bool found = false;
    cout << "================== ASSIGNED PATIENTS ==================\n";
    for (auto &[maj, doclist] : doctorsByMajor)
    {
        ListNode *curr = doclist->getHead();
        while (curr != nullptr)
        {
            if (!curr->Patients.isEmpty())
            {
                found = 1;
                cout << "\n--------------------Doctor Info--------------------\n";
                cout << "Major: " << caseTypeTostring(curr->doctor.getCaseType()) << nl;
                cout << "Doctor: " << curr->doctor.getName() << nl;
                cout << "ID: " << curr->doctor.getId() << nl;
                cout << "\n---------------------------------------------------\n";

                curr->Patients.display();
            }
            curr = curr->next;
        }
    }

    if (!found)
        cout << "No assigned Patients." << nl;

    cout << "\n====================== WAITING LIST ======================\n";
    if (waiting.isEmpty())
    {
        cout << "No patients in waiting list." << nl;
    }
    else
    {
        waiting.display();
    }
    cout << "\n+==================================================+\n";
}

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
