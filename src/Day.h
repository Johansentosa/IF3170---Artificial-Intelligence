#ifndef DAY
#define DAY
enum class Day
{
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY
}; //Enumerate days. Why? Because I CAN

inline void printDay(Day x) {
	switch (x) {
		case Day::MONDAY: printf("MONDAY "); break;
		case Day::TUESDAY: printf("TUESDAY "); break;
		case Day::WEDNESDAY: printf("WEDNESDAY "); break;
		case Day::THURSDAY: printf("THURSDAY "); break;
		case Day::FRIDAY: printf("FRIDAY "); break;
	}
}

inline int getDay(Day x){
	switch (x) {
		case Day::MONDAY: return 1;
		case Day::TUESDAY: return 2;
		case Day::WEDNESDAY: return 3;
		case Day::THURSDAY: return 4;
		case Day::FRIDAY: return 5;
	}
}
#endif
