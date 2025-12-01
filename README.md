# "وَأَنْ لَيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ"
# patient-management-System

![alt text](</UML/Untitled Diagram.drawio.png>)

--------------------------------------------------

This Patient class manages patient records in a hospital system:
What it does:

Stores patient data: ID, name, age, and case type (GENERAL, EMERGENCY, ICU, PEDIATRIC, or SURGICAL)
Creates patients: Through default constructor (empty patient) or parameterized constructor (with specific details)
Displays patient info: display() method prints all patient details in a formatted way, converting the case type enum to readable text
Provides controlled access:

Getters retrieve individual attributes (getId, getName, getAge, getCaseType)
Setters modify data safely - setAge() includes validation to prevent negative ages


Ensures data encapsulation: Private members are only accessible through public methods, protecting data integrity

In essence: It's a blueprint for creating and managing individual patient objects with proper data hiding and controlled access to patient information.