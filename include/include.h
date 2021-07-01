/* File name: include.h */
/* This is a head file */

#ifndef _INCLUDE_H_
#define _INCLUDE_H_

/* include head file */
#include <stdio.h>
#include <stdlib.h>
/* system() srand() rand() malloc() free() exit() */
#include <unistd.h>
/* pause() */
#include <sys/stat.h>
/* pass */
#include <sys/types.h>
/* pass */
#include <string.h>
/* strcat() strcmp() strcpy() */

#ifndef Clear
	#define Clear printf("\033[2J\033[1;1H");
#endif
#ifndef Clear2
	#define Clear2 system("clear");
#endif

/* kbhit */
int kbhit();
int input();
int kbhit_if();
int kbhit2();

/* menu */
void menu(char title[50], short p, short a);
void menu2(char title[50]);
#ifndef Menu
	#define Menu printf("\033[0m\033[11;11H");
#endif
#ifndef Menu2
	#define Menu2 printf("\033[0m\033[11;19H");
#endif

/* pid */
/* #include <sys/types.h> */
/* pid_t */
#include <signal.h>
/* signal() */
#include <wait.h>

#endif

