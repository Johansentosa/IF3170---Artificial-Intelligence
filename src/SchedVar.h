//SchedVar.h
//A class containing Variables and domain for SchedCSP

#ifndef SCHEDVAR
#define SCHEDVAR

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Day.h"
using namespace std;

template <typename T>
class SchedVar{
	public:
		SchedVar();
		SchedVar(const SchedVar<T> &o);
		SchedVar<T> operator=(const SchedVar<T> &o);
		~SchedVar();
		
		//var
		vector<T> domain;
		bool conflict; //only time variable will get conflict, otherwise conflict = false
		int selectedIndex; //selected index in domain array
};

#endif
