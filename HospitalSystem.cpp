// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine
#include "HospitalSystem.h"
#include "SafeInput.h"

// ================= helper functions =================

static CaseType readCaseType() // reading caseType
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

static string readName() // this functions to read name with space like -> OMar Adel Youssif

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

    for (auto const &[key, listPtr] : doctorsByMajor)
    {
        delete listPtr;
    }
}

static string readLineTrimmed() // reading line like name of patient or doctor
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
    validateId[id] = p;

    DoctorList *list = doctorsByMajor[ct];

    if (list == nullptr || list->isEmpty())
    {
        // cout << "No doctors availalbe  in the department!" << nl;
        cout << "Patient will be pushed into the WAITING LIST.\n";
        waiting.enqueue(p);
        cout << name << " added to WATTING LIST." << nl;
        return;
    }
}

void HospitalSystem::deletePatient()
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|              DELETE PATIENT BY ID                |\n";
    cout << "+==================================================+\n";

    cout << "Enter Patient ID to search: ";
    int id = safe_input_int(1, INT_MAX);

    if (!validateId.count(id))
    {
        cout << "this id is not found!";
        return;
    }

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

    validateId.erase(id);

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
            cout << "Status: In Waiting List (Not assigned to a doctor)\n";
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
// In HospitalSystem.cpp

void HospitalSystem::assignPatientFromWaiting()
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|         ASSIGN PATIENT FROM WAITING LIST         |\n";
    cout << "+==================================================+\n";

    // 1. Check if waiting list has patients
    if (waiting.isEmpty())
    {
        cout << "The waiting list is empty. No patients to assign.\n";
        cout << "+==================================================+\n";
        return;
    }

    // 2. Display patients currently in waiting
    cout << "--- Current Waiting List ---\n";
    waiting.display();

    // 3. Select Patient
    cout << "Enter Patient ID to assign: ";
    int pId = safe_input_int(1, INT_MAX);

    // Verify patient exists in waiting list
    if (!waiting.searchPatientbool(pId))
    {
        cout << "Patient ID " << pId << " not found in the waiting list.\n";
        return;
    }

    // 4. Retrieve patient info to identify their CaseType (Major)
    Patient tempP = waiting.searchPatient(pId);
    CaseType requiredMajor = tempP.getCaseType();

    // 5. Get the Doctor list for this major
    DoctorList *docList = doctorsByMajor[requiredMajor];

    if (docList == nullptr || docList->isEmpty())
    {
        cout << "\nERROR: No doctors available in " << caseTypeTostring(requiredMajor) << " department.\n";
        cout << "Cannot assign this patient at the moment.\n";
        return;
    }

    // 6. Show available doctors
    cout << "\nAvailable Doctors in " << caseTypeTostring(requiredMajor) << " Department:\n";
    docList->display();

    // 7. Select Doctor
    cout << "Enter Doctor ID to assign the patient to: ";
    int dId = safe_input_int(1, INT_MAX);

    ListNode *docNode = docList->SearchById(dId);

    if (docNode == nullptr)
    {
        cout << "Invalid Doctor ID. Assignment cancelled.\n";
        return;
    }

    // 8. PERFORM THE MOVE
    // Remove from waiting list and get the object
    Patient pToMove = waiting.removeById(pId);

    // Enqueue to the specific doctor's queue
    docNode->Patients.enqueue(pToMove);

    cout << "\nSUCCESS: Patient " << pToMove.getName()
         << " (ID: " << pId << ") has been moved from Waiting List\n"
         << "to Dr. " << docNode->doctor.getName() << "'s queue.\n";

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
        cout << "This Doctor ID already exists! Hiring cancelled.\n";
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
    else if (list->doctorPatientCount(id) != 0)
    {
        cout << "This Doctor Has a Patients, Can’t Be Fired Now!\n";
    }
    else
    {
        list->deleteById(id);
        cout << "\nDoctor " << dr.getName() << " Is Fired.\n";
        validateId.erase(id);
    }

    cout << "+==================================================+\n";
}

void HospitalSystem::searchDoctorByID()
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|              SEARCH DOCTOR BY ID                 |\n";
    cout << "+==================================================+\n";

    cout << "Enter Doctor ID to search: ";
    int id = safe_input_int(1, INT_MAX);

    // 1. Check if ID exists in the global system
    if (validateId.count(id) == 0)
    {
        cout << "\nID " << id << " not found in the system.\n";
        cout << "+==================================================+\n";
        return;
    }

    // 2. Retrieve basic Person info to find their Department (Major)
    Person p = validateId[id];
    CaseType ct = p.getCaseType();

    // 3. Search in the specific DoctorList for that department
    DoctorList *list = doctorsByMajor[ct];
    ListNode *node = list->SearchById(id);

    if (node != nullptr)
    {
        cout << "\n+==================================================+\n";
        cout << "|               DOCTOR INFORMATION                 |\n";
        cout << "+==================================================+\n";
        cout << "ID                 : " << node->doctor.getId() << "\n";
        cout << "Name               : " << node->doctor.getName() << "\n";
        cout << "Age                : " << node->doctor.getAge() << "\n";
        cout << "Department         : " << caseTypeTostring(node->doctor.getCaseType()) << "\n";
        cout << "Years of Exp       : " << node->doctor.getYearsOfExperience() << "\n";
        cout << "Salary             : " << node->doctor.getSal() << "\n";
        cout << "Patients in Queue  : " << node->Patients.getQueueCount() << "\n";
        cout << "+==================================================+\n";
    }
    else
    {
        // If the ID exists in validateId but isn't in a DoctorList, it must be a Patient
        cout << "\nID " << id << " is registered but belongs to a Patient, not a Doctor.\n";
        cout << "+==================================================+\n";
    }
}

void HospitalSystem::searchDoctorByDepartment()
{
    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|           SEARCH DOCTORS BY DEPARTMENT           |\n";
    cout << "+==================================================+\n";

    // 1. Read the department using existing helper
    CaseType ct = readCaseType();

    DoctorList *list = doctorsByMajor[ct];

    if (list->isEmpty())
    {
        cout << "\nNo doctors found in " << caseTypeTostring(ct) << " department.\n";
        cout << "+==================================================+\n";
        return;
    }

    // 2. Display Table Header
    cout << "\nDoctors in " << caseTypeTostring(ct) << " Department:\n";
    cout << "+------------------------------------------------------------------------------------+\n";
    cout << "| " << left << setw(5) << "ID"
         << "| " << setw(20) << "Name"
         << "| " << setw(5) << "Age"
         << "| " << setw(15) << "Experience"
         << "| " << setw(15) << "Patients Queue" << "|\n";
    cout << "+------------------------------------------------------------------------------------+\n";

    ListNode *curr = list->getHead();
    while (curr != nullptr)
    {
        cout << "| " << left << setw(5) << curr->doctor.getId()
             << "| " << setw(20) << curr->doctor.getName()
             << "| " << setw(5) << curr->doctor.getAge()
             << "| " << setw(15) << curr->doctor.getYearsOfExperience()
             << "| " << setw(15) << curr->Patients.getQueueCount() << "|\n";
        curr = curr->next;
    }
    cout << "+------------------------------------------------------------------------------------+\n";
}

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
                    cout << "________________________________________________\n";
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
                return;
            }
            curr = curr->next;
        }
    }
    cout << "+==================================================+\n";
}

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

void HospitalSystem::treatPatients()
{

    for (auto &[maj, list] : doctorsByMajor)
    {
        ListNode *curDoc = list->getHead();
        while (curDoc != nullptr)
        {
            if (curDoc->Patients.getQueueCount() > 0)
            {
                int patientId = curDoc->Patients.dequeue().getId();
                validateId.erase(patientId);
            }
        }
    }

    cout << "\n";
    cout << "+==================================================+\n";
    cout << "|      The treatment process is successful.        |\n";
    cout << "+==================================================+\n";
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
    cout << "|   4) doctors Count                               |\n";
    cout << "|   5) Patient Count                               |\n";
    cout << "|   6) display All doctors                         |\n";
    cout << "|   7) display All patients                        |\n";
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
// In HospitalSystem.cpp

void HospitalSystem::patientManagement()
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
        cout << "|   4) Assign Patient from Waiting List            |\n";
        cout << "|                                                  |\n";
        cout << "|   0) Back to Main Menu                           |\n";
        cout << "|                                                  |\n";
        cout << "+==================================================+\n";
        cout << "Choose an option: ";

        choice = safe_input_int(0, 4);

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

        case 4:
            assignPatientFromWaiting();
            break;

        case 0:
            return;

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
        case 3:
            treatPatients();
            break;
        case 4:
            doctorsCount();
            break;
        case 5:
            patientsCount();
            break;
        case 6:
            displayDoctors();
            break;
        case 7:
            displayPatients();
            break;

        case 0:
            printExitScreen();
            return;

        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}
