#include "HC.h"

HillClimb::HillClimb(SchedCSP csp):csp(csp){};

SchedCSP* HillClimb::getSolution(){
	csp.initAllVars();
	int idxConflict = csp.findFirstConflicts();
	int conflict	= csp.countConflicts();
	int newConflict ;
	int counter = 0;
	while((conflict>0)&&(counter<1000)){
		csp.initSingleVar(idxConflict);	
		newConflict = csp.countConflicts();
		if(newConflict < conflict){
			idxConflict = csp.findFirstConflicts();
			conflict = newConflict;
			counter = 0;
		}
		else{
			counter++;
		}
		//cout<<csp.countConflicts()<<endl;
	}

	return &csp;
	
	
};
