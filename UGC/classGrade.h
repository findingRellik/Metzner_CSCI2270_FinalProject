#ifndef CLASSGRADE_H
#define CLASSGRADE_H

#include <iostream>
#include <istream>

using namespace std;

struct Section{ //Every class has multiple
    string section; //Section name contained within class
    double sectionWeight = 0; //Individual section of class weight e.g. HW %30 or .30
    int numGrades = 0; //Number of grades in section e.g. 14 HW assignments throughout the semester
    double *sectionGrades;//Array of grade entries
    double gradeSum = 0; // Sum of Grades of section
    double avgGrade = 0; //AVG. GRADE of section
    double weightSum = 0; // Avg. Grade X Weight of section

    Section *next; //Pointer to next section array
    Section(){} // default constructor
};

class classGrade{
private:
    Section *head;
    Section *tail;
    string className; //Name of class e.g. "Data Structures"
    int numSections; //Number section
    bool finalTaken = false; //Whether or not final will be factored in to current grading process
public:
    classGrade(string name, int count);
    classGrade();
    ~classGrade();
    Section* getSectionInfo(Section *node);
    Section* validGrade(Section *node, int i);
    Section* getAvg(Section *node);
    void deleteClass();
    void addClass();
    void printGrades();
    void totalGrades();
    void bestNworst();
    void min2pass();
    void min2A();
    void changeGrade();
    void min2grade();
    Section* updateSectionVal(Section *node, int i);
};

#endif // CLASSGRADE_H
