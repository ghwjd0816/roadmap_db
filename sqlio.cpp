#include "sqlio.h"

const char *classified[8] = { "사고와표현", "Academic_English", "1학년세미나", "핵심교양", "전공관련교양", "전공필수", "전공선택", "일반선택" };

dept_db subjob11()
{
	system("cls");
	struct dept_db temp;
	format_print("\n\n\n");
	format_print("--------------------------------\n");
	format_print("[*]학과 추가\n");
	format_print("[+]학과명 : ");
	scanf("%s", temp.name);
	format_print("[+]사고와 표현 학점 : ");
	scanf("%d", &temp.sapyo);
	format_print("[+]Academic English 학점 : ");
	scanf("%d", &temp.acdeng);
	format_print("[+]1학년세미나 학점 : ");
	scanf("%d", &temp.freshman);
	format_print("[+]핵심교양 학점 : ");
	scanf("%d", &temp.hackgyo);
	format_print("[+]전공관련교양 학점 : ");
	scanf("%d", &temp.jeongyo);
	format_print("[+]전공필수 학점 : ");
	scanf("%d", &temp.jeonpil);
	format_print("[+]전공선택 학점 : ");
	scanf("%d", &temp.jeonson);
	format_print("[+]일반선택 학점 : ");
	scanf("%d", &temp.illson);
	format_print("--------------------------------\n");
	format_print("[*]다시 입력하시겠습니까?(y/n) ");
	char re;
	scanf(" %c", &re);
	if (re == 'y' || re == 'Y')return subjob11();
	return temp;
}

subject_db subjob21()
{
	system("cls");
	struct subject_db temp;
	format_print("\n\n\n");
	format_print("--------------------------------\n");
	format_print("[*]과목 추가\n");
	format_print("[+]과목명 : ");
	scanf("%s", temp.name);
	format_print("[+]학과명 : ");
	scanf("%s", temp.dept);
	format_print("[+]분류 : ");
	scanf("%s", temp.classify);
	format_print("[+]학점수 : ");
	scanf("%d", &temp.num);
	format_print("--------------------------------\n");
	int i = 0;
	for (; i < 8; i++)
	{
		if (strcmp(temp.classify, classified[i]))break;
	}
	if (i == 8)format_print("[-]분류 오류. 재입력 요망\n");
	format_print("[*]다시 입력하시겠습니까?(y/n) ");
	char re;
	scanf(" %c", &re);
	if (re == 'y' || re == 'Y')return subjob21();
	return temp;
}

student_db subjob31()
{
	system("cls");
	struct student_db temp;
	format_print("\n\n\n");
	format_print("--------------------------------\n");
	format_print("[*]학생 추가\n");
	format_print("[+]학생이름 : ");
	scanf("%s", temp.name);
	format_print("[+]학번 : ");
	scanf("%s", temp.studentno);
	format_print("[+]학과 : ");
	scanf("%s", temp.dept);
	format_print("--------------------------------\n");
	format_print("[*]다시 입력하시겠습니까?(y/n) ");
	char re;
	scanf(" %c", &re);
	if (re == 'y' || re == 'Y')return subjob31();
	return temp;
}

sugang_db subjob41()
{
	system("cls");
	struct sugang_db temp;
	format_print("\n\n\n");
	format_print("--------------------------------\n");
	format_print("[*]수강 추가\n");
	format_print("[+]학생이름 : ");
	scanf("%s", temp.name);
	format_print("[+]과목명 : ");
	scanf("%s", temp.subject);
	format_print("[+]학기 : ");
	scanf("%d", &temp.semester);
	format_print("--------------------------------\n");
	format_print("[*]다시 입력하시겠습니까?(y/n) ");
	char re;
	scanf(" %c", &re);
	if (re == 'y' || re == 'Y')return subjob41();
	return temp;
}

void format_print(char *c)
{
	printf("       \t\t\t\t\t%s", c);
}