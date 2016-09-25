//SchedCSP.cpp	
#include "SchedCSP.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

int SchedCSP::getRoomIndex(string roomName) {
	for (int i = 0; i < constr.size(); ++i)
	{
		if (constr[i].roomName == roomName)
		{
			return i;
		}
	}
	assert(false && "Room not found");
}

//CTORS
SchedCSP::SchedCSP(){}
SchedCSP::SchedCSP(const char * fname){
	conflicts = -1;
	ifstream infile(fname);
	assert(infile.is_open() && "File Cannot be Opened");
	string line;

	//Input Ruangan
	getline(infile, line);
	if(line.substr(0,7)=="Ruangan"){
		
		while(1){
			getline(infile, line);
			if(line.substr(0,6)=="Jadwal"){
				break;
			}
			vector<string> c = splitString(line,';');
			Room roomBuild;
			roomBuild.roomName = c[0];
			roomBuild.openTime = stoi(c[1]);
			roomBuild.closeTime = stoi(c[2]);
			vector<string> days = splitString(c[3], ',');
			for (int i = 0; i < days.size(); ++i)
			{
				int x = stoi(days[i]);
				Day res;
				switch (x) {
					case 1: res = Day::MONDAY; break;
					case 2: res = Day::TUESDAY; break;
					case 3: res = Day::WEDNESDAY; break;
					case 4: res = Day::THURSDAY; break;
					case 5: res = Day::FRIDAY; break;
				}
				roomBuild.openDays.push_back(res);
			}
			constr.push_back(roomBuild);
		}
	}
	
	//Input Jadwal
	while(getline(infile, line)){
		vector<string> v = splitString(line,';');
		classname.push_back(v[0]);
		SchedVar<Day> day;
		SchedVar<int> time;
		SchedVar<string> room;
		//room
		if(v[1]=="-"){
			for(int i=0; i<constr.size();++i){
				room.domain.push_back(constr[i].roomName);
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
		for(int i=start; i<=(end-dur); ++i){
			time.domain.push_back(i);
		}
		
		//day
		vector<string> days = splitString(v[5], ',');
		for (int i = 0; i < days.size(); ++i)
		{
			int x = stoi(days[i]);
			Day res;
			switch (x) {
				case 1: res = Day::MONDAY; break;
				case 2: res = Day::TUESDAY; break;
				case 3: res = Day::WEDNESDAY; break;
				case 4: res = Day::THURSDAY; break;
				case 5: res = Day::FRIDAY; break;
			}
			day.domain.push_back(res);
		}

		//Cross check with room availibilty, remove room if room *absolutely* cannot satisfy course schedule
		vector<string> availableRoom;
		for (int i = 0; i < room.domain.size(); ++i)
		{
			string selectedRoomName = room.domain[i];
			int roomidx;
			roomidx = getRoomIndex(selectedRoomName);

			//check day availibilty
			vector<Day> roomOpenDays = constr[roomidx].openDays;
			bool flag = false;
			for (int j = 0; j < day.domain.size(); ++j)
			{
				Day x = day.domain[j];
				for (int k = 0; k < roomOpenDays.size(); ++k)
				{
					if (roomOpenDays[k] == x)
					{
						flag = true;
						break;
					}
				}
				if (flag)
				{
					break;
				}
			}
			if (!flag)
			{
				continue;
			}

			//check time availibilty
			if ((start <= constr[roomidx].openTime && constr[roomidx].openTime < end) ||
				(constr[roomidx].openTime <= start && start < constr[roomidx].closeTime)) //check if there's cross section
			{
				if (max(constr[roomidx].openTime, start) + dur <= min(constr[roomidx].closeTime, end)) // if course at least can fit into the cross section
				{
					availableRoom.push_back(selectedRoomName);
				} 
			}
		}
		assert(availableRoom.size() != 0 && "There's no possible room to accomodate a course");
		room.domain = availableRoom;

		duration.push_back(dur);
		dayVars.push_back(day);
		roomVars.push_back(room);
		timeVars.push_back(time);
	}
}


SchedCSP::~SchedCSP(){
	
}

//Getter
// vector<vector<string>> SchedCSP::getConstraint(){
// 	return constr;
// }

// vector<string> SchedCSP::getClassName(){
// 	return classname;
// }

// vector<vector<SchedVar>> SchedCSP::getVars(){
// 	return vars;
// }

// int SchedCSP::getConflicts(){
// 	return conflicts;
// }

vector<int> SchedCSP::getRandomIndex() {
	initAllVars();
	vector<int> res;
	for (int j = 0; j < timeVars.size(); ++j)
	{
		res.push_back(timeVars[j].selectedIndex);
		res.push_back(dayVars[j].selectedIndex);
		res.push_back(roomVars[j].selectedIndex);
	}
	return res;
}

void SchedCSP::applyIndex(vector<int> v) {
	int pos = 0;
	for (int j = 0; j < timeVars.size(); ++j)
	{
		timeVars[j].selectedIndex = v[pos++];
		dayVars[j].selectedIndex = v[pos++];
		roomVars[j].selectedIndex = v[pos++];
	}
}

bool SchedCSP::testIndex(vector<int> v) {
	applyIndex(v);
	for (int i = 0; i < timeVars.size(); ++i)
	{
		if (timeVars[i].selectedIndex < 0 || timeVars[i].selectedIndex >= timeVars[i].domain.size() ||
			dayVars[i].selectedIndex < 0 || dayVars[i].selectedIndex >= dayVars[i].domain.size() ||
			roomVars[i].selectedIndex < 0 || roomVars[i].selectedIndex >= roomVars[i].domain.size()) {
			return false;
		}

		string selectedRoomName = roomVars[i].domain[roomVars[i].selectedIndex];
		Day selectedDay = dayVars[i].domain[dayVars[i].selectedIndex];
		int selectedTime = timeVars[i].domain[timeVars[i].selectedIndex];

		int roomidx;
		roomidx = getRoomIndex(selectedRoomName);
		Room selectedRoom = constr[roomidx];
		bool flag = false;
		for (int j = 0; j < selectedRoom.openDays.size(); ++j)
		{
			if (selectedRoom.openDays[j] == selectedDay)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			return false;
		}

		if (!(selectedTime >= selectedRoom.openTime && selectedTime + duration[i] <= selectedRoom.closeTime))
		{
			return false;
		}
	}
	return true;
}

//Conflict
int SchedCSP::countConflicts(){
	int count = 0;
	for (int i = 0; i < timeVars.size(); ++i)
	{
		timeVars[i].conflict = false;
	}
	checkConflicts();
	for (int i = 0; i < timeVars.size(); ++i)
	{
		if (timeVars[i].conflict)
		{
			count++;
		}
	}
	conflicts = count;
	return conflicts;
}

void SchedCSP::checkConflicts(){
	for(int i=0;i<timeVars.size()-1;++i){
		for(int j=i+1;j<timeVars.size();++j){
			//if room and day are equal
			Day dayI = dayVars[i].domain[dayVars[i].selectedIndex];
			Day dayJ = dayVars[j].domain[dayVars[j].selectedIndex];
			string roomI = roomVars[i].domain[roomVars[i].selectedIndex];
			string roomJ = roomVars[j].domain[roomVars[j].selectedIndex];
			if(dayI == dayJ && roomI == roomJ){
				//check the time
				int startI = timeVars[i].domain[timeVars[i].selectedIndex];
				int endI = startI + duration[i];
				int startJ = timeVars[j].domain[timeVars[j].selectedIndex];
				int endJ = startJ + duration[j];
				if ((startI <= startJ && startJ < endI) ||
					(startJ <= startI && startI < endJ))
				{
					timeVars[i].conflict = true;
					timeVars[j].conflict = true;
				}
			}
		}
	}
}

void SchedCSP::printVars(){
	cout<<"Printing All Variables Domain"<<endl;
	for (int j = 0; j < timeVars.size(); ++j)
	{
		cout<<"Course: " << classname[j] << endl;
		cout<<"Time: ";
		for (int i = 0; i < timeVars[j].domain.size(); ++i)
		{
			cout<<timeVars[j].domain[i]<<"\t";
		}
		cout<<endl;
		cout<<"Room: ";
		for (int i = 0; i < roomVars[j].domain.size(); ++i)
		{
			cout<<roomVars[j].domain[i]<<"\t";
		}
		cout<<endl;
		cout<<"Day: ";
		for (int i = 0; i < dayVars[j].domain.size(); ++i)
		{
			printDay(dayVars[j].domain[i]);
		}
		cout<<endl;
		cout<<endl;
	}
		
}

void SchedCSP::printConstr(){
	cout<<"Printing All Room"<<endl;
	for(int i=0; i<constr.size();++i){
		Room room = constr[i];
		cout<<"Room Name: "<<room.roomName<<"\t";
		cout<<"Room Open Time: "<<room.openTime<<"\t";
		cout<<"Room Close Time: "<<room.closeTime<<"\t";
		cout<<"Room Open Day: ";
		for (int j = 0; j < room.openDays.size(); ++j)
		{
			printDay(room.openDays[j]);
			
		}
		cout<<endl;
	}
}

void SchedCSP::printVarValues(){
	cout<<"Printing Selected Variables Values"<<endl;
	for (int j = 0; j < timeVars.size(); ++j)
	{
		cout<<"Course: " << classname[j] << endl;
		cout<<"Time: ";
		cout<<timeVars[j].domain[timeVars[j].selectedIndex]<<endl;
		cout<<"Room: ";
		cout<<roomVars[j].domain[roomVars[j].selectedIndex]<<endl;
		cout<<"Day: ";
		printDay(dayVars[j].domain[dayVars[j].selectedIndex]);
		cout<<endl;
		cout<<endl;
	}
}

//Initiator
void SchedCSP::initAllVars(){
	conflicts = 0;
	for(int i=0; i<timeVars.size(); ++i){
		roomVars[i].selectedIndex = rand() % roomVars[i].domain.size();

		string selectedRoomName = roomVars[i].domain[roomVars[i].selectedIndex];
		int roomidx;
		roomidx = getRoomIndex(selectedRoomName);

		//init day var
		vector<Day> roomOpenDays = constr[roomidx].openDays;
		vector<Day> courseAvailableDays = dayVars[i].domain;
		bool flag[courseAvailableDays.size()]; //true when course available that day AND room open, false otherwise
		int countAvailableDays = 0; //number flag turned on
		for (int j = 0; j < courseAvailableDays.size(); ++j)
		{
			flag[j] = false;
			Day x = courseAvailableDays[j];
			for (int k = 0; k < roomOpenDays.size(); ++k)
			{
				if (roomOpenDays[k] == x)
				{
					flag[j] = true;
					break;
				}
			}
			if (flag[j])
			{
				countAvailableDays++;
			}
		}
		int dayRandCount = rand() % countAvailableDays; //random day
		for (int j = 0; j < courseAvailableDays.size(); ++j)
		{
			if (flag[j])
			{
				if (dayRandCount == 0)
				{
					dayVars[i].selectedIndex = j;
					break;
				} else {
					dayRandCount--;
				}
			}
		}

		//init time var
		int dur = duration[i];
		int roomOpenTime = constr[roomidx].openTime;
		int roomCloseTime = constr[roomidx].closeTime;
		int courseStartTime = timeVars[i].domain[0];
		int courseEndTime = timeVars[i].domain[timeVars[i].domain.size() - 1] + dur;
		int startTimeWindow = max(roomOpenTime, courseStartTime); //time window to random
		int endTimeWindow = min(roomCloseTime, courseEndTime) - dur;
		int windowSize = endTimeWindow - startTimeWindow + 1;
		int selectedTime = startTimeWindow + rand() % windowSize;
		for (int j = 0; j < timeVars[i].domain.size(); ++j)
		{
			if (timeVars[i].domain[j] == selectedTime)
			{
				timeVars[i].selectedIndex = j;
				break;
			}
		}


	}
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
