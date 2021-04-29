// Group project
// 4/28/2021
// Github test

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct person;
typedef person* PersonPtr;

struct person{

    string pName;
    long pSSN;

    char gender;
    string DOB;

    float height;
    float weight;

    long fSSN;
    long mSSN;

    PersonPtr next;
};

void TestFunction();
void DisplayMenu();
void InitializeList(PersonPtr&);
void DisplayList(PersonPtr);

int main(){

    PersonPtr head;
    InitializeList(head);

    cout << "County-Pop-Project" << endl << endl;
    DisplayMenu();

    bool isrunning = true;
    int userin;
    while(isrunning == true){
        cout << "Enter which menu item you would like(1, 2, 3 || 0 to quit): ";
        cin >> userin;

        switch(userin){
            case 1 :
                cout << endl;
                DisplayList(head);
            case 2 :
                cout << endl;
                TestFunction();
            case 3 :
                cout << endl;
                TestFunction();
            case 4 :
                cout << endl;
                TestFunction();
            case 5 :
                cout << endl;
                TestFunction();
            case 6 :
                cout << endl;
                TestFunction();
            case 7 :
                cout << endl;
                TestFunction();
            case 8 :
                cout << endl;
                TestFunction();
            case 9 :
                cout << endl;
                TestFunction();
            case 10 :
                cout << endl;
                TestFunction();
            case 11 :
                cout << endl;
                TestFunction();
            case 12 :
                cout << endl;
                TestFunction();
            default :
                cout << "Goodbye.";
                return 1;
        }
        cout << endl;
    }
}

void DisplayMenu(){

    cout << "Menu:" << endl
    << "1. Display the list of county residents" << endl
    << "2. Remove a person" << endl
    << "3. Add a person" << endl
    << "4. Add people to the list in bulk by reading a supplementary file containing person data" << endl
    << "5. Edit a person (user specifies one SSN and enters new details of pname, height and weight for that SSN)" << endl
    << "6. Display all persons eligible for social security (age 65 and older)" << endl
    << "7. Display all persons at high risk of cardiovascular disease (BMI 27 and higher)" << endl
    << "8. Display the male:female ratio of the population of the county (females per thousand males)" << endl
    << "9. Find the parents of a person (user supplies SSN of the person)" << endl
    << "10. Find all children of a person (user supplies SSN of the person)" << endl
    << "11. Find all siblings of a person (user supplies SSN of the person)" << endl
    << "12. Find all uncles, aunts, cousins, nephews and nieces of a person (user supplies SSN of the person)" << endl;
}

void InitializeList(PersonPtr& head){
    /* This function initializes the list of
       residents from a file at the start of the program */

    head = new person;
    head->next = NULL;
    PersonPtr current = head;
    PersonPtr newPerson;

    string fline;
    ifstream fCountyPop;
    fCountyPop.open("county-pop.txt");

    while(!fCountyPop.eof()){

        getline(fCountyPop, fline);
        current->pName = fline;
        getline(fCountyPop, fline);
        current->pSSN = stol(fline);
        getline(fCountyPop, fline);
        current->gender = fline[0];
        getline(fCountyPop, fline);
        current->DOB = fline;
        getline(fCountyPop, fline);
        current->height = stof(fline);
        getline(fCountyPop, fline);
        current->weight = stof(fline);
        getline(fCountyPop, fline);
        current->fSSN = stol(fline);
        getline(fCountyPop, fline);
        current->mSSN = stol(fline);

        newPerson = new person; // independent person
        current->next = newPerson; // linking persons
        current = newPerson;
    }
    fCountyPop.close();

    current = head;
    person* prevPerson;

    while (current->next != NULL){
        prevPerson = current;
        current = current->next;
    }

    prevPerson->next = NULL;
    delete newPerson;

    current = head;
}

void DisplayList(PersonPtr head){

    PersonPtr current = head;

    while(current != NULL) { // better way to display data - not defined size
        cout << current->pName << " | " << current->pSSN << " | "
             << current->gender << " | " << current->DOB << " | "
             << current->height << " | " << current->weight << " | "
             << current->fSSN << " | "  << current->mSSN << " | " <<  endl;
        current = current->next;
    }
}

void TestFunction(){

    cout << "testing 1 2 3";
}
