//main.cpp
#include <iostream>
#include "SchedCSP.h"
#include "GA.h"
#include "HC.h"
#include "SA.h"
#include <ctime>
using namespace std;

int main(){
	srand(time(NULL));
	string fname = "testcase/tc1.txt";
	SchedCSP *S = new SchedCSP(fname.c_str());
	//S->printConstr();

	//S->printVars();
	
	//GeneticAlgorithm G(*S);
	//S = G.getCSPSolution();
	//SimulatedAnnealing H(*S);
	//S = H.getSolution();
	HillClimb H(*S);
	S = H.getSolution();
	cout<<"Conflict,"<<S->countConflicts()<<endl;	
	cout<<"class,time,room,day,duration"<<endl;
	S->print4PHP();
	return 0;
}
