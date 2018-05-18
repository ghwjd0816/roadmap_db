#include "sqlio.h"

#pragma once
#pragma comment(lib, "libmySQL.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

int jobs();
int subjobs();

int main()
{
	char DB_PASS[15] = {}, ch;
	printf("[*]비밀번호를 입력하세요 : ");
	int cnt = 0;
	while(true)
	{
		ch = getch();
		if (ch == 13)break;
		printf("*");
		DB_PASS[cnt++] = ch;
		if (cnt > 14)break;
	}
	system("cls");
	MYSQL *pConnection = NULL;
	MYSQL conn;
	MYSQL_RES *pSQL_result;
	MYSQL_ROW SQL_row;
	int nQuery_stat;

	mysql_init(&conn);

	pConnection = mysql_real_connect(
		&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT,
		(char*)NULL, 0);
	if (pConnection == NULL)
	{
		printf("[-]Failed to connect mySQL\n");
		return -1;
	}

	mysql_query(pConnection, "SET SESSION character_set_connection=euckr;");
	mysql_query(pConnection, "SET SESSION character_set_results=euckr;");
	mysql_query(pConnection, "SET SESSION character_set_client=euckr;");

	while (1)
	{
		char szInsertQuery[1023];
		char szDeleteQuery[1023];
		char szSelectQuery[1023];
		bool insertflag = 0;
		bool deleteflag = 0;
		bool selectflag = 0;
		char *formatstring = NULL;
		int formatnum = 0;

		int jobno = jobs();
		if (jobno == 6) break;

		else if (jobno == 5)
		{
			char stname[10], deptname[30], stunum[10];
			format_print("[*]학번 : ");
			scanf("%s", stunum);
			system("cls");
			struct timetable tt = { 0,0,0,0,0,0,0,0 };
			struct timetable tott = { 0,0,0,0,0,0,0,0 };
			sprintf(szSelectQuery, "SELECT 학과.*, 학생.학생이름 FROM 학과, 학생 WHERE 학번='%s' AND 학과=학과명", stunum);
			nQuery_stat = mysql_query(pConnection, szSelectQuery);
			if (nQuery_stat != 0)
			{
				format_print("[-]Failed to send select query\n");
				return -1;
			}
			pSQL_result = mysql_store_result(pConnection);
			while ((SQL_row = mysql_fetch_row(pSQL_result)) != NULL)
			{
				sprintf(deptname, "%s", SQL_row[0]);
				tott.sp = atoi(SQL_row[1]);
				tott.ae = atoi(SQL_row[2]);
				tott.fm = atoi(SQL_row[3]);
				tott.hg = atoi(SQL_row[4]);
				tott.jg = atoi(SQL_row[5]);
				tott.jp = atoi(SQL_row[6]);
				tott.js = atoi(SQL_row[7]);
				tott.is = atoi(SQL_row[8]);
				sprintf(stname, "%s", SQL_row[9]);
			}
			
			mysql_free_result(pSQL_result);

			sprintf(szSelectQuery, "SELECT 과목.*, 수강.학기 FROM 수강,학생,학과,과목 WHERE 학생.학번='%s' AND 학생.학생이름=수강.학생이름 AND 수강.과목명=과목.과목명", stunum);
			nQuery_stat = mysql_query(pConnection, szSelectQuery);
			if (nQuery_stat != 0)
			{
				format_print("[-]Failed to send select query\n");
				return -1;
			}
			pSQL_result = mysql_store_result(pConnection);
			while ((SQL_row = mysql_fetch_row(pSQL_result)) != NULL)
			{
				char subname[50], dept[30], classi[30], subnum[10], semnum[10];
				int subno = 0, semno = 0;
				sprintf(subname, "%s", SQL_row[0]);
				sprintf(dept, "%s", SQL_row[1]);
				sprintf(classi, "%s", SQL_row[2]);
				sprintf(subnum, "%s", SQL_row[3]);
				sprintf(semnum, "%s", SQL_row[4]);
				subno = atoi(subnum);
				semno = atoi(semnum);
				if (strcmp(classi, "사고와표현") == 0)
					tt.sp += subno;
				else if (strcmp(classi, "Academic_English") == 0)
					tt.ae += subno;
				else if (strcmp(classi, "1학년세미나") == 0)
					tt.fm += subno;
				else if (strcmp(classi, "핵심교양") == 0)
					tt.hg += subno;
				else if (strcmp(classi, "전공관련교양") == 0)
					tt.jg += subno;
				else if (strcmp(classi, "전공필수") == 0)
				{
					if (strcmp(dept, deptname) == 0)tt.jp += subno;
					else tt.is += subno;
				}
				else if (strcmp(classi, "전공선택") == 0)
				{
					if (strcmp(dept, deptname) == 0)tt.js += subno;
					else tt.is += subno;
				}
				else if (strcmp(classi, "일반선택") == 0)
					tt.is += subno;
			}
			mysql_free_result(pSQL_result);

			printf("[|]%s, %s\n", stname, deptname);
			printf("[|]과목분류 : 사표 아잉 일세 핵교 전교 전필 전선 일선\n");
			printf("[|]이수기준 : %4d %4d %4d %4d %4d %4d %4d %4d\n", tott.sp, tott.ae, tott.fm, tott.hg, tott.jg, tott.jp, tott.js, tott.is);
			printf("[|]이수경과 : %4d %4d %4d %4d %4d %4d %4d %4d\n", tt.sp, tt.ae, tt.fm, tt.hg, tt.jg, tt.jp, tt.js, tt.is);
			printf("[|]필요학점 : %4d %4d %4d %4d %4d %4d %4d %4d\n"
				, tott.sp - tt.sp, tott.ae - tt.ae, tott.fm - tt.fm, tott.hg - tt.hg, tott.jg - tt.jg, tott.jp - tt.jp, tott.js - tt.js, tott.is - tt.is);

			continue;
		}

		int subjobno = subjobs();
		system("cls");
		if (jobno == 1)
		{
			if (subjobno == 1)
			{
				struct dept_db deptdb = subjob11();
				sprintf(szInsertQuery, "INSERT INTO 학과(학과명, 사고와표현, Academic_English, 1학년세미나, 핵심교양, 전공관련교양, 전공필수, 전공선택, 일반선택) VALUES('%s',%d,%d,%d,%d,%d,%d,%d,%d);",
					deptdb.name, deptdb.sapyo, deptdb.acdeng, deptdb.freshman, deptdb.hackgyo, deptdb.jeongyo, deptdb.jeonpil, deptdb.jeonson, deptdb.illson);
				insertflag = true;
			}
			else if (subjobno == 2)
			{
				char deptname[30];
				format_print("[-]삭제할 학과를 입력하세요 : ");
				scanf("%s", deptname);
				sprintf(szDeleteQuery, "DELETE FROM 학과 WHERE 학과명='%s'", deptname);
				deleteflag = true;
			}
			else if (subjobno == 3)
			{
				sprintf(szSelectQuery, "SELECT * FROM 학과");
				selectflag = true;
			}
		}

		else if (jobno == 2)
		{
			if (subjobno == 1)
			{
				struct subject_db subjectdb = subjob21();
				sprintf(szInsertQuery, "INSERT INTO 과목(과목명, 학과명, 분류, 학점수) VALUES('%s','%s','%s',%d);",
					subjectdb.name, subjectdb.dept, subjectdb.classify, subjectdb.num);
				insertflag = true;
			}
			else if (subjobno == 2)
			{
				char subjectname[30];
				format_print("\n\n");
				format_print("[-]삭제할 과목을 입력하세요 : ");
				scanf("%s", subjectname);
				sprintf(szDeleteQuery, "DELETE FROM 과목 WHERE 과목명='%s'", subjectname);
				deleteflag = true;
			}
			else if (subjobno == 3)
			{
				sprintf(szSelectQuery, "SELECT * FROM 과목");
				selectflag = true;
			}
		}

		else if (jobno == 3)
		{
			if (subjobno == 1)
			{
				struct student_db studentdb = subjob31();
				sprintf(szInsertQuery, "INSERT INTO 학생(학생이름, 학번, 학과) VALUES('%s','%s','%s');",
					studentdb.name, studentdb.studentno, studentdb.dept);
				insertflag = true;
			}
			else if (subjobno == 2)
			{
				char studentname[30], studentno[10];
				format_print("\n\n");
				format_print("[-]삭제할 학생이름과 학번을 입력하세요\n");
				format_print("[*]학생이름 : ");
				scanf("%s", studentname);
				format_print("[*]학번 : ");
				scanf("%s", studentno);
				sprintf(szDeleteQuery, "DELETE FROM 학생 WHERE 학생이름='%s' AND 학번='%s'", studentname, studentno);
				deleteflag = true;
			}
			else if (subjobno == 3)
			{
				sprintf(szSelectQuery, "SELECT * FROM 학생");
				selectflag = true;
			}
		}

		else if (jobno == 4)
		{
			if (subjobno == 1)
			{
				struct sugang_db sugangdb = subjob41();
				sprintf(szInsertQuery, "INSERT INTO 수강(학생이름, 과목명, 학기) VALUES('%s','%s',%d);",
					sugangdb.name, sugangdb.subject, sugangdb.semester);
				insertflag = true;
			}
			else if (subjobno == 2)
			{
				char studentname[30], subjectname[30];
				format_print("\n\n");
				format_print("[-]삭제할 학생이름과 과목명을 입력하세요 : ");
				format_print("[*]학생이름 : ");
				scanf("%s", studentname);
				format_print("[*]과목명 : ");
				scanf("%s", subjectname);
				sprintf(szDeleteQuery, "DELETE FROM 수강 WHERE 학생이름='%s' AND 과목명='%s'", studentname, subjectname);
				deleteflag = true;
			}
			else if (subjobno == 3)
			{
				sprintf(szSelectQuery, "SELECT * FROM 수강");
				selectflag = true;
			}
		}

		else
		{
			format_print("[-]Unjustifiable use Detected");
			break;
		}

		system("cls");
		if (insertflag)
		{
			nQuery_stat = mysql_query(pConnection, szInsertQuery);
			if (nQuery_stat != 0)
			{
				format_print("[-]Failed to send insert query\n");
				return -1;
			}
			format_print("\n\n");
			format_print("[+]Success to send insert query\n");
		}
		if (deleteflag)
		{
			nQuery_stat = mysql_query(pConnection, szDeleteQuery);
			if (nQuery_stat != 0)
			{
				format_print("[-]Failed to send delete query\n");
				return -1;
			}
			format_print("\n\n");
			format_print("[+]Success to send delete query\n");
		}
		if (selectflag)
		{
			format_print("\n\n\n");
			nQuery_stat = mysql_query(pConnection, szSelectQuery);
			if (nQuery_stat != 0)
			{
				format_print("[-]Failed to send select query\n");
				return -1;
			}
			pSQL_result = mysql_store_result(pConnection);
			while ((SQL_row = mysql_fetch_row(pSQL_result)) != NULL)
			{
				format_print("");
				if (jobno == 1)printf("[|]%s, %s, %s, %s, %s, %s, %s, %s, %s\n"
					, SQL_row[0], SQL_row[1], SQL_row[2], SQL_row[3], SQL_row[4]
					, SQL_row[5], SQL_row[6], SQL_row[7], SQL_row[8]);
				if (jobno == 2)printf("[|]%s, %s, %s, %s\n"
					, SQL_row[0], SQL_row[1], SQL_row[2], SQL_row[3]);
				if (jobno == 3)printf("[|]%s, %s, %s\n"
					, SQL_row[0], SQL_row[1], SQL_row[2]);
				if (jobno == 4)printf("[|]%s, %s, %s\n"
					, SQL_row[0], SQL_row[1], SQL_row[2]);
			}
			mysql_free_result(pSQL_result);
		}
	}

	format_print("[-]작업을 종료합니다.\n");
	mysql_close(pConnection);

}

int jobs()
{
	format_print("\n\n\n");
	format_print("[*]수강신청 로드맵\n");
	int jobnumber = 0;
	format_print("--------------------------------\n");
	format_print("[*]원하는 작업을 선택하세요\n");
	format_print("[1]학과 관련 작업\n");
	format_print("[2]과목 관련 작업\n");
	format_print("[3]학생 관련 작업\n");
	format_print("[4]수강 관련 작업\n");
	format_print("[5]이수 학점 출력\n");
	format_print("[6]작업 종료\n");
	format_print("--------------------------------\n");
	format_print("[+]작업 번호 입력 : ");
	scanf("%d", &jobnumber);
	if (jobnumber < 1 || jobnumber > 6)
	{
		format_print("[-]작업 번호 입력 오류\n");
		format_print("[+]작업 번호 입력 : ");
		scanf("%d", &jobnumber);
	}

	return jobnumber;
}

int subjobs()
{
	int jobnumber = 0;
	format_print("--------------------------------\n");
	format_print("[*]원하는 하위 작업을 선택하세요\n");
	format_print("[1]추가\n");
	format_print("[2]제거\n");
	format_print("[3]목록 출력\n");
	format_print("[4]작업 종료\n");
	format_print("--------------------------------\n");
	format_print("[+]작업 번호 입력 : ");
	scanf("%d", &jobnumber);
	if (jobnumber < 1 || jobnumber > 4)
	{
		format_print("[-]작업 번호 입력 오류\n");
		format_print("[+]작업 번호 입력 : ");
		scanf("%d", &jobnumber);
	}

	return jobnumber;
}