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

#endif