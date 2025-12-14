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
    int age = safe_input_int(1, 150);

    CaseType ct = readCaseType();

    Patient p(id, name, age, ct);

    DoctorList *list = doctorsByMajor[ct];

    if (list == nullptr || list->isEmpty())
    {
        // cout << "No doctors availalbe  in the department!" << nl;
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

void HospitalSystem::deletePatient()
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|              DELETE PATIENT BY ID                |\n";
    cout << "+==================================================+\n";

    cout << "Enter Patient ID to search: ";
    int id = safe_input_int(1, INT_MAX);

    bool found = false;

    // 1. Search in the General Waiting List (No doctor assigned yet)
    QueueNode *currP = waiting.getHead();
    if (waiting.searchPatientbool(id))
    {
        cout << "Patient " << currP->patient.getName() << " has been deleted from the Waiting list\n";
        waiting.removeById(id);
        return;
    }

    // 2. Search in every Doctor's Patient Queue
    // We iterate through every major -> every doctor -> their patient queue
    for (auto &[major, docList] : doctorsByMajor)
    {
        ListNode *currDoc = docList->getHead();
        while (currDoc != nullptr)
        {
            if (currDoc->Patients.searchPatientbool(id))
            {
                cout << "Patient " << currDoc->Patients.searchPatient(id).getName() << " has been deleted from Dr. " << currDoc->doctor.getName() << " queue\n";
                currDoc->Patients.removeById(id);
                return;
            }
        }
    }

    // 3. If the loop finishes and we haven't returned, the patient was not found
    cout << "\nPatient with ID " << id << " not found in any patient queue.\n";
    cout << "+==================================================+\n";
} // sanad

void HospitalSystem::searchPatientByID()
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|              SEARCH PATIENT BY ID                |\n";
    cout << "+==================================================+\n";

    cout << "Enter Patient ID to search: ";
    int id = safe_input_int(1, INT_MAX);

    bool found = false;

    // 1. Search in the General Waiting List (No doctor assigned yet)
    QueueNode *currP = waiting.getHead();
    while (currP != nullptr)
    {
        if (currP->patient.getId() == id)
        {
            cout << "\n+==================================================+\n";
            cout << "|               PATIENT INFORMATION                 |\n";
            cout << "+==================================================+\n";
            currP->patient.display();
            cout << "Status        : In Waiting List (Not assigned to a doctor)\n";
            cout << "+==================================================+\n";
            return;
        }
        currP = currP->next;
    }

    // 2. Search in every Doctor's Patient Queue
    // We iterate through every major -> every doctor -> their patient queue
    for (auto &[major, docList] : doctorsByMajor)
    {
        ListNode *currDoc = docList->getHead();
        while (currDoc != nullptr)
        {
            // Search inside this doctor's specific queue
            QueueNode *pNode = currDoc->Patients.getHead();
            while (pNode != nullptr)
            {
                if (pNode->patient.getId() == id)
                {
                    cout << "\n+==================================================+\n";
                    cout << "|               PATIENT INFORMATION                 |\n";
                    cout << "+==================================================+\n";
                    pNode->patient.display();
                    cout << "Status        : Assigned to Dr. " << currDoc->doctor.getName() << "\n";
                    cout << "Doctor ID     : " << currDoc->doctor.getId() << "\n";
                    cout << "+==================================================+\n";
                    return;
                }
                pNode = pNode->next;
            }
            currDoc = currDoc->next;
        }
    }

    // 3. If the loop finishes and we haven't returned, the patient was not found
    cout << "\nPatient with ID " << id << " not found in any patient queue.\n";
    // Check if it exists in the system map (meaning it might be a doctor)
    if (validateId.count(id))
    {
        cout << "(Note: This ID is registered in the system, but it likely belongs to a Doctor.)\n";
    }
    cout << "+==================================================+\n";
}

// ================= DOCTOR MANAGEMENT =================
void HospitalSystem::hireDoctor() // hire a new doctor (Omar Mohamed)
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|                   HIRE NEW DOCTOR                |\n";
    cout << "+==================================================+\n";
    cout << "Enter Doctor ID (integer): ";
    int id = safe_input_int(1, INT_MAX);
    if (validateId.count(id))
    {
        cout << "This Doctor ID already exists! Hired cancelled.\n";
        return;
    }

    cout << "Enter Doctor Name: ";
    string name = readLineTrimmed();

    cout << "Enter Age: ";
    int age = safe_input_int(18, 150);

    CaseType ct = readCaseType();

    cout << "Enter Years Of Experianece: ";
    int ex = safe_input_int(0, 80);

    Doctor dr(id, name, age, ct, ex);

    DoctorList *list = doctorsByMajor[ct];

    list->addDoctor(dr);

    validateId[id] = dr;

    cout << "\nDoctor " << name << " Is Hired Successfully.\n";

    cout << "+==================================================+\n";
}

void HospitalSystem::fireDoctor() // fire a doctor with id (Omar Mohamed)
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|                    FIRE A DOCTOR                 |\n";
    cout << "+==================================================+\n";
    cout << "Enter Doctor ID (integer): ";
    int id = safe_input_int(1, INT_MAX);
    if (validateId.count(id) == 0)
    {
        cout << "Invalid Id, Please Enter a Correct Doctor Id!\n";
        return;
    }

    Person dr = validateId[id];
    CaseType ct = dr.getCaseType();
    DoctorList *list = doctorsByMajor[ct];

    if (list->isEmpty() || list->SearchById(id) == nullptr)
    {
        cout << "Invalid Id, Please Enter a Correct Doctor Id!\n";
        return;
    }
    else
    {
        list->deleteById(id);
        cout << "\nDoctor " << dr.getName() << " Is Fired.\n";
        validateId.erase(id);
    }

    cout << "+==================================================+\n";
}

void HospitalSystem::searchDoctorByID() {}
void HospitalSystem::searchDoctorByDepartment() {}
void HospitalSystem::showDoctorQueue()
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|                 Show Doctor's queue              |\n";
    cout << "+==================================================+\n";
    cout << "Enter Doctor ID (integer): ";
    int id = safe_input_int(1, INT_MAX);
    if (validateId.count(id) == 0)
    {
        cout << "Invalid Id, Please Enter a Correct Doctor Id!\n";
        return;
    }

    Person dr = validateId[id];
    CaseType ct = dr.getCaseType();
    DoctorList *list = doctorsByMajor[ct];

    if (list->isEmpty() || list->SearchById(id) == nullptr)
    {
        cout << "Invalid Id, Please Enter a Correct Doctor Id!\n";
        return;
    }
    else
    {
        ListNode *curr = list->getHead();
        while (curr != nullptr)
        {
            if (curr->doctor.getId() == id)
            {
                cout << "Doctor ID : " << curr->doctor.getId() << "\n";
                cout << "Name      : " << curr->doctor.getName() << "\n";
                cout << "\n+=============== Doctor's queue ===============+\n";
                if (curr->Patients.getQueueCount() == 0)
                {
                    cout << "No patients on this doctor's queue\n";
                }
                else
                {
                    QueueNode *Node = curr->Patients.getHead();
                    cout << "| "
                         << left << setw(5) << "ID"
                         << "| " << setw(20) << "Name"
                         << "| " << setw(5) << "Age"
                         << '\n';
                    cout << "+----------------------------+";
                    while (Node != nullptr)
                    {
                        cout << "| "
                             << left << setw(5) << Node->patient.getId()
                             << "| " << setw(20) << Node->patient.getName()
                             << "| " << setw(5) << Node->patient.getAge()
                             << '\n';
                        Node = Node->next;
                    }
                }
            }
        }
    }
    cout << "+==================================================+\n";
} // sanad
// ================= General =================
void HospitalSystem::displayPatients()
{

    cout << "\n+===============================================================================================================+\n";
    cout << "|                                              PATIENTS TABLE                                                  |\n";
    cout << "+===============================================================================================================+\n";

    // Table Header
    cout << "| "
         << left << setw(5) << "ID"
         << "| " << setw(20) << "Name"
         << "| " << setw(5) << "Age"
         << "| " << setw(12) << "Major"
         << "| " << setw(20) << "Assigned Doctor"
         << "| " << setw(12) << "Doctor ID"
         << "| " << setw(10) << "Status"
         << "|\n";

    cout << "+---------------------------------------------------------------------------------------------------------------+\n";

    bool found = false;

    for (auto &[maj, doclist] : doctorsByMajor)
    {
        ListNode *curr = doclist->getHead();

        while (curr != nullptr)
        {
            QueueNode *p = curr->Patients.getHead();

            while (p != nullptr)
            {
                found = true;

                cout << "| "
                     << left << setw(5) << p->patient.getId()
                     << "| " << setw(20) << p->patient.getName()
                     << "| " << setw(5) << p->patient.getAge()
                     << "| " << setw(12) << caseTypeTostring(p->patient.getCaseType())
                     << "| " << setw(20) << curr->doctor.getName()
                     << "| " << setw(12) << curr->doctor.getId()
                     << "| " << setw(10) << "Assigned"
                     << "|\n";

                p = p->next;
            }

            curr = curr->next;
        }
    }

    if (!found)
    {
        cout << "|                                        No assigned patients found.                                           |\n";
    }

    if (!waiting.isEmpty())
    {
        QueueNode *p = waiting.getHead();

        while (p != nullptr)
        {
            cout << "| "
                 << left << setw(5) << p->patient.getId()
                 << "| " << setw(20) << p->patient.getName()
                 << "| " << setw(5) << p->patient.getAge()
                 << "| " << setw(12) << caseTypeTostring(p->patient.getCaseType())
                 << "| " << setw(20) << "---"
                 << "| " << setw(12) << "---"
                 << "| " << setw(10) << "Waiting"
                 << "|\n";

            p = p->next;
        }
    }

    cout << "+===============================================================================================================+\n";
    // we can also use display function which in Queue and LinkedList but this way is more formal
}

void HospitalSystem::displayDoctors()
{
    cout << "\n+====================================================================================================+\n";
    cout << "|                                         DOCTORS TABLE                                              |\n";
    cout << "+====================================================================================================+\n";

    cout << "| "
         << left << setw(5) << "ID"
         << "| " << setw(20) << "Name"
         << "| " << setw(5) << "Age"
         << "| " << setw(12) << "Major"
         << "| " << setw(10) << "Patients"
         << "| " << setw(17) << "Experience (yrs)"
         << "| " << setw(12) << "Salary"
         << "|\n";

    cout << "+----------------------------------------------------------------------------------------------------+\n";

    bool found = false;

    for (auto &[major, doclist] : doctorsByMajor)
    {
        ListNode *curr = doclist->getHead();

        while (curr != nullptr)
        {
            found = true;

            cout << "| "
                 << left << setw(5) << curr->doctor.getId()
                 << "| " << setw(20) << curr->doctor.getName()
                 << "| " << setw(5) << curr->doctor.getAge()
                 << "| " << setw(12) << caseTypeTostring(curr->doctor.getCaseType())
                 << "| " << setw(10) << curr->Patients.getQueueCount()
                 << "| " << setw(17) << curr->doctor.getYearsOfExperience()
                 << "| " << setw(12) << curr->doctor.getSal()
                 << "|\n";

            curr = curr->next;
        }
    }

    if (!found)
    {
        cout << "|                                   No doctors found in system.                                     |\n";
    }

    cout << "+====================================================================================================+\n";

    // we can also use display function which on list of doctors but this is more formal
}

void HospitalSystem::patientsCount()
{
    int assigned = 0;
    int waitingCnt = waiting.getQueueCount();
    for (auto &[maj, docList] : doctorsByMajor)
    {
        ListNode *curr = docList->getHead();
        while (curr != nullptr)
        {
            assigned += curr->Patients.getQueueCount();
            curr = curr->next;
        }
    }

    int total = assigned + waitingCnt;
    cout << "\n+==================================================+\n";
    cout << "|                PATIENTS COUNT SUMMARY            |\n";
    cout << "+==================================================+\n";
    cout << "Assigned Patients : " << assigned << "\n";
    cout << "Waiting Patients  : " << waitingCnt << "\n";
    cout << "----------------------------------------------------\n";
    cout << "Total Patients    : " << total << "\n";
    cout << "+==================================================+\n";
}

void HospitalSystem::doctorsCount()
{
    int general = 0, emergency = 0, icu = 0, pediatric = 0, surgical = 0;

    if (doctorsByMajor.count(GENERAL))
        general = doctorsByMajor[GENERAL]->getCount();
    if (doctorsByMajor.count(EMERGENCY))
        emergency = doctorsByMajor[EMERGENCY]->getCount();
    if (doctorsByMajor.count(ICU))
        icu = doctorsByMajor[ICU]->getCount();
    if (doctorsByMajor.count(PEDIATRIC))
        pediatric = doctorsByMajor[PEDIATRIC]->getCount();
    if (doctorsByMajor.count(SURGICAL))
        surgical = doctorsByMajor[SURGICAL]->getCount();

    int total = general + emergency + icu + pediatric + surgical;

    cout << "\n+==================================================+\n";
    cout << "|                 DOCTORS COUNT SUMMARY            |\n";
    cout << "+==================================================+\n";
    cout << "GENERAL Doctors    : " << general << "\n";
    cout << "EMERGENCY Doctors  : " << emergency << "\n";
    cout << "ICU Doctors        : " << icu << "\n";
    cout << "PEDIATRIC Doctors  : " << pediatric << "\n";
    cout << "SURGICAL Doctors   : " << surgical << "\n";
    cout << "----------------------------------------------------\n";
    cout << "Total Doctors      : " << total << "\n";
    cout << "+==================================================+\n";
}

void HospitalSystem::treatPatient() {} // Omar adel
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
