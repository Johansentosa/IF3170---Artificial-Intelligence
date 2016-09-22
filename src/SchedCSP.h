//SchedCSP.h
//class that can read CSP from file and saves the CSP inside the object

#include "SchedVar.h"
using namespace std;

class SchedCSP{
  public:
    //Set variables within the constructors. Read from test file
    SchedCSP(const char *fname);
    SchedCSP(const SchedCSP &obj);
    SchedCSP operator=(const SchedCSP &o);
    ~SchedCSP();
    
    //Getter
    vector<vector<string>> getConstraint();
    vector<string> getClassName();
    vector<vector<SchedVar>> getVars();
    int getConflicts();
    
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
    vector<vector<string>> constr;
    
	//vars is different from other vectors, iterate from first index; e.g. vars[j][i]
    vector<vector<SchedVar>> vars; //vars[0] is room, vars[1] is starting time, vars[2] is day  
    
    vector<string> classname; //class name for vars; e.g. IF2130
    int conflicts;
};
