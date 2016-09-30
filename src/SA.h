//SA.h
//Simulated Anenaling Algorithm Class
#ifndef SA
#define SA

#include <math.h>
#include "SchedCSP.h"
#include <ctime>

class SimulatedAnnealing{
	public:
		SimulatedAnnealing(SchedCSP csp);
		SchedCSP* getSolution();
	
	private:
		float Temperature (float T, int count);
		float acceptance (int delta, float temperature);
		float rng ();
		SchedCSP csp;
};
#endif