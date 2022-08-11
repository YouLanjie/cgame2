#include "../include/head.h"

void Init() {
	int error = 0;
	FILE * fp;

#ifdef _WIN32
	changeDir("./cgame2-data/");
	config[1] = 1;
#endif
	if (access(GameDir, 0) == EOF) {
		changeDir("./cgame2-data/");
		config[1] = 1;
		if (access(GameDir, 0) == EOF) {
#ifdef __linux
			mkdir(GameDir, 0777);
#endif
#ifdef _WIN32
			mkdir(GameDir);
#endif
		}
		config[1] = 1;
		fp = fopen(Config, "w");
		fprintf(fp, "%d %d %d",config[0], config[1], Max);
		fclose(fp);
	}
	if(access(Config,0) == EOF) {       /* 创建Config文件 */
		fp = fopen(Config,"w");
		if (!fp) {
#ifdef __linux
			printf("\033[?25h");
#endif
			perror("[init](Config): fopen");
			exit(-1);
		}
		fprintf(fp, "%d %d %d",config[0], config[1], Max);
		fclose(fp);
	}
	else {
		fp = fopen(Config, "r");
		if (!fp) {
#ifdef __linux
			printf("\033[?25h");
#endif
			perror("Can't open file");
			exit(-1);
		}
		error = fscanf(fp,"%d%d%d", &config[0], &config[1], &Max);
		if (error == EOF) {
			perror("[init](Config): fscanf");
			fclose(fp);
			fp = fopen(Config, "w");
			config[0] = config[1] = 0;
			Max = 15;
			fprintf(fp, "%d %d %d",config[0], config[1], Max);
		}
		fclose(fp);
	}
	if (config[1] == 1 && strcmp(Config, "/etc/cgame2/config.txt") == 0) {
		changeDir("./cgame2-data/");
		if ((fp = fopen(Config, "w"))) {
			fprintf(fp,"%d %d %d", config[0], config[1], Max);
			fclose(fp);
		}
		Init();
	}
#ifdef __linux
	else if (config[1] == 0 && strcmp(Config, "./cgame2-data/config.txt") == 0) {
		changeDir("/etc/cgame2/");
		if ((fp = fopen(Config, "w"))) {
			fprintf(fp,"%d %d %d", config[0], config[1], Max);
			fclose(fp);
		}
		Init();
	}
#endif
	if(access(Save, 0) == EOF) {       /*创建Save文件*/
		fp = fopen(Save,"w");
		if (!fp) {
#ifdef __linux
			printf("\033[?25h");
#endif
			perror("\033[1;31m[init](Save): fopen\033[0m");
			exit(-1);
		}
		fclose(fp);
	}
	return;
}

void changeDir(char * dir) {
	GameDir = dir;
	strcpy(Config, GameDir);
	strcat(Config, "config.txt");
	strcpy(Save, GameDir);
	strcat(Save, "save.txt");
	return;
}
