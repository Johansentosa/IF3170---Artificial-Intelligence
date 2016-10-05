//main.cpp
#include <iostream>
#include "SchedCSP.h"
#include "GA.h"
#include "HC.h"
#include "SA.h"
#include <ctime>
using namespace std;

int main(int argc, char *argv[]){
	if ( argc != 3 ){
		cout<<"usage: "<< argv[1] <<" <algorithm>\n"<<endl;
		cout<<"usage: "<< argv[2] <<" <filename>\n"<<endl;
	} else {
		srand(time(NULL));
		string algo = argv[1];
		string fname = argv[2];
		SchedCSP *S = new SchedCSP(fname.c_str());
		if(algo=="SA"){
			SimulatedAnnealing H(*S);
			S = H.getSolution();
			cout<<"Conflict,"<<S->countConflicts()<<endl;
			cout<<"Effectiveness,"<<S->getEffectiveness()<<endl;
			cout<<"class,time,room,day,duration"<<endl;
			S->print4PHP();
		} else if(algo=="GA"){
			GeneticAlgorithm G(*S);
			S = G.getCSPSolution();
			cout<<"Conflict,"<<S->countConflicts()<<endl;
			cout<<"Effectiveness,"<<S->getEffectiveness()<<endl;
			cout<<"class,time,room,day,duration"<<endl;
			S->print4PHP();
		} else if(algo=="HC"){
			HillClimb H(*S);
			S = H.getSolution();
			cout<<"Conflict,"<<S->countConflicts()<<endl;
			cout<<"Effectiveness,"<<S->getEffectiveness()<<endl;
			cout<<"class,time,room,day,duration"<<endl;
			S->print4PHP();
		} else {
			cout<<"usage: "<< argv[1] <<" <algorithm>\n"<<endl;
			cout<<"usage: "<< argv[2] <<" <filename>\n"<<endl;
		}
		return 0;
	}
}
