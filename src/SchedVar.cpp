//SchedVar.cpp
#include "SchedVar.h"

SchedVar::SchedVar(){
	duration = 0;
	value = "null";
	conflict = false;
}

SchedVar::SchedVar(const SchedVar &o):domain(o.domain){
	duration = o.duration;
	value = o.value;
	conflict = o.conflict;
}

SchedVar SchedVar::operator=(const SchedVar &o){
	domain = o.domain;
	duration = o.duration;
	value = o.value;
	conflict = o.conflict;
	return *this;
}
SchedVar::~SchedVar(){
	
}
