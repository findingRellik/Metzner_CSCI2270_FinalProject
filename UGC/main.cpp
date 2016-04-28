/**Universal Grade Calculator by Austin Metzner*/
#include <iostream>
#include <istream>
#include "classGrade.h"

using namespace std;
/**
struct Section{ //Every class has multiple
    string section; //Section name contained within class
    double sectionWeight = 0; //Individual section of class weight e.g. HW %30 or .30
    int numGrades = 0; //Number of grades in section e.g. 14 HW assignments throughout the semester
    double *sectionGrades;//Array of grade entries
    double gradeSum = 0; // Sum of Grades of section
    double avgGrade = 0; //AVG. GRADE of section
    double weightSum = 0; // Avg. Grade X Weight of section

    Section *next; //Pointer to next section array
};

class classGrade{
private:
   Section *head;
   Section *tail;
   string className; //Name of class e.g. "Data Structures"
   int numSections; //Number section
   bool finalTaken = false; //Whether or not final will be factored in to current grading process
public:
    classGrade(string name, int count)
    {
        className = name;
        numSections = count;
        finalTaken = false;
        head = NULL;
        tail = NULL;
    }
    classGrade()
    {
        head = NULL;
        tail = NULL;
    }
    ~classGrade()
    {
        this->deleteClass();
    }

    Section* getSectionInfo(Section *node)//Gets section info Checks if section weight entered is less than one
    {
        cout<<"Enter name of section: ";
        getline(cin, node->section);
        double x = -1;
        while(0 >= x || x > 1)
        {
            cout<<"Enter section weight (0-1.00): ";
            cin>>x; cin.ignore();
            if( x>0 && x<=1)
            {
                node->sectionWeight = x;
                break;
            }
        }
        int y = -1;
        while(0 > y)
        {
            cout<<"Enter number of grades in section: ";
            cin>>y; cin.ignore();
            if(y >=0)
            {
                node->numGrades = y;
                break;
            }
        }
        node->sectionGrades = new double[node->numGrades]; //Creates array for grades for this section
        return node;
    }

    Section* validGrade(Section *node, int i)//makes sure grade entry is from 0-100
    {
        double x = -1;
        while(0 > x || x > 100)
        {
            cout<<"Enter "<<node->section<<" grade "<<(i+1)<<": ";
            cin>>x; cin.ignore();
            if(x>0 && x<=100)
            {
                node->sectionGrades[i] = x;
                node->gradeSum += node->sectionGrades[i];
                return node;
            }
        }
    }

    Section* getAvg(Section *node)//calculates section average
    {
        node->avgGrade = (node->gradeSum/node->numGrades);//Getting Section Average and weighted grade
        node->weightSum = node->sectionWeight*node->avgGrade;
        return node;
    }

    void deleteClass()
    {
        Section *current = head;
        Section *tmp = new Section;
        if(current != NULL)
        {
            cout<<"Deleting "<<this->className<<endl;
            while(current != NULL)
            { // Runs until all are deleted
                tmp = current->next;
                cout<<"Deleting "<<current->section<<endl;
                delete current;
                current = tmp;
            }
        head = NULL;
        }
        delete current;
        cout<<"Class successfully deleted"<<endl;
    }

    void addClass()
    {
        cout<<"===ADDING CLASS==="<<endl;
        //Establishing class
        cout<<"Enter name of class: ";
        getline(cin, this->className);
        cout<<"The final is by default the last section included in the section count"<<endl;
        cout<<"Enter number of sections: ";
        cin>>this->numSections; cin.ignore(); cout<<endl;

        //Establishing each section and grades
        Section* first = new Section;//Instating head as first section of class
        double finalWeight = 0;//used to calculate weight of final automatically
        first = getSectionInfo(first);
        for(int i = 0; i < first->numGrades; i++)//Inputting grades
        {
            first = validGrade(first, i);
        }
        first = getAvg(first);
        finalWeight += first->sectionWeight;
        cout<<"Section average: "<<first->avgGrade<<endl; cout<<endl;
        head = first;

        Section *current = head;//sets values of each section after head
        for(int i = 1; i < this->numSections-1; i++)
        {
            Section *tmp = new Section;
            tmp = getSectionInfo(tmp);
            for(int i = 0; i < tmp->numGrades; i++)
            {
                validGrade(tmp, i);
            }
            tmp = getAvg(tmp);
            finalWeight += tmp->sectionWeight;
            cout<<"Section average grade: "<<tmp->avgGrade<<endl; cout<<endl;
            current->next = tmp;
            current = current->next;
        }
        //The final
        Section *final = new Section;
        current->next = final;
        if(finalWeight >= 1)
        {
            cout<<"Section weight sum must be less than 1"<<endl;
            return;
        }
        final->section = "Final"; final->sectionGrades = new double[1]; final->numGrades = 1;
        string answer;
        while(answer != "y" && answer != "n")
        {
            final->sectionWeight = 1 - finalWeight; //automatically determines weight of final
            cout<<"Have you taken the final? (y/n)   ";
            getline(cin, answer);
            if(answer == "y")
            {
                cout<<"What was your score?  ";
                cin>>final->gradeSum; cin.ignore();
                final->sectionGrades[0] = final->gradeSum;
                final = getAvg(final);
                this->finalTaken = true;
                break;
            }
            else if (answer == "n") break;
        }
        tail = final; cout<<endl;
    }

    void printGrades()
    {
        Section *current = head;
        cout<<"===PRINTING GRADES==="<<endl;
        cout<<endl;
        while(current != NULL)
        {
            if(current == tail && this->finalTaken == false)
            {
                cout<<"Final has not been taken ~"<<endl;
                break;
            }
            else
            {
                cout<<"Name of section: "<<current->section;
                cout<<" | Section weight: "<<current->sectionWeight;
                cout<<" | Number of grades: "<<current->numGrades<<endl;
                for(int i = 0; i < current->numGrades; i++)
                {
                    if(i == 0)
                        cout<<current->section<<" "<<(i+1)<<": ";
                    else
                        cout<<" | "<<current->section<<" "<<(i+1)<<": ";
                    cout<<current->sectionGrades[i];
                }
                cout<<endl;
                cout<<"Average grade in this section: "<<current->avgGrade;
                cout<<" | Weighted grade: "<<current->weightSum<<endl<<endl;
                current = current->next;
            }
        }
        cout<<"=================="<<endl;
        cout<<endl;
    }

    void totalGrades()//Calculates current or final grade
    {
        cout<<endl;
        cout<<"===CALCULATING CLASS GRADE==="<<endl<<endl;
        if(this->finalTaken == true)
        {
            Section *current = head;
            double finalGrade = 0; //Current grade is weighted Averages divided by combined weights of classes thus far
            while(current != NULL)
            {
                finalGrade += current->weightSum;
                current = current->next;
            }
            cout<<"Your grade in "<<this->className<<" is: "<<finalGrade<<endl<<endl;
        }
        else//If final not taken
        {
            Section *current = head;
            double currentSum,currentWeight = 0; //Current grade is weighted Averages divided by combined weights of classes thus far
            while(current != tail)
            {
                currentSum += current->weightSum;
                currentWeight += current->sectionWeight;
                current = current->next;
            }
            cout<<"Your grade in "<<this->className<<" thus far is: "<<(currentSum/currentWeight)<<endl;
        } cout<<endl;
    }

    void bestNworst()//Calculates best and worst section
    {
        cout<<"===BEST AND WORST SECTIONS==="<<endl;
        Section *current = head;
        Section *worstSection = new Section; Section *bestSection = new Section;
        double worstGrade = 99999; double bestGrade = -1;
        while(current != NULL)
        {
            if(current == tail)
            {
                if(this->finalTaken == false)
                    break;
            }
            if(current->avgGrade > bestGrade)
            {
                bestGrade = current->avgGrade;
                bestSection = current;
            }
            if(current->avgGrade < worstGrade)
            {
                worstGrade = current->avgGrade;
                worstSection = current;
            }
            current = current->next;
        }
        cout<<"Your best section in "<<this->className<<" is '"<<bestSection->section<<"' with an average grade of: ";
        cout<<bestSection->avgGrade<<endl;
        cout<<"Your worst section in "<<this->className<<" is '"<<worstSection->section<<"' with an average grade of: ";
        cout<<worstSection->avgGrade<<endl; cout<<endl;
    }

    void min2pass()//Minimum grade on final needed to pass
    {
        cout<<endl;
        cout<<"===MINIMUM GRADE TO PASS==="<<endl;
        if(this->finalTaken == true)
        {
            cout<<"This operation calculates the minimum score the user needs to pass this class"<<endl;
            cout<<"The final exam must not have been taken in order to access the function ~"<<endl<<endl;
            return;
        }
        else//If final not taken
        {
            Section *current = head;
            double currentGrade = 0; double grade2pass = 0;
            while(current != tail)
            {
                currentGrade += current->weightSum;
                current = current->next;
            }
            grade2pass = (60 - currentGrade)/tail->sectionWeight;
            cout<<"Assuming a 60 is the deciding point of failure or not..."<<endl;
            cout<<"You need a minimum score of "<<grade2pass<<" on the final in order to pass "<<this->className<<endl;
            if(grade2pass >= 80)
                cout<<"Good luck ~"<<endl;
        }
        cout<<endl;
    }

    void changeGrade()//Lets user change grades of a section
    {
        cout<<"===CHANGING GRADES==="<<endl;
        string input;
        while(input != "q")
        {
            Section *current = head;
            cout<<"Enter 'q' to quit editing"<<endl;
            cout<<"Which section would you like to edit?...  ";
            getline(cin, input);
            if(input == "q")
                return;
            while(current != NULL)
            {
                if(current->section == input)
                    break;
                current = current->next;
            }
            if(current == NULL)
                cout<<"Section name not found"<<endl;
            else
            {
                for(int i = 0; i < current->numGrades; i++)
                {
                    if(i == 0)
                        cout<<current->section<<" "<<i<<": ";
                    else
                        cout<<" | "<<i<<": ";
                    cout<<current->sectionGrades[i];
                } cout<<endl;
                int index; //double newGrade;
                cout<<"Which grade would you like to change (select number next to grade)?: ";
                cin>>index; cin.ignore();
                current = updateSectionVal(current, index);
            }
        }
    }

    Section* updateSectionVal(Section *node, int i)//Updates values of section after changes are made
    {
        node->gradeSum = 0;
        double x = -1;
        if (node->section == "Final") //If user wants to update the final it will be marked as taken
            this->finalTaken = true;
        while(0 > x || x > 100)
        {
            cout<<"What number would you like to change grade "<<i<<" to?: ";
            cin>>x; cin.ignore();
            if(x>0 && x<=100)
            {
                node->sectionGrades[i] = x;

                break;
            }
        }
        for(int t = 0; t < node->numGrades; t++)
            node->gradeSum += node->sectionGrades[t];
        node = getAvg(node);
        return node;
    }
};
*/


int main()
{
    cout << "Welcome to the Universal Grader!" << endl;
    classGrade *myClass = new classGrade;

    string userInput;
    while(userInput != "9"){
        cout<<"======Main Menu====="<<endl;
        cout<<"1. Add a class"<<endl;
        cout<<"2. Calculate class grade"<<endl;
        cout<<"3. Print grades"<<endl;
        cout<<"4. Best and worst section"<<endl;
        cout<<"5. Minimum grade (on final) to pass"<<endl;
        cout<<"6. Change grade"<<endl;
        cout<<"7. Delete class"<<endl;
        cout<<"8. Minimum grade (on final) to receive A"<<endl;
        cout<<"9. Quit"<<endl<<endl<<"~~";

        getline(cin,userInput);
//OPTION 1 ADD A NEW CLASS
        if(userInput == "1"){
            //classGrade *myClass = new classGrade;
            myClass->addClass();
        }
//OPTION 2 CALCULATE GRADE
        else if(userInput == "2"){
            myClass->totalGrades();
        }
//OPTION 3 PRINT GRADES
        else if(userInput == "3"){
            myClass->printGrades();
        }
//OPTION 4 Best and worst sections
        else if(userInput == "4"){
            myClass->bestNworst();
        }
//OPTION 5 MINIMUM GRADE ON FINAL TO PASS
        else if(userInput == "5"){
            myClass->min2pass();
        }
//OPTION 6 Change GRADE
        else if(userInput == "6"){
            myClass->changeGrade();
        }
//OPTION 7 DELETE CLASS
        else if(userInput == "7"){
            myClass->deleteClass();
        }
//OPTION 8 MINIMUM GRADE ON FINAL TO EARN A
        else if(userInput == "8"){
            myClass->min2A();
        }

    }
    cout<<"Later alligator"<<endl;
    delete myClass;

    return 0;
}
