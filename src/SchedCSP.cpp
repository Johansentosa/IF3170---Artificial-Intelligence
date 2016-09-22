//SchedCSP.cpp	
#include "SchedCSP.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

//CTORS
SchedCSP::SchedCSP(const char * fname){
	conflicts = -1;
	ifstream infile(fname);
	string line;
	getline(infile, line);
	if(line.substr(0,7)=="Ruangan"){
		
		while(1){
			getline(infile, line);
			if(line.substr(0,6)=="Jadwal"){
				break;
			}
			vector<string> c = splitString(line,';');
			constr.push_back(c);
		}
	}
	
	//Create Variables
	vector<SchedVar> vday;
	vector<SchedVar> vtime;
	vector<SchedVar> vroom;
	while(getline(infile, line)){
		vector<string> v = splitString(line,';');
		classname.push_back(v[0]);
		SchedVar day;
		SchedVar time;
		SchedVar room;
		//day
		day.domain = splitString(v[5],',');
		
		//room
		if(v[1]=="-"){
			for(int i=0; i<constr.size();++i){
				room.domain.push_back(constr[i][0]);
			}
		} else {
			vector<string> vv = splitString(v[1],',');
			if(vv.size()>1){
				room.domain.push_back(v[1]);
			} else {
				room.domain = vv;
			}
		}
		
		//time
		int start = stoi(v[2]);
		int end = stoi(v[3]);
		int dur = stoi(v[4]);
		
		time.duration = dur;
		for(int i=start; i<=(end-dur); ++i){
			time.domain.push_back(to_string(i));
		}
		
		vday.push_back(day);
		vroom.push_back(room);
		vtime.push_back(time);
	}
	vars.push_back(vroom);
	vars.push_back(vtime);
	vars.push_back(vday);
}

SchedCSP::~SchedCSP(){
	
}

//Getter
vector<vector<string>> SchedCSP::getConstraint(){
	return constr;
}

vector<string> SchedCSP::getClassName(){
	return classname;
}

vector<vector<SchedVar>> SchedCSP::getVars(){
	return vars;
}

int SchedCSP::getConflicts(){
	return conflicts;
}

//Conflict
int SchedCSP::countConflicts(){
	int count = 0;
	checkConflicts();
	for(int i=0;i<vars[1].size();++i){
		if(vars[1][i].conflict){
			count++;
		}
	}
	conflicts = count;
	return conflicts;
}

void SchedCSP::checkConflicts(){
	for(int i=0;i<vars[0].size()-1;++i){
		for(int j=i+1;j<vars[0].size();++j){
			//if room and day are equal
			if((vars[0][i].value==vars[0][j].value)&&(vars[2][i].value==vars[2][j].value)){
				//check the time
				int a_start = stoi(vars[1][i].value);
				int a_end = stoi(vars[1][i].value) + vars[1][i].duration;
				int b_start = stoi(vars[1][j].value);
				int b_end = stoi(vars[1][j].value) + vars[1][j].duration;
				if(a_end>b_start && a_start < b_end){
					vars[1][i].conflict = true;
					vars[1][j].conflict = true;
				}
			}
		}
	}
}

//Printer
void SchedCSP::printVars(){
	for(int i=0; i<vars.size();++i){
		for(int j=0;j<vars[i].size();++j){
			for(int k=0;k<vars[i][j].domain.size();++k){
				cout<<vars[i][j].domain[k]<<"\t";
			}
			cout<<endl;
		}
		cout<<endl;
	}
}

void SchedCSP::printConstr(){
	for(int i=0; i<constr.size();++i){
		for(int j=0;j<constr[i].size();++j){
			cout<<constr[i][j]<<"\t";
		}
		cout<<endl;
	}
}

void SchedCSP::printVarValues(){
	for(int i=0; i<vars.size();++i){
		for(int j=0;j<vars[i].size();++j){
			cout<<vars[i][j].value<<endl;
		}
		cout<<endl;
	}
}

//Initiator
void SchedCSP::initAllVars(){
	conflicts = 0;
	for(int i=0; i<vars[0].size(); ++i){
		initClassVar(i);
	}
}

void SchedCSP::initClassVar(int index){
	bool avail = false;
	do{
		initRoomVar(index);
		initTimeVar(index);
		initDayVar(index);
		
		int roomidx=-1;
		//check room
		for(int i=0; i<constr.size();++i){
			if(constr[i][0]==vars[0][index].value){
				roomidx = i;
				break;
			}
		}
		if(roomidx==-1){
			cout<<"Room not found"<<endl;
			break;
		}
		
		//check other var based on room's time and day availability
		//check day
		vector<int> vstr = splitInt(constr[roomidx][3],',');
		bool day = false;
		for(int i=0; i<vstr.size();++i){
			if(vstr[i]==stoi(vars[2][index].value)){
				day = true;
				break;
			}
		}
		
		//check time
		bool time = false;
		if(day){
			int open = stoi(constr[roomidx][1]);
			int close = stoi(constr[roomidx][2]);
			int begin = stoi(vars[1][index].value);
			int end = stoi(vars[1][index].value)+vars[1][index].duration;
			if((open<=begin)&&(close>=end)){
				time = true;
			}
		}
		avail = (time && day);
	} while(!avail);
}

void SchedCSP::initRoomVar(int index){
	srand(time(NULL));
	int val = rand() % vars[0][index].domain.size();
	vars[0][index].value = vars[0][index].domain[val];
}

void SchedCSP::initTimeVar(int index){
	srand(time(NULL));
	int val = rand() % vars[1][index].domain.size();
	vars[1][index].value = vars[1][index].domain[val];
	vars[1][index].conflict = false;
}

void SchedCSP::initDayVar(int index){
	srand(time(NULL));
	int val = rand() % vars[2][index].domain.size();
	vars[2][index].value = vars[2][index].domain[val];
}

//Splitter
vector<string> SchedCSP::splitString(string line, char delimiter){
	vector<string> vect;
    stringstream ss;
    ss.str(line);
    string item;
    while (getline(ss, item, delimiter)) {
        vect.push_back(item);
    }
	return vect;
}

vector<int> SchedCSP::splitInt(string line, char delimiter){
	vector<int> vect;
    stringstream ss(line);
    int i;
    while (ss >> i){
        vect.push_back(i);

        if (ss.peek() == delimiter){
            ss.ignore();
		}
    }
	return vect;
}
