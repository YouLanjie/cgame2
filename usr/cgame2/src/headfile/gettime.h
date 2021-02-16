#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *gettime() {
	time_t timep;
	struct tm *p;
	time(&timep);

	char *ch;
	char b[10];

	p = gmtime(&timep);
	ch = (char *)malloc(sizeof(char) * 40);

	strcpy(ch,"日期：");
	sprintf(b,"%d",1900+p->tm_year);
	strcat(ch,b);
	strcat(ch,"年/");
	sprintf(b,"%d",1+p->tm_mon);
	strcat(ch,b);
	strcat(ch,"月/");
	sprintf(b,"%d",p->tm_mday);
	strcat(ch,b);
	strcat(ch,"日 时间：");
	sprintf(b,"%d",8+p->tm_hour);
	strcat(ch,b);
	strcat(ch,":");
	sprintf(b,"%d",p->tm_min);
	strcat(ch,b);
	strcat(ch,":");
	sprintf(b,"%d",p->tm_sec);
	strcat(ch,b);
	return ch;
}

void printtime() {
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	printf("%d/%d/%d %d:%d:%d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
	return;
}
