// It is a project!

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
void InitializeList(PersonPtr&, string);
void DisplayList(PersonPtr);
void DisplayHighBMI(PersonPtr);
void RemovePerson(PersonPtr&, long);
void AddPersonsFromFile(PersonPtr&, string);
void AddPersonFromUser(PersonPtr&);
void EditPerson(PersonPtr, long) ;
float CalcBMI(float, float);

int main(){

    PersonPtr head;
    string filename = "county-pop.txt";
    InitializeList(head, filename);

    cout << "County-Pop-Project" << endl << endl;
    DisplayMenu();

    bool isrunning = true;
    int userin;
    long inputSSN ;
    string inputFilename ;
    
    while(isrunning == true){
        cout << "Enter which menu item you would like(1, 2, 3 || 0 to quit and 13 to see the menu again): ";
        cin >> userin;

        switch(userin){
            case 0 :
                cout << endl << "Goodbye.";
                isrunning = false;
                break ;
            case 1 :
                cout << endl;
                DisplayList(head);
                break;
            case 2 :
                cout << endl << "Please enter the SSN of the person you would like to delete: " ;
                cin >> inputSSN ;
                RemovePerson(head, inputSSN);
                break;
            case 3 :
                cout << endl ;
                AddPersonFromUser(head) ;
                break;
            case 4 :
                cout << endl << "Please enter the file name: " ;
                cin >> inputFilename ;
                AddPersonsFromFile(head, inputFilename);
                break;
            case 5 :
                cout << endl << "Please enter the SSN of the person you would like to edit: ";
                cin >> inputSSN ;
                EditPerson(head, inputSSN) ;
                break;
            case 6 :
                cout << endl;
                TestFunction();
                break;
            case 7 :
                cout << endl;
                DisplayHighBMI(head);
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
            case 13 :
                cout << endl ;
                DisplayMenu() ;
                break ;
            default :
                cout << endl << "That is not a valid menu option. Please try again." << endl ;
        }
        cout << endl;
    }
    return 0 ;
}

void DisplayMenu(){

    cout << "Menu:" << endl
    << "0. To quit." << endl
    << "1. Display the list of people in order of ascending SSN" << endl
    << "2. Remove a person from the list" << endl
    << "3. Add a person to the list" << endl
    << "4. Add people to the list in bulk by reading a supplementary file containing person data" << endl
    << "5. Edit a person (you specify one SSN and enter new details for pname, height and weight)" << endl
    << "6. Display all persons eligible for social security (age 65 and older)" << endl
    << "7. Display all persons at high risk of cardiovascular disease (BMI 27 and higher)" << endl
    << "8. Display the male:female ratio of the people in the list" << endl
    << "9. Find the parents of a person (you supply SSN of the person)" << endl
    << "10. Find all children of a person (you supply SSN of the person)" << endl
    << "11. Find all siblings of a person (you supply SSN of the person)" << endl
    << "12. Find all uncles, aunts, cousins, nephews and nieces of a person (you supply SSN of the person)" << endl;
}

void InitializeList(PersonPtr& head, string filename){
    /* This function initializes the list of
       residents from a file at the start of the program */

    head = new person;
    head->next = NULL;
    PersonPtr current = head;
    PersonPtr newPerson;

    string fline;
    ifstream fCountyPop;
    fCountyPop.open(filename);

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
    
}

void DisplayList(PersonPtr head){

    PersonPtr current = head;
    
    cout << endl;

    // Displays a list of persons of indefinite size
    while(current != NULL){
        cout << current->pName << " | " << current->pSSN << " | "
             << current->gender << " | " << current->DOB << " | "
             << current->height << " | " << current->weight << " | "
             << current->fSSN << " | "  << current->mSSN << " | " <<  endl;
        current = current->next;
    }
    current = head;
}

float CalcBMI(float height, float weight){
    return (weight / (height * height)) * 703;
}

void DisplayHighBMI(PersonPtr head){

    // Counts the persons in the list with high BMIs
    int pcount;
    PersonPtr current = head;

    while(current != NULL){
        if(CalcBMI(current->height, current->weight) > 27){
            pcount++;
            current = current->next;
        }
        else
            current = current->next;
    }
    current = head;

    // Creates a person array to store those with high BMIs
    person personary[pcount];
    int i = 0;

    while(current != NULL){
        if(CalcBMI(current->height, current->weight) > 27){
            personary[i] = *current;
            i++;
            current = current->next;
        }
        else
            current = current->next;
    }
    current = head;

    // Sorts the person array into ascending order
    person tmp;
    for(int i = 0; i < pcount; i++){
        for(int x = 1; x < pcount; x++){
            if(CalcBMI(personary[x].height, personary[x].weight) < CalcBMI(personary[x - 1].height, personary[x - 1].weight)){
                tmp = personary[x];
                personary[x] = personary[x - 1];
                personary[x - 1] = tmp;
            }
        }
    }

    // Displays the person array
    cout << "List of those at high risk of cardiovascular disease: " << endl;
    for(int x = 0; x < pcount; x++){
        cout << personary[x].pName << " BMI: "
             << CalcBMI(personary[x].height, personary[x].weight)
             << endl;

    }
}

void TestFunction(){

    cout << "testing 1 2 3";
}

void RemovePerson(PersonPtr& head, long pSSN) {
    
    bool first = true ;
    PersonPtr future ;
    PersonPtr current = head ;
    string retry ;
    while (true) {
        future = current -> next ;
        if (future->pSSN == pSSN) {
            if (future->next == NULL) {
                current -> next = NULL ; // LAST 1/2/3 - remove 3 then 2 points to NULL
                delete future ;
                break ;
            }
            else {
                current -> next = future -> next ; // MID 1/2/3 - remove 2 and then 1 points to 3
                delete future ;
                break ;
            }
        }
        if ((current->pSSN == pSSN) && (first == true)) {
            head = future ;
            delete current ; // FIRST 1/2/3 - remove 1 and 2 becomes head
            break ;
        }
        if (future->next == NULL) {
            cin.ignore() ;
            cout << "That is not a valid SSN. Please try again." ;
            cout << endl << "SSN: " ;
            getline(cin, retry) ; 
            pSSN = stol(retry) ;
            current = head ;
        }
        current = current -> next ;
        first = false ;
    }
    
    current = head ;
    cout << endl ;
    
    while (current != NULL) { // better way to display data - not defined size
        cout << current -> pName << " | " << current -> pSSN << " | " 
                << current -> gender << " | " << current -> DOB << " | " 
                << current -> height << " | " << current -> weight << " | " 
                << current -> fSSN << " | "  << current -> mSSN << " | " <<  endl ;
        current = current -> next ;
    }
    
}

void AddPersonsFromFile(PersonPtr& head, string ogFile){


    PersonPtr current = head ;
    PersonPtr newPerson = NULL ;
    PersonPtr future = current -> next ;
    string fLine ;
    
    ifstream fNew;
    fNew.open(ogFile);
    
    while (!fNew.eof()) { 
        
        newPerson = new person ;
        
        getline( fNew, fLine) ; 
        newPerson -> pName = fLine ;
        getline( fNew, fLine) ; 
        newPerson -> pSSN = stol(fLine) ;
        getline( fNew, fLine) ; 
        newPerson -> gender = fLine[0] ;
        getline( fNew, fLine) ; 
        newPerson -> DOB = fLine ;
        getline( fNew, fLine) ; 
        newPerson -> height = stof(fLine) ;
        getline( fNew, fLine) ; 
        newPerson -> weight = stof(fLine) ;
        getline( fNew, fLine) ; 
        newPerson -> fSSN = stol(fLine) ;
        getline( fNew, fLine) ; 
        newPerson -> mSSN = stol(fLine) ;
        
        bool first = true ;
        bool loop = true ;
        current = head ;
        while (loop == true) {
            future = current -> next ;
            if (future == NULL) { // add userPerson to end of list
                current -> next = newPerson ; // xxx/current/future/userPerson
                newPerson -> next = NULL ;
                loop = false ;
            }
            else { 
                if (future->pSSN > newPerson->pSSN) {
                    if (first == true) {
                        if (current->pSSN > newPerson->pSSN) {
                            head = newPerson ; // add userPerson to start of list - new head
                            newPerson -> next = current ; // userPerson/current/future/xxx
                            loop = false ;
                        }
                        else {
                            current -> next = newPerson ; // put userPerson in between position 1 and 2
                            newPerson -> next = future ;  // current/userPerson/future/xxx
                            loop = false ;
                        }   
                    }
                    else {  
                        current -> next = newPerson ; // not the first pass but xxx/current/userPerson/future/xxx
                        newPerson -> next = future ;
                        loop = false ;
                    }
                }
                else { 
                    if (future->pSSN == newPerson->pSSN) { // idk how you can have the same SSN but whatever
                        current -> next = newPerson ; // xx/5(Current)/5(UsPer)/future
                        newPerson -> next = future ;
                        loop = false ;
                    }
                current = current -> next ; // move down the list
                }
            }
            first = false ;
        }
        
        
    }
    fNew.close() ;
    
    current = head ;
    cout << endl ;
    while (current != NULL) { 
        cout << current -> pName << " | " << current -> pSSN << " | " 
                << current -> gender << " | " << current -> DOB << " | " 
                << current -> height << " | " << current -> weight << " | " 
                << current -> fSSN << " | "  << current -> mSSN << " | " <<  endl ;
        current = current -> next ;
    }
}

void AddPersonFromUser(PersonPtr& head) {
    
    PersonPtr current = head ;
    PersonPtr newPerson = NULL ;
    PersonPtr future = current -> next ;
    string fLine ;
    PersonPtr userPerson = new person ;
    
    cin.ignore() ; // skips the name input without this
    cout << "Please enter the information for the person you would like to add." << endl ;
    cout << endl << "Name:" ;
    getline(cin, fLine) ; 
    userPerson -> pName = fLine ; 
    cout << endl << "SSN: " ;
    getline(cin, fLine) ; 
    userPerson -> pSSN = stol(fLine) ;
    cout << "Gender(M/F): " ;
    getline(cin, fLine) ; 
    userPerson -> gender = fLine[0] ;
    cout << "Date of birth(YYYY/MM/DD): " ;
    getline(cin, fLine) ; 
    userPerson -> DOB = fLine ;
    cout << "Height(in inches): " ;
    getline(cin, fLine) ; 
    userPerson -> height = stof(fLine) ;
    cout << "Weight(in pounds): " ;
    getline(cin, fLine) ; 
    userPerson -> weight = stof(fLine) ;
    cout << "Father's SSN: " ;
    getline(cin, fLine) ; 
    userPerson -> fSSN = stol(fLine) ;
    cout << "Mother's SSN: " ;
    getline(cin, fLine) ; 
    userPerson -> mSSN = stol(fLine) ;
    
    bool first = true ;
    while (future != NULL) {
        future = current -> next ;
        if (future == NULL) { // add userPerson to end of list
            current -> next = userPerson ; // xxx/current/future/userPerson
            userPerson -> next = NULL ;
            break ;
        }
        else { 
            if (future->pSSN > userPerson->pSSN) {
                if (first == true) {
                    if (current->pSSN > userPerson->pSSN) {
                        head = userPerson ; // add userPerson to start of list - new head
                        userPerson -> next = current ; // userPerson/current/future/xxx
                        break ;
                    }
                    else {
                    current -> next = userPerson ; // put userPerson in between position 1 and 2
                    userPerson -> next = future ;  // current/userPerson/future/xxx
                    break ;
                    }
                }
                else {  
                    current -> next = userPerson ; // not the first pass but xxx/current/userPerson/future/xxx
                    userPerson -> next = future ;
                    break ;
                }
            }
            else { 
                if (future->pSSN == userPerson->pSSN) { // idk how you can have the same SSN but whatever
                    current -> next = userPerson ; // xx/5(Current)/5(UsPer)/future
                    userPerson -> next = future ;
                    break ;
                }
                current = current -> next ; // move down the list
            }
        }
        first = false ;
    }
    current = head ;
    cout << endl ;
    
    while (current != NULL) { 
        cout << current -> pName << " | " << current -> pSSN << " | " 
                << current -> gender << " | " << current -> DOB << " | " 
                << current -> height << " | " << current -> weight << " | " 
                << current -> fSSN << " | "  << current -> mSSN << " | " <<  endl ;
        current = current -> next ;
    }
}

void EditPerson(PersonPtr head, long inputSSN) {
    
    PersonPtr current = head ;
    PersonPtr future = current -> next ;
    string fLine ;
    
    while(current != NULL) {
        if (inputSSN == current->pSSN) {
            cout << endl << current -> pName << " | " << current -> pSSN << " | " 
                << current -> gender << " | " << current -> DOB << " | " 
                << current -> height << " | " << current -> weight << " | " 
                << current -> fSSN << " | "  << current -> mSSN << " | " <<  endl ;
            
            cin.ignore() ;  
            cout << endl << "Please enter the new name:" ;
            getline(cin, fLine) ;
            current -> pName = fLine ;
            cout << endl << "Please enter the new height:" ;
            getline(cin, fLine) ;
            current -> height = stof(fLine) ;
            cout << endl << "Please enter the new weight:" ;
            getline(cin, fLine) ;
            current -> weight = stof(fLine) ;
            
            cout << endl << endl << "Updated person to:" << endl ;
            cout << current -> pName << " | " << current -> pSSN << " | " 
                << current -> gender << " | " << current -> DOB << " | " 
                << current -> height << " | " << current -> weight << " | " 
                << current -> fSSN << " | "  << current -> mSSN << " | " <<  endl ;
            break ;
        }
        else {
            current = current -> next ;
        }
        if (current == NULL) {
            cout << endl << "SSN:" << inputSSN << " not found. Please try again." ;
        }
    }
}




















