/**Universal Grade Calculator by Austin Metzner*/
#include <iostream>
#include <istream>
#include "classGrade.h"

using namespace std;

int main()
{
    cout << "Welcome to the Universal Grader!" << endl;
    classGrade *myClass = new classGrade;

    string userInput;
    while(userInput != "10"){
        cout<<"======Main Menu====="<<endl;
        cout<<"1. Add a class"<<endl;
        cout<<"2. Calculate class grade"<<endl;
        cout<<"3. Print grades"<<endl;
        cout<<"4. Best and worst section"<<endl;
        cout<<"5. Minimum grade (on final) to pass"<<endl;
        cout<<"6. Change grade"<<endl;
        cout<<"7. Delete class"<<endl;
        cout<<"8. Minimum grade (on final) to receive A"<<endl;
        cout<<"9. Minimum grade (on final) to receive grade of your choice"<<endl;
        cout<<"10. Quit"<<endl<<endl<<"~~";

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
//OPTION 8 MINIMUM GRADE ON FINAL TO EARN A GRADE OF USER'S CHOICE
        else if(userInput == "9"){
            myClass->min2grade();
        }
    }
    cout<<"Later alligator"<<endl;
    delete myClass;

    return 0;
}
