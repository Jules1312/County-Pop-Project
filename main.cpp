// It is a project!

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

struct person;
typedef person* PersonPtr;

struct ages ;
typedef ages* AgesPtr ;

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

struct ages{
    
    long pSSN ;
    string pName ;
    float age ;
    
    AgesPtr next ;
    AgesPtr prev ;
    
} ;

void TestFunction();
void DisplayMenu();
void InitializeList(PersonPtr&, string, AgesPtr&, AgesPtr&);
void DisplayList(PersonPtr, AgesPtr, AgesPtr);
void DisplayHighBMI(PersonPtr);
void RemovePerson(PersonPtr&, long, AgesPtr&, AgesPtr&);
void RemoveAge(AgesPtr&, AgesPtr&, long) ;
void AddPersonsFromFile(PersonPtr&, string, AgesPtr&, AgesPtr&);
void AddPersonFromUser(PersonPtr&, AgesPtr&, AgesPtr&);
void EditPerson(PersonPtr, long) ;
float CalcBMI(float, float);
float get_age(string) ;
void buildAgeList(AgesPtr&, AgesPtr&, float, string, long) ;
void DisplaySSPeople(AgesPtr) ;
long* FindChildren(PersonPtr, long, int&) ; 
void DisplayChildren(long*, int&, AgesPtr, long) ;
void DisplayMFRatio(PersonPtr);
void DisplayParents(PersonPtr, long);

int main(){
    
    AgesPtr agesHead = NULL ;
    AgesPtr agesEND = NULL ;
    
    PersonPtr head = NULL ;
    string filename = "county-pop.txt";
    InitializeList(head, filename, agesHead, agesEND);

    cout << "County-Pop-Project" << endl << endl;
    DisplayMenu();

    bool isrunning = true;
    int userin;
    long inputSSN ;
    string inputFilename ;
    int arraySize = 0 ;
    
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
                DisplayList(head, agesHead, agesEND);
                break;
            case 2 :
                cout << endl << "Please enter the SSN of the person you would like to delete: " ;
                cin >> inputSSN ;
                RemovePerson(head, inputSSN, agesHead, agesEND);
                break;
            case 3 :
                cout << endl ;
                AddPersonFromUser(head, agesHead, agesEND) ;
                break;
            case 4 :
                cout << endl << "Please enter the file name: " ;
                cin >> inputFilename ;
                AddPersonsFromFile(head, inputFilename, agesHead, agesEND);
                break;
            case 5 :
                cout << endl << "Please enter the SSN of the person you would like to edit: ";
                cin >> inputSSN ;
                EditPerson(head, inputSSN) ;
                break;
            case 6 :
                cout << endl;
                DisplaySSPeople(agesEND);
                break;
            case 7 :
                cout << endl;
                DisplayHighBMI(head);
                break;
            case 8 :
                cout << endl;
                DisplayMFRatio(head);
                break;
            case 9 :
                cout << endl << "Please enter the SSN of the person whos parents you want to find: ";
                cin >> inputSSN;
                DisplayParents(head, inputSSN);
                break;
            case 10 :
                cout << endl << "Find the children of which person? Please enter their SSN: " ;
                cin >> inputSSN ;
                DisplayChildren(FindChildren(head, inputSSN, arraySize), arraySize, agesHead, inputSSN) ;
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

void InitializeList(PersonPtr& head, string filename, AgesPtr& agesHead, AgesPtr& agesEND){
    /* This function initializes the list of
       residents from a file at the start of the program */

    PersonPtr current = NULL ;
    PersonPtr newPerson = NULL ;

    string fline;
    ifstream fCountyPop;
    fCountyPop.open(filename);

    while(!fCountyPop.eof()){
        
        newPerson = new person ;

        getline(fCountyPop, fline);
        newPerson->pName = fline;
        getline(fCountyPop, fline);
        newPerson->pSSN = stol(fline);
        getline(fCountyPop, fline);
        newPerson->gender = fline[0];
        getline(fCountyPop, fline);
        newPerson->DOB = fline;
        getline(fCountyPop, fline);
        newPerson->height = stof(fline);
        getline(fCountyPop, fline);
        newPerson->weight = stof(fline);
        getline(fCountyPop, fline);
        newPerson->fSSN = stol(fline);
        getline(fCountyPop, fline);
        newPerson->mSSN = stol(fline);
        
        

        newPerson -> next = NULL ;
        
        if (head == NULL) {
            head = newPerson ;
            current = newPerson ;
            buildAgeList(agesHead, agesEND, get_age(newPerson->DOB + " 00:00:00"), newPerson->pName, newPerson->pSSN) ;
        }
        else {
            current -> next = newPerson ;
            current = newPerson ;
            buildAgeList(agesHead, agesEND, get_age(newPerson->DOB + " 00:00:00"), newPerson->pName, newPerson->pSSN) ;
        }
    }
    fCountyPop.close();

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

void DisplayList(PersonPtr head, AgesPtr agesHead, AgesPtr agesEND){

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
    
    
    AgesPtr currentAge = agesHead ;
    
    while(currentAge != NULL){
        cout << currentAge->age << " | " << currentAge->pSSN << " | "
             << currentAge->pName << " | " <<  endl;
        currentAge = currentAge->next;
    }
    
    currentAge = agesEND ;
    
    while(currentAge != NULL){
        cout << currentAge->age << " | " << currentAge->pSSN << " | "
             << currentAge->pName << " | " <<  endl;
        currentAge = currentAge->prev;
    }
}

float CalcBMI(float height, float weight){
    return (weight / (height * height)) * 703;
}

void DisplayHighBMI(PersonPtr head){

    // Counts the persons in the list with high BMIs
    int pcount;
    PersonPtr current = head;

    while(current != NULL){
        //cout << current->pName << "  " << CalcBMI(current->height, current->weight) << endl ;
        if(CalcBMI(current->height, current->weight) > 27){
            pcount++;
            //current = current->next;
            cout << current->pName << " if" << endl ;
        }
        else {
            //current = current->next;
            //cout << current->pName << " else" << endl ;
        }
        current = current->next;
        //cout << endl << current->pName << " this is current next at end of loop" ;
    }
    current = head;

    // Creates a person array to store those with high BMIs
    person personary[pcount];
    int i = 0;

    while(current != NULL){
        if(CalcBMI(current->height, current->weight) > 27){
            cout << "i " << i ;
            personary[i].pName = current->pName;
            personary[i].height = current->height ;
            personary[i].weight = current->weight ;
            
            cout << endl << current->pName << " 2nd loop" << endl ;
            cout << personary[i].pName << endl ;
            i++;
            //current = current->next;
        }
        //else {
           // current = current->next;
        //}
        current = current->next;
        cout << endl << current << " current next" << endl ;
    }
    current = head;
    cout << endl << "did we leave the loop?" ;
    // Sorts the person array into ascending order
    person tmp;
    /*for(int i = 0; i < pcount; i++){
        for(int x = 1; x < pcount; x++){ // 0 = 4    1 = 4
            if(CalcBMI(personary[x].height, personary[x].weight) < CalcBMI(personary[x - 1].height, personary[x - 1].weight)){
                tmp = personary[x];
                personary[x] = personary[x - 1];
                personary[x - 1] = tmp;
            }
        }
    }
*/
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

void RemovePerson(PersonPtr& head, long pSSN, AgesPtr& agesHead, AgesPtr& agesEND) {
    
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
    
    RemoveAge(agesHead, agesEND, pSSN) ; // remove the person from the age linked list too
    
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

void AddPersonsFromFile(PersonPtr& head, string ogFile, AgesPtr& agesHead, AgesPtr& agesEND){


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
        
        buildAgeList(agesHead, agesEND, get_age(newPerson->DOB + " 00:00:00"), newPerson->pName, newPerson->pSSN) ;
        
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

void AddPersonFromUser(PersonPtr& head, AgesPtr& agesHead, AgesPtr& agesEND) {
    
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
    
    buildAgeList(agesHead, agesEND, get_age(userPerson->DOB + " 00:00:00"), userPerson->pName, userPerson->pSSN) ;
    
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

float get_age(string strDOB) {
    
    time_t tDOB ;
    int yy, month, dd, hh, mm, ss ;
    struct tm tBase ;
    
    const char *zStart = strDOB.c_str() ;
    
    sscanf(zStart, "%d/%d/%d %d:%d:%d", &yy, &month, &dd, &hh, &mm, &ss) ;
    
    tBase.tm_year = yy - 1900 ;
    tBase.tm_mon = mm - 1 ;
    tBase.tm_mday = dd ;
    tBase.tm_hour = hh ;
    tBase.tm_min = mm ;
    tBase.tm_sec = ss ;
    tBase.tm_isdst = -1 ;
    
    tDOB = mktime(&tBase) ;
    
    time_t tCurrent ;
    time(&tCurrent) ;
    
    long seconds = difftime(tCurrent, tDOB) ;
    float years = float(seconds) / (365.0 * 24.0 * 3600.0) ;
    
    return years ;
}

void buildAgeList(AgesPtr& agesHead, AgesPtr& agesEND, float age, string pName, long pSSN) {
    
    AgesPtr newAger = new ages ;
    
    newAger -> pName = pName ;
    newAger -> pSSN = pSSN ;
    newAger -> age = age ;
    newAger -> next = NULL ;
    newAger -> prev = NULL ;
    
    if (agesHead == NULL) {
        agesHead = newAger ; // first age in list so it is first and last
        agesEND = newAger ;
        return ;
    }
    AgesPtr current = agesHead ;
    AgesPtr past = current ;
    AgesPtr future = NULL ;
    
    if (newAger->age > current->age) { // only deals with first 2 in the list
        agesHead = newAger ; // if it is larger than the first/head then it becomes it
        newAger -> next = current ; // 3/2  3 now points to 2
        current -> prev = newAger ; // 3/2  2 now points back to 3
        return ;
    }
    else {
        while (current != NULL) { // not position 1 or 2? Lets find where it goes
        
            future = current -> next ;
            if (newAger->age > current->age) { // list == 4/*3/2/1   3 == newAger  2 == current
                past -> next = newAger ; // 4 points to 3
                newAger -> prev = past ; // 3 points back to 4
                newAger -> next = current ; // 3 points to 2
                current -> prev = newAger ; // 2 points back to 3    now it is 4 <-> 3 <-> 2
                return ;
            }
            else {
                if (future == NULL) { // you are on the last age in the list
                    current -> next = newAger ; // 2 points to 1   4/3/2/*1*  2 == current   1 == newAger
                    newAger -> prev = current ; // 1 points back to 2
                    agesEND = newAger ; // set 1 to the end so we can find it 
                    return ;
                }
            }
            past = current ;
            current = current -> next ; // keep the loop goin
        }
        
    }
}
void RemoveAge(AgesPtr& agesHead, AgesPtr& agesEND, long pSSN) {
    
    AgesPtr current = agesHead ;
    AgesPtr future ;
    AgesPtr temp ;
    bool first = true ;
    
    while (true) {
        future = current -> next ;
        if (future->pSSN == pSSN) { 
            if (future->next == NULL) { //end so 4/3/2/1 remove 1
                current -> next = NULL ; // 2 points to NULL
                agesEND = current ; // set the end to 2 
                delete future ; // delete 1
                return ;
            }
            else {  // 4/3/2/1 delete 2
                current -> next = future -> next ; // 3 points to 1
                temp = future -> next ;  // temp == 1
                temp -> prev = current ; // so 1 points back to 3
                delete future ; // delete 2
                return ;
            }
        }
        if ((current->pSSN == pSSN) && (first == true)) { // 4/3/2/1 delete 4
            agesHead = future ; // new head is 3
            future -> prev = NULL ; // head prev set to NULL
            delete current ; // delete 4
            return ;
        }
        current = current -> next ;
        first = false ;
    }
}
void DisplaySSPeople(AgesPtr agesEND) {
    
    AgesPtr currentAge = agesEND ;
    
    while (currentAge != NULL){
        if (currentAge->age >= 65) {
            cout << currentAge->pName << "'s age is " << currentAge->age 
             << " and they are eligible for Social Security!" 
             <<  endl ;
        }
        
        currentAge = currentAge->prev;
    }
}
long* FindChildren(PersonPtr head, long inputSSN, int &arraySize) {
    
    PersonPtr current = head ;
    PersonPtr foundThem ;
    bool male ;
    arraySize = 0 ; // reset it for multiple runs
     
    
    while (current != NULL) { // find the person to find gender
        if (current->pSSN == inputSSN) {
            foundThem = current ;
            break ;
        }
        current = current -> next ;
        if (current == NULL) {
            cin.ignore() ;
            cout << inputSSN << " was not found. Please enter a new SSN: " ;
            cin >> inputSSN ;
            current = head ;
        }
        
    }
    
    if (foundThem->gender == 'M') {
        male = true ;
    }
    else male = false ;
    
    current = head ;
    while (current != NULL) { // just counting the children so we can make the array
        if (male == true) { // look at fSSN of everyone cus he a daddy
            if (current->fSSN == foundThem->pSSN) {
                arraySize++ ;
            }
        }
        else {// she a momma
            if (current->mSSN == foundThem->pSSN) { 
                arraySize++ ;
            }
        }
        current = current -> next ;
    }
    
    // array is dynamic so it will exist outside of the function
    long* childrenArray = new long[arraySize] ; // array to hold the SSN's of all the children
    int i = 0 ;
    current = head ;
    
    while (current != NULL) { // now we are filling the array
        if (male == true) { // look at fSSN of everyone cus he a daddy
            if (current->fSSN == foundThem->pSSN) {
                childrenArray[i] = current -> pSSN  ;
                i++ ;
            }
        }
        else {// she a momma
            if (current->mSSN == foundThem->pSSN) { 
                childrenArray[i] = current -> pSSN  ;
                i++ ;
            }
        }
        current = current -> next ;
    }
    
    return childrenArray ;
    
    
}

void DisplayChildren(long* childrenArray, int &arraySize, AgesPtr agesHead, long inputSSN) {
    
    AgesPtr current = agesHead ;
    
    if (arraySize == 0) {
        delete[] childrenArray ; // free up memory
        cout << endl << "SSN:" << inputSSN << " has no children." << endl ;
        return ; //we done here
    }
    
    cout << endl << endl << "Here are the children:" << endl << endl ;
    
    while (current != NULL) {
        for (int i = 0; i < arraySize; i++) { // compare all children to each current
            if (current->pSSN == childrenArray[i]) {
                cout << current -> pName << " | " << current -> pSSN 
                    << " | Age:" << current -> age << endl ;
            }  
        }
        current = current -> next ;
    }
    
    delete[] childrenArray ;
}

void DisplayMFRatio(PersonPtr head){

    int mcounter = 0;
    int fcounter = 0;
    int ocounter = 0;
    int d;
    float mfratio;

    PersonPtr current = head;

    while(current != NULL){
        switch(current->gender){
            case 'M' :
                mcounter++;
                break;
            case 'F' :
                fcounter++;
                break;
            default :
                ocounter++;
                break;
        }
        current = current->next;
    }

    d = __gcd(mcounter, fcounter);
    mcounter = mcounter / d;
    fcounter = fcounter / d;
    mfratio = fcounter / mcounter;

    cout << "The male:female ratio of the county is " << fcounter * mfratio << " females per 1000 males." << endl;
    if(ocounter > 0){
        cout << endl << "and there are " << ocounter << " individuals of other genders";
    }
}

void DisplayParents(PersonPtr head, long uSSN){

    PersonPtr current = head;
    string pName, fName, mName;
    long fSSN, mSSN;

    while(current != NULL){

        if(current->pSSN == uSSN){
            pName = current->pName;
            fSSN = current->fSSN;
            mSSN = current->mSSN;
        }
        current = current->next;
    }
    current = head;

    while(current != NULL){
        if(current->pSSN == fSSN)
            fName = current->pName;
        current->next;
    }
    while(current != NULL){
        if(current->pSSN == mSSN)
            mName = current->pName;
        current->next;
    }

    cout << pName << "'s mother is " << mName
    << " and their father is " << fName;
}

