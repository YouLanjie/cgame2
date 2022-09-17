#include "../include/head.h"

void GetTime() {
	time_t timep;
	struct tm *tp;

	time(&timep);
	tp=gmtime(&timep);

	GameInfo->chess->t.year = 1900+tp->tm_year;
	GameInfo->chess->t.mon = 1+tp->tm_mon;
	GameInfo->chess->t.day = tp->tm_mday;
	GameInfo->chess->t.hour = 8 + tp->tm_hour;
	GameInfo->chess->t.min = tp->tm_min;
	GameInfo->chess->t.sec = tp->tm_sec;
	return;
}

void GetNowTime() {
	time_t timep;
	struct tm *tp;

	time(&timep);
	tp=gmtime(&timep);

	GameInfo->chess->nt.year = 1900+tp->tm_year;
	GameInfo->chess->nt.mon = 1+tp->tm_mon;
	GameInfo->chess->nt.day = tp->tm_mday;
	GameInfo->chess->nt.hour = 8 + tp->tm_hour;
	GameInfo->chess->nt.min = tp->tm_min;
	GameInfo->chess->nt.sec = tp->tm_sec;
	return;
}


