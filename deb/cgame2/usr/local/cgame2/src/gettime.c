#include "../include/head.h"

void gettime() {
	time_t timep;
	struct tm *tp;

	time(&timep);
	tp=gmtime(&timep);

	p -> t.year = 1900+tp->tm_year;
	p -> t.mon = 1+tp->tm_mon;
	p -> t.day = tp->tm_mday;
	p -> t.hour = 8 + tp->tm_hour;
	p -> t.min = tp->tm_min;
	p -> t.sec = tp->tm_sec;
	return;
}

void getnowtime() {
	time_t timep;
	struct tm *tp;

	time(&timep);
	tp=gmtime(&timep);

	p -> nt.year = 1900+tp->tm_year;
	p -> nt.mon = 1+tp->tm_mon;
	p -> nt.day = tp->tm_mday;
	return;
}


