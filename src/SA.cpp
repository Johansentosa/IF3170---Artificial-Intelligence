#include "SA.h"

SimulatedAnnealing::SimulatedAnnealing(SchedCSP csp):csp(csp){};

float SimulatedAnnealing::Temperature(float T,int count){
	return T * pow(0.95,(double)count);
};

float SimulatedAnnealing::acceptance(int delta, float temperature){
	return 1/(1+exp(-delta/temperature));
};

float SimulatedAnnealing::rng(){
	int r = rand()%100000;
	return (float)r/100000;
}

SchedCSP* SimulatedAnnealing::getSolution(){
	csp.initAllVars();
	int idxConflict = csp.findFirstConflicts();
	int conflict	= csp.countConflicts();
	int newConflict ;
	int counter = 0;
	int delta ;
	int T = 1;
	while((conflict>0)&&(counter<1000)){
		csp.initSingleVar(idxConflict);	
		newConflict = csp.countConflicts();
		delta = newConflict - conflict;
		if((newConflict < conflict)||(rng()>acceptance(delta,Temperature(T,counter)))){
			idxConflict = csp.findFirstConflicts();
			conflict = newConflict;
			counter = 0;
		}
		else{
			counter++;
		}
		//cout<<csp.countConflicts()<<endl;
		//cout<<"this is probability"<<acceptance(delta,Temperature(1,counter))<<endl;
		//cout<<"this is rng"<<rng()<<endl;
	}

	return &csp;
	
	
};
