//main.cpp
#include <iostream>
#include "SchedCSP.h"
#include "GA.h"
#include "HC.h"
using namespace std;

int main(){
	//srand(time(NULL));
	string fname = "testcase/tc1.txt";
	SchedCSP *S = new SchedCSP(fname.c_str());
	S->printConstr();
	cout<<endl;
	cout<<"done"<<endl;
	cout<<endl;
	S->printVars();
	cout<<endl;/*
	GeneticAlgorithm G(*S);
	S = G.getCSPSolution();*/
	HillClimb H(*S);
	S = H.getSolution();	
	S->printVarValues();
	cout<<endl;
	cout<<S->countConflicts()<<endl;
	
	return 0;
}
