//SchedCSP.h
//class that can read CSP from file and saves the CSP inside the object
#ifndef SCHEDCSP
#define SCHEDCSP 

#include "SchedVar.h"
#include <cassert>
using namespace std;

typedef struct
{
    string roomName;
    int openTime, closeTime;
    vector<Day> openDays; 
} Room;

class SchedCSP{
  public:
    //Set variables within the constructors. Read from test file
    SchedCSP();
    SchedCSP(const char *fname);
    ~SchedCSP();
    
    //Getter
    // vector<vector<string>> getConstraint();
    // vector<string> getClassName();
    // vector<vector<SchedVar>> getVars();
    // int getConflicts();
    int getRoomIndex(string roomName);
    int getRoomIndexFrom(string, int);
    vector<int> getIndex();
    vector<int> getRandomIndex();
    void applyIndex(vector<int> v);
    bool testIndex(vector<int> v);
    int getCourseSize();
    
    //Printer
    void printVars();
    void printConstr();
    void printVarValues();
    void print4PHP();
    
    //Splitter
    vector<string> splitString(string line, char delimiter);
    vector<int> splitInt(string line, char delimiter);
    
    //Initiator
    void initAllVars();	//initialize all variables with random values
    void initSingleVar(int); //initialize single variables with random values
    
    //Conflicts
    int countConflicts();	//count conflict then set conflicts
    void checkConflicts();	//check variables, if conflicting each other, set SchedVar bool conflict true
    int findFirstConflicts();	//return first-found index of conflict, if no conflict return -1
    
  private:
    //Variables and domains
    vector<Room> constr;
    
	vector<SchedVar<Day>> dayVars;
    vector<SchedVar<int>> timeVars;
    vector<SchedVar<int>> roomVars;

    vector<string> classname; //class name for vars; e.g. IF2130
    vector<int> duration;

    int conflicts;
};
#endif
