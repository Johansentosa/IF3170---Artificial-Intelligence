//SchedVar.h
//A class containing Variables and domain for SchedCSP

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class SchedVar{
	public:
		SchedVar();
		SchedVar(const SchedVar &o);
		SchedVar operator=(const SchedVar &o);
		~SchedVar();
		
		//var
		vector<string> domain;	
		int duration; //only time variable will get duration, otherwise duration = 0
		bool conflict; //only time variable will get conflict, otherwise conflict = false
		string value;
};
