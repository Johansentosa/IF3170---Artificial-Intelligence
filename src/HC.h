//HC.h
//Hill Climb Algorithm Class
#ifndef HC
#define HC

#include "SchedCSP.h"

class HillClimb{
	public:
		HillClimb(SchedCSP csp);
		SchedCSP* getSolution();
	
	private:
		SchedCSP csp;
};
#endif