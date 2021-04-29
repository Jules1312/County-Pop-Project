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
                break;
            case 2 :
                cout << endl;
                TestFunction();
                break;
            case 3 :
                cout << endl;
                TestFunction();
                break;
            case 4 :
                cout << endl;
                TestFunction();
                break;
            case 5 :
                cout << endl;
                TestFunction();
                break;
            case 6 :
                cout << endl;
                TestFunction();
                break;
            case 7 :
                cout << endl;
                TestFunction();
                break;
            case 8 :
                cout << endl;
                TestFunction();
                break;
            case 9 :
                cout << endl;
                TestFunction();
                break;
            case 10 :
                cout << endl;
                TestFunction();
                break;
            case 11 :
                cout << endl;
                TestFunction();
                break;
            case 12 :
                cout << endl;
                TestFunction();
                break;
            default :
                cout << "Goodbye.";
                isrunning = false;
                break;
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
    PersonPtr future = NULL;
    PersonPtr past = current;
    PersonPtr temp = current;
    bool first = true ;

    // Sorts the list into ascending order
    while(temp != NULL) {

        future = current->next;
        first = true;
        while(future != NULL) {
            if(current->pSSN > future->pSSN) {
                if(current == temp){
                    temp = future ; // 1/2/3  so 1/3/2 it makes temp 3 in the 2 position
                }
                if(first == true){
                    past = current->next; // move past up one position
                    head = current->next; // set head to the top
                    current->next = future->next; // current points ahead 2 1/2/3/4 to 1/3/2/4 -- 3 to 2
                    future->next = current; // future points back one 3 to 2  ^^^^
                    first = false; // only for head

                }
                else{
                    past->next = future; //   1/2/4/3 so 2 points to 4
                    past = future; // move past up one position for next loop
                    current->next = future->next; // current points ahead two 1/2/4/3 so 2 points to 4
                    future->next = current; //roll future forward for next loop

                }
            }
            else{
                past = current; // roll forward one if not swapped 1/2/3/4  2 position becomes 3
                current = future; // roll forward one as well
                first = false; // in case we dont swap 1/2
            }
            future = current->next; //
        }
        current = head;
        temp = temp->next;
    }

    current = head;
    cout << endl;

    // Displays a list of persons of indefinite size
    while(current != NULL){
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
