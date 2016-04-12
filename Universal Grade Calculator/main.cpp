#include <iostream>
#include <istream>

using namespace std;

struct Section{
    string section;
    double sectionWeight;
    int numGrades;
    double sectionGrades[];
    double gradeSum;
    double weightSum;

    Section *next;
};

class classGrade{
private:
   Section *head;
   Section *tail;
   string className;
   int numSections;
public:
    classGrade(string name, int count){
        className = name;
        numSections = count;
        head = NULL;
        tail = NULL;
    }
    classGrade(){
        head = NULL;
        tail = NULL;
    }

    void addClass(){
        //Instating head as first class
        head = new Section;
        cout<<"Enter name of class: ";
        getline(cin, this->className);
        cout<<"Enter number of sections: ";
        cin>>this->numSections;

        cout<<"Enter name of section: ";
        getline(cin, head->section);
        cout<<"Enter section weight: ";
        cin>>head->sectionWeight;
        cout<<"Enter number of grades in section: ";
        cin>>head->numGrades;
        //Inputting grades
        head->sectionGrades[head->numGrades];
        for(int i = 0; i < head->numGrades; i++){
            cout<<"Enter grade"<<i<<": ";
            cin>>head->sectionGrades[i];
            head->gradeSum += head->sectionGrades[i];
        }
        //Getting Section Average
        head->weightSum = head->sectionWeight*head->gradeSum;
        cout<<"Section average: "<<head->weightSum<<endl;
        head->next = NULL;
        Section *current = head;

        //sets values of each section
        int i = 1;
        while(i < this->numSections){
            City *tmp = new City;
            tmp->cityName = cityList[i];
            tmp->message = "";
            tmp->next = NULL;
            tmp->previous = current;
            current->next = tmp;
            current = current->next;
            i++;
        }

    }

    void printGrades(){
        current = head;
        cout<<"===CURRENT PATH==="<<endl;
        cout<<"NULL <- ";
        while(current != NULL){
            if(current->next == NULL){
                cout<<current->cityName<<" -> ";
                current = current->next;
            }
            else{
                cout<<current->cityName<<" <-> ";
                current = current->next;
            }
        }
        cout<<"NULL"<<endl;
        cout<<"=================="<<endl;
    }


};

int main()
{
    cout << "Welcome to the Universal Grader!" << endl;
    //classGrade *myClass = new classGrade;
    Section *head = new Section;

    string userInput;
    while(userInput != "5"){
        cout<<"======Main Menu====="<<endl;
        cout<<"1. Add a class"<<endl;
        cout<<"2. Calculate grade"<<endl;
        cout<<"3. Print grades"<<endl;
        cout<<"4. Delete class"<<endl;
        cout<<"5. Quit"<<endl;

        getline(cin,userInput);
//OPTION 1 ADD A NEW CLASS
        if(userInput == "1"){
            classGrade *myClass = new classGrade;
            myClass.addClass();
        }
//OPTION 2 CALCULATE GRADE
        else if(userInput == "2"){
            myClass.addClass(numSec);
        }
//OPTION 3 PRINT GRADES
        else if(userInput == "3"){
            myClass.addClass(numSec);
        }
//OPTION 4 enqueue sentence
        else if(userInput == "4"){
            delete myClass;
        }

    }
    cout<<"Goodbye!"<<endl;
    delete myClass;

    return 0;
}
