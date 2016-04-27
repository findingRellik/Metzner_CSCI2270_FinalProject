#include <iostream>
#include <istream>

using namespace std;

struct Section{ //Every class has multiple
    string section; //Section name contained within class
    double sectionWeight; //Individual section of class weight e.g. HW %30 or .30
    int numGrades; //Number of grades in section e.g. 14 HW assignments throughout the semester
    double sectionGrades[];//Array of grade entries
    double gradeSum; // Sum of Grades of section
    double avgGrade; //AVG. GRADE of section
    double weightSum; // Avg. Grade X Weight of section

    Section()
    {
        sectionWeight = 0;
        numGrades = 0;
        gradeSum = 0;
        avgGrade = 0;
        weightSum = 0;
    }

    Section *next; //Pointer to next section array
};

class classGrade{
private:
   Section *head;
   Section *tail;
   double totalGrade = 0;// Total grade thus far
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

    void addClass()
    {
        /**Establishing class*/
        cout<<"Enter name of class: ";
        getline(cin, this->className);
        cout<<"Enter number of sections: ";
        cin>>this->numSections; cin.ignore(); cout<<endl;

        /**Establishing each section and grades*/
        head = new Section;//Instating head as first section of class
        tail = new Section;
        cout<<"Enter name of section: ";
        getline(cin, head->section);
        cout<<"Enter section weight: ";
        cin>>head->sectionWeight; cin.ignore();
        cout<<"Enter number of grades in section: ";
        cin>>head->numGrades; cin.ignore(); cout<<endl;
        head->sectionGrades[head->numGrades] = {0}; //Creates array for grades for this section
        for(int i = 1; i <= head->numGrades; i++)//Inputting grades
        {
            cout<<"Enter "<<head->section<<" grade "<<i<<": ";
            cin>>head->sectionGrades[i]; cin.ignore();
            head->gradeSum += head->sectionGrades[i];
            //cout<<"Grade sum "<<head->gradeSum<<endl;
        }
        head->avgGrade = (head->gradeSum/head->numGrades);//Getting Section Average and weighted grade
        head->weightSum = head->sectionWeight*head->avgGrade;
        this->totalGrade += head->weightSum;
        cout<<"Section average: "<<head->avgGrade<<endl; cout<<endl;

        Section *current = head;//sets values of each section after head
        for(int i = 1; i < this->numSections-1; i++)
        {
            Section *tmp = new Section;
            cout<<"Enter name of section: ";
            getline(cin, tmp->section);
            cout<<"Enter section weight: ";
            cin>>tmp->sectionWeight; cin.ignore();
            cout<<"Enter number of grades in section: ";
            cin>>tmp->numGrades; cin.ignore(); cout<<endl;
            tmp->sectionGrades[head->numGrades];

            for(int i = 1; i <= tmp->numGrades; i++)//Inputting grades
            {
                cout<<"Enter "<<tmp->section<<" grade "<<i<<": ";
                cin>>tmp->sectionGrades[i]; cin.ignore();
                tmp->gradeSum += tmp->sectionGrades[i];
                //cout<<"Grade sum "<<tmp->gradeSum<<endl;
            }
            tmp->avgGrade = (tmp->gradeSum/tmp->numGrades);//Getting Section Average
            tmp->weightSum = tmp->sectionWeight*tmp->avgGrade;
            this->totalGrade += tmp->weightSum;
            cout<<"Section average: "<<tmp->avgGrade<<endl; cout<<endl;
            current->next = tmp;
            current = current->next;
        }
        /**The final*/
        Section *current2 = new Section;
        current->next = current2;
        current2->section = "Final"; current2->sectionGrades[1] = {0}; current2->numGrades = 1;
        string answer = "";
        while(answer != "y" or answer != "n")
        {
            cout<<"What is the final's weight?  ";
            cin>>current2->sectionWeight; cin.ignore();
            cout<<"Have you taken the final? (y/n)  ";
            getline(cin, answer);
            if(answer == "y")
            {
                cout<<"What was your score?  ";
                cin>>current2->avgGrade; cin.ignore();
                current2->sectionGrades[1] = current2->avgGrade;
                current2->gradeSum = current2->avgGrade;
                current2->weightSum = current2->sectionWeight*current->avgGrade;
                this->finalTaken = true;
                this->totalGrade += current2->weightSum;
                break;
            }
            else if (answer == "n") break;
        }
        tail = current2;
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

                    for(int i = 1; i <= current->numGrades; i++)
                    {
                        if(i == 1)
                            cout<<current->section<<" "<<i<<": ";
                        else
                            cout<<" |"<<current->section<<" "<<i<<": ";
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
        if(this->finalTaken == true)
            cout<<"Your grade in "<<this->className<<" is: "<<this->totalGrade<<endl;
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

        while
        Section *current = head;
        double currentGrade = 0; double grade2pass = 0;
        while(current != tail)
        {
            currentGrade += current->weightSum;
            current = current->next;
        }
        grade2pass = (60 - currentGrade)/tail->sectionWeight;

    }
};



int main()
{
    cout << "Welcome to the Universal Grader!" << endl;
    classGrade *myClass = new classGrade;
    //Section *head = new Section;

    string userInput;
    while(userInput != "11"){
        cout<<"======Main Menu====="<<endl;
        cout<<"1. Add a class"<<endl;
        cout<<"2. Calculate class grade"<<endl;
        cout<<"3. Print grades"<<endl;
        cout<<"4. Best and worst section"<<endl;
        cout<<"5. Minimum grade (on final) to pass"<<endl;cout<<endl;
        cout<<"4. Delete class"<<endl;
        cout<<"11. Quit"<<endl;

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
//OPTION 6 MINIMUM GRADE ON FINAL TO PASS
        else if(userInput == "6"){
            myClass->changeGrade();
        }

    }
    cout<<"Goodbye!"<<endl;
    delete myClass;

    return 0;
}
