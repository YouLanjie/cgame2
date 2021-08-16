#include "../include/head.h"

void welcome(short p,short a) {
	Clear
	if (p == 1){
		printf("%s",LANG[10]);
	}
	else if (p == 2) {
		printf("%s",LANG[11]);
	}
	kbhit2();
	menu(LANG[12],p,a);
	kbhit2();
	return;
}


