//SchedVar.cpp
#include "SchedVar.h"

template <typename T>
SchedVar<T>::SchedVar(){
	conflict = false;
}

template <typename T>
SchedVar<T>::SchedVar(const SchedVar<T> &o):domain(o.domain){
	conflict = o.conflict;
}

template <typename T>
SchedVar<T> SchedVar<T>::operator=(const SchedVar<T> &o){
	domain = o.domain;
	conflict = o.conflict;
	return *this;
}

template <typename T>
SchedVar<T>::~SchedVar(){
	
}

template class SchedVar<Day>;
template class SchedVar<int>;
template class SchedVar<string>;
