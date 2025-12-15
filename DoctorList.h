// بسم الله الرحمن الرحيم
// "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
// Free Palestine
#ifndef DOCTORLIST_H
#define DOCTORLIST_H

#include <bits/stdc++.h>
#include "PatientQueue.h"
#include "Doctor.h"
using namespace std;

class ListNode
{
public:
    Doctor doctor;         // Doctor object
    PatientQueue Patients; // Queue of patients for this doctor
    ListNode *next;        // pointer to next node

    ListNode(const Doctor &d) : doctor(d), next(nullptr) {}
};

class DoctorList
{
private:
    ListNode *head;
    ListNode *tail;
    int DoctorsCount; // number of doctors

public:
    DoctorList() : head(nullptr), tail(nullptr), DoctorsCount(0) {}
    ~DoctorList()
    {
        clear();
    }

    ListNode *getHead()
    {
        return head;
    }

    void addDoctor(const Doctor &doctor)
    {
        ListNode *newNode = new ListNode(doctor);
        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        DoctorsCount++;
    }

    ListNode *SearchById(int DoctorId)
    {
        ListNode *curr = head;

        while (curr != nullptr)
        {
            if (curr->doctor.getId() == DoctorId)
            {
                return curr; // return the whole doctor node
            }
            curr = curr->next;
        }

        return nullptr;
    }

    void deleteHead() // Support other delete methods (Omar Mohamed)
    {
        if (isEmpty())
        {
            return;
        }
        else if (DoctorsCount == 1)
        {
            delete head;
            head = tail = nullptr;
            DoctorsCount--;
        }
        else
        {
            ListNode *curr = head;
            head = head->next;
            delete curr;
            DoctorsCount--;
        }
    }

    Doctor deleteById(int DoctorId) // delete doctor from list with ID (Omar Mohamed)
    {
        if (isEmpty())
        {
            cout << "There Is No Doctors To Delete!" << nl;
            return Doctor();
        }
        else
        {
            if (SearchById(DoctorId) == nullptr)
            {
                cout << "Invalid Id, Please Enter a Correct Doctor Id!\n";
                return Doctor();
            }
            else
            {
                if (head->doctor.getId() == DoctorId)
                {
                    Doctor temp = head->doctor;
                    deleteHead();
                    return temp;
                }
                else
                {
                    ListNode *delNode = head;
                    ListNode *prev = head;
                    while (prev->next->doctor.getId() != DoctorId)
                    {
                        prev = prev->next;
                    }
                    Doctor temp = prev->next->doctor;
                    delNode = prev->next;
                    prev->next = delNode->next;
                    delete delNode;
                    DoctorsCount--;
                    return temp;
                }
            }
        }
    }

    int doctorPatientCount(int DoctorId) // return the count of patients for a doctor that have this id (-MoRa-)
    {
        if (isEmpty())
        {
            cout << "Invalid Id, Please Enter a Correct Doctor Id!" << nl;
            return 0;
        }
        else
        {
            if (SearchById(DoctorId) == nullptr)
            {
                cout << "Invalid Id, Please Enter a Correct Doctor Id!\n";
                return 0;
            }
            else
            {
                if (head->doctor.getId() == DoctorId)
                {
                    return head->Patients.getQueueCount();
                }
                else
                {
                    ListNode *curr = head;
                    while (curr->doctor.getId() != DoctorId)
                    {
                        curr = curr->next;
                    }
                    return curr->Patients.getQueueCount();
                }
            }
        }
    }

    void display() // This function display doctors queue
    {
        if (isEmpty())
        {
            cout << "There is no Doctors." << nl;
            return;
        }
        else
        {
            ListNode *curr = head;
            while (curr != nullptr)
            {
                cout << "Doctor ID : " << curr->doctor.getId() << "\n";
                cout << "Name      : " << curr->doctor.getName() << "\n";
                cout << "Queue     : " << curr->Patients.getQueueCount() << " waiting\n";
                cout << "------------------------------------------\n";
                curr = curr->next;
            }
        }
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    int getCount() const
    {
        return DoctorsCount;
    }

    void clear()
    {
        while (head != nullptr)
        {
            ListNode *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        DoctorsCount = 0;
    }
};

#endif