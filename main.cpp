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
	printf("[*]��й�ȣ�� �Է��ϼ��� : ");
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
			format_print("[*]�й� : ");
			scanf("%s", stunum);
			system("cls");
			struct timetable tt = { 0,0,0,0,0,0,0,0 };
			struct timetable tott = { 0,0,0,0,0,0,0,0 };
			sprintf(szSelectQuery, "SELECT �а�.*, �л�.�л��̸� FROM �а�, �л� WHERE �й�='%s' AND �а�=�а���", stunum);
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

			sprintf(szSelectQuery, "SELECT ����.*, ����.�б� FROM ����,�л�,�а�,���� WHERE �л�.�й�='%s' AND �л�.�л��̸�=����.�л��̸� AND ����.�����=����.�����", stunum);
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
				if (strcmp(classi, "����ǥ��") == 0)
					tt.sp += subno;
				else if (strcmp(classi, "Academic_English") == 0)
					tt.ae += subno;
				else if (strcmp(classi, "1�г⼼�̳�") == 0)
					tt.fm += subno;
				else if (strcmp(classi, "�ٽɱ���") == 0)
					tt.hg += subno;
				else if (strcmp(classi, "�������ñ���") == 0)
					tt.jg += subno;
				else if (strcmp(classi, "�����ʼ�") == 0)
				{
					if (strcmp(dept, deptname) == 0)tt.jp += subno;
					else tt.is += subno;
				}
				else if (strcmp(classi, "��������") == 0)
				{
					if (strcmp(dept, deptname) == 0)tt.js += subno;
					else tt.is += subno;
				}
				else if (strcmp(classi, "�Ϲݼ���") == 0)
					tt.is += subno;
			}
			mysql_free_result(pSQL_result);

			printf("[|]%s, %s\n", stname, deptname);
			printf("[|]����з� : ��ǥ ���� �ϼ� �ٱ� ���� ���� ���� �ϼ�\n");
			printf("[|]�̼����� : %4d %4d %4d %4d %4d %4d %4d %4d\n", tott.sp, tott.ae, tott.fm, tott.hg, tott.jg, tott.jp, tott.js, tott.is);
			printf("[|]�̼���� : %4d %4d %4d %4d %4d %4d %4d %4d\n", tt.sp, tt.ae, tt.fm, tt.hg, tt.jg, tt.jp, tt.js, tt.is);
			printf("[|]�ʿ����� : %4d %4d %4d %4d %4d %4d %4d %4d\n"
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
				sprintf(szInsertQuery, "INSERT INTO �а�(�а���, ����ǥ��, Academic_English, 1�г⼼�̳�, �ٽɱ���, �������ñ���, �����ʼ�, ��������, �Ϲݼ���) VALUES('%s',%d,%d,%d,%d,%d,%d,%d,%d);",
					deptdb.name, deptdb.sapyo, deptdb.acdeng, deptdb.freshman, deptdb.hackgyo, deptdb.jeongyo, deptdb.jeonpil, deptdb.jeonson, deptdb.illson);
				insertflag = true;
			}
			else if (subjobno == 2)
			{
				char deptname[30];
				format_print("[-]������ �а��� �Է��ϼ��� : ");
				scanf("%s", deptname);
				sprintf(szDeleteQuery, "DELETE FROM �а� WHERE �а���='%s'", deptname);
				deleteflag = true;
			}
			else if (subjobno == 3)
			{
				sprintf(szSelectQuery, "SELECT * FROM �а�");
				selectflag = true;
			}
		}

		else if (jobno == 2)
		{
			if (subjobno == 1)
			{
				struct subject_db subjectdb = subjob21();
				sprintf(szInsertQuery, "INSERT INTO ����(�����, �а���, �з�, ������) VALUES('%s','%s','%s',%d);",
					subjectdb.name, subjectdb.dept, subjectdb.classify, subjectdb.num);
				insertflag = true;
			}
			else if (subjobno == 2)
			{
				char subjectname[30];
				format_print("\n\n");
				format_print("[-]������ ������ �Է��ϼ��� : ");
				scanf("%s", subjectname);
				sprintf(szDeleteQuery, "DELETE FROM ���� WHERE �����='%s'", subjectname);
				deleteflag = true;
			}
			else if (subjobno == 3)
			{
				sprintf(szSelectQuery, "SELECT * FROM ����");
				selectflag = true;
			}
		}

		else if (jobno == 3)
		{
			if (subjobno == 1)
			{
				struct student_db studentdb = subjob31();
				sprintf(szInsertQuery, "INSERT INTO �л�(�л��̸�, �й�, �а�) VALUES('%s','%s','%s');",
					studentdb.name, studentdb.studentno, studentdb.dept);
				insertflag = true;
			}
			else if (subjobno == 2)
			{
				char studentname[30], studentno[10];
				format_print("\n\n");
				format_print("[-]������ �л��̸��� �й��� �Է��ϼ���\n");
				format_print("[*]�л��̸� : ");
				scanf("%s", studentname);
				format_print("[*]�й� : ");
				scanf("%s", studentno);
				sprintf(szDeleteQuery, "DELETE FROM �л� WHERE �л��̸�='%s' AND �й�='%s'", studentname, studentno);
				deleteflag = true;
			}
			else if (subjobno == 3)
			{
				sprintf(szSelectQuery, "SELECT * FROM �л�");
				selectflag = true;
			}
		}

		else if (jobno == 4)
		{
			if (subjobno == 1)
			{
				struct sugang_db sugangdb = subjob41();
				sprintf(szInsertQuery, "INSERT INTO ����(�л��̸�, �����, �б�) VALUES('%s','%s',%d);",
					sugangdb.name, sugangdb.subject, sugangdb.semester);
				insertflag = true;
			}
			else if (subjobno == 2)
			{
				char studentname[30], subjectname[30];
				format_print("\n\n");
				format_print("[-]������ �л��̸��� ������� �Է��ϼ��� : ");
				format_print("[*]�л��̸� : ");
				scanf("%s", studentname);
				format_print("[*]����� : ");
				scanf("%s", subjectname);
				sprintf(szDeleteQuery, "DELETE FROM ���� WHERE �л��̸�='%s' AND �����='%s'", studentname, subjectname);
				deleteflag = true;
			}
			else if (subjobno == 3)
			{
				sprintf(szSelectQuery, "SELECT * FROM ����");
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

	format_print("[-]�۾��� �����մϴ�.\n");
	mysql_close(pConnection);

}

int jobs()
{
	format_print("\n\n\n");
	format_print("[*]������û �ε��\n");
	int jobnumber = 0;
	format_print("--------------------------------\n");
	format_print("[*]���ϴ� �۾��� �����ϼ���\n");
	format_print("[1]�а� ���� �۾�\n");
	format_print("[2]���� ���� �۾�\n");
	format_print("[3]�л� ���� �۾�\n");
	format_print("[4]���� ���� �۾�\n");
	format_print("[5]�̼� ���� ���\n");
	format_print("[6]�۾� ����\n");
	format_print("--------------------------------\n");
	format_print("[+]�۾� ��ȣ �Է� : ");
	scanf("%d", &jobnumber);
	if (jobnumber < 1 || jobnumber > 6)
	{
		format_print("[-]�۾� ��ȣ �Է� ����\n");
		format_print("[+]�۾� ��ȣ �Է� : ");
		scanf("%d", &jobnumber);
	}

	return jobnumber;
}

int subjobs()
{
	int jobnumber = 0;
	format_print("--------------------------------\n");
	format_print("[*]���ϴ� ���� �۾��� �����ϼ���\n");
	format_print("[1]�߰�\n");
	format_print("[2]����\n");
	format_print("[3]��� ���\n");
	format_print("[4]�۾� ����\n");
	format_print("--------------------------------\n");
	format_print("[+]�۾� ��ȣ �Է� : ");
	scanf("%d", &jobnumber);
	if (jobnumber < 1 || jobnumber > 4)
	{
		format_print("[-]�۾� ��ȣ �Է� ����\n");
		format_print("[+]�۾� ��ȣ �Է� : ");
		scanf("%d", &jobnumber);
	}

	return jobnumber;
}