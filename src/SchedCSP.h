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
    vector<int> getRandomIndex();
    void applyIndex(vector<int> v);
    bool testIndex(vector<int> v);
    
    //Printer
    void printVars();
    void printConstr();
    void printVarValues();
    
    //Splitter
    vector<string> splitString(string line, char delimiter);
    vector<int> splitInt(string line, char delimiter);
    
    //Initiator
    void initAllVars();	//initialise variables with random values
    void initClassVar(int index);	//initialise time,day, and room var with constr check
    void initTimeVar(int index);	//initialise variable in nth index
    void initDayVar(int index);
    void initRoomVar(int index);
    
    //Conflicts
    int countConflicts();	//count conflict then set conflicts
    void checkConflicts();	//check variables, if conflicting each other, set SchedVar bool conflict true
    
  private:
    //Variables and domains
    vector<Room> constr;
    
	vector<SchedVar<Day>> dayVars;
    vector<SchedVar<int>> timeVars;
    vector<SchedVar<string>> roomVars;

    vector<string> classname; //class name for vars; e.g. IF2130
    vector<int> duration;

    int conflicts;
};
#endif