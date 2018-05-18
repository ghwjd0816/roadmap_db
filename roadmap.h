#pragma once

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <mysql.h>

#define  DB_HOST  "localhost"
#define  DB_USER  "root"
#define  DB_PORT  3306
#define  DB_NAME  "roadmap"

struct timetable {
	int sp;
	int ae;
	int fm;
	int hg;
	int jg;
	int jp;
	int js;
	int is;
};

struct dept_db {
	char name[30];
	int sapyo;
	int acdeng;
	int freshman;
	int hackgyo;
	int jeongyo;
	int jeonpil;
	int jeonson;
	int illson;
};

struct subject_db {
	char name[50];
	char dept[30];
	char classify[30];
	int num;
};

struct student_db {
	char name[10];
	char studentno[11];
	char dept[30];
};

struct sugang_db {
	char name[10];
	char subject[50];
	int semester;
};