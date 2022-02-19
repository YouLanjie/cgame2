#include "../include/head.h"

void Init() {
	unsigned short error = 0;
	int config[2] = {1, 0};    //配置选项

	Clear
	if (access("/usr/local/cgame2", 0) == EOF) {
		perror("\033[1;31m[init](Game Dir): access \033[0m");
		strcpy(Save, "./cgame2-data/save.txt");
		strcpy(Config, "./cgame2-data/config.txt");
		error = 1;
	}
	else if(access("/usr/local/cgame2/data",0) == EOF) {
		mkdir("/usr/local/cgame2/data", 0777);
		if(access("/usr/local/cgame2/data",0) == EOF) {
			perror("\033[1;31m[init](Game Dir): access \033[0m");
#ifdef __linux
			printf("\033[?25h");
#endif
			exit(1);
		}
		error = 0;
	}
	if(access(Config,0) == EOF) {       /* 创建Config文件 */
		config[0] = 1;
		config[1] = 0;
		Max = 15;
		fp = fopen(Config,"w");
		if (!fp) {
			perror("\033[1;31m[init](Config): fopen\033[0m");
			getch();
			exit(1);
		}
		fprintf(fp, "1 %d 15",config[1]);
		fclose(fp);
	}
	else {           /* 读取config文件 */
		fp = fopen(Config, "r");
		if (!fp) {
			perror("Config");
			printf("\033[?25h");
			exit(-1);
		}
		if(fscanf(fp, "%d%d%d", &config[0], &config[1], &Max) == EOF) {
			perror("Config");
#ifdef __linux
			printf("\033[?25h");
#endif
			exit(-1);
		}
		fclose(fp);
	}
	if (config[1] == 1) {  /* 更改数据存放地址为当前目录 */
		strcpy(Save, "./cgame2-data/save.txt");
		strcpy(Config, "./cgame2-data/config.txt");
		config[1] = 1;
		mkdir("./cgame2-data/", 0777);
		if (access("cgame2-data", 0) == EOF) {
			perror("\033[1;31m[init](mkdir)创建文件夹失败Failed to create folder\033[0m");
			getch();
			exit(1);
		}
		if (access(Config,0) == EOF) {
			fp = fopen(Config,"w");
			config[0] = 1;
			config[1] = 1;
			Max = 15;
			if (!fp) {
				perror("\033[1;31m[init](Config): fopen\033[0m");
				getch();
				exit(1);
			}
			fprintf(fp, "%d %d %d", config[0], config[1], Max);
			fclose(fp);
		}
		else {
			fp = fopen(Config,"w");
			config[1] = 1;
			fprintf(fp, "%d %d %d", config[0], config[1], Max);
			fclose(fp);
		}
		
	}
	else if (error != 1 && config[1] == 0) {  /* 更改数据存放地址为默认目录 */
		strcpy(Save, "/usr/local/cgame2/data/save.txt");
		strcpy(Config, "/usr/local/cgame2/data/config.txt");
		if (access(Config,0) == EOF) {
			fp = fopen(Config,"w");
			config[0] = 1;
			config[1] = 0;
			Max = 15;
			if (!fp) {
				perror("\033[1;31m[init](Config): fopen\033[0m");
				getch();
				exit(1);
			}
			fprintf(fp, "%d %d %d", config[0], config[1], Max);
			fclose(fp);
		}
		else {
			fp = fopen(Config,"w");
			config[1] = 0;
			fprintf(fp, "%d %d %d", config[0], config[1], Max);
			fclose(fp);
		}
	}	
	if(access(Save,0) == EOF) {       /*创建Save文件*/
		fp = fopen(Save,"w");
		if (!fp) {
			perror("\033[1;31m[init](Save): fopen\033[0m");
			getch();
			exit(1);
		}
		fclose(fp);
	}
	return;
}
