//main.cpp
#include <iostream>
#include "SchedCSP.h"
using namespace std;

int main(){
	srand(time(NULL));
	string fname = "testcase/tc1.txt";
	SchedCSP *S = new SchedCSP(fname.c_str());
	S->printConstr();
	cout<<endl;
	cout<<"done"<<endl;
	cout<<endl;
	S->printVars();
	cout<<endl;
	S->initAllVars();
	S->printVarValues();
	cout<<endl;
	cout<<S->countConflicts()<<endl;
	return 0;
}
