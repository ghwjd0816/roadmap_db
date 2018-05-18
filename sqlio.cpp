#include "sqlio.h"

const char *classified[8] = { "����ǥ��", "Academic_English", "1�г⼼�̳�", "�ٽɱ���", "�������ñ���", "�����ʼ�", "��������", "�Ϲݼ���" };

dept_db subjob11()
{
	system("cls");
	struct dept_db temp;
	format_print("\n\n\n");
	format_print("--------------------------------\n");
	format_print("[*]�а� �߰�\n");
	format_print("[+]�а��� : ");
	scanf("%s", temp.name);
	format_print("[+]���� ǥ�� ���� : ");
	scanf("%d", &temp.sapyo);
	format_print("[+]Academic English ���� : ");
	scanf("%d", &temp.acdeng);
	format_print("[+]1�г⼼�̳� ���� : ");
	scanf("%d", &temp.freshman);
	format_print("[+]�ٽɱ��� ���� : ");
	scanf("%d", &temp.hackgyo);
	format_print("[+]�������ñ��� ���� : ");
	scanf("%d", &temp.jeongyo);
	format_print("[+]�����ʼ� ���� : ");
	scanf("%d", &temp.jeonpil);
	format_print("[+]�������� ���� : ");
	scanf("%d", &temp.jeonson);
	format_print("[+]�Ϲݼ��� ���� : ");
	scanf("%d", &temp.illson);
	format_print("--------------------------------\n");
	format_print("[*]�ٽ� �Է��Ͻðڽ��ϱ�?(y/n) ");
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
	format_print("[*]���� �߰�\n");
	format_print("[+]����� : ");
	scanf("%s", temp.name);
	format_print("[+]�а��� : ");
	scanf("%s", temp.dept);
	format_print("[+]�з� : ");
	scanf("%s", temp.classify);
	format_print("[+]������ : ");
	scanf("%d", &temp.num);
	format_print("--------------------------------\n");
	int i = 0;
	for (; i < 8; i++)
	{
		if (strcmp(temp.classify, classified[i]))break;
	}
	if (i == 8)format_print("[-]�з� ����. ���Է� ���\n");
	format_print("[*]�ٽ� �Է��Ͻðڽ��ϱ�?(y/n) ");
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
	format_print("[*]�л� �߰�\n");
	format_print("[+]�л��̸� : ");
	scanf("%s", temp.name);
	format_print("[+]�й� : ");
	scanf("%s", temp.studentno);
	format_print("[+]�а� : ");
	scanf("%s", temp.dept);
	format_print("--------------------------------\n");
	format_print("[*]�ٽ� �Է��Ͻðڽ��ϱ�?(y/n) ");
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
	format_print("[*]���� �߰�\n");
	format_print("[+]�л��̸� : ");
	scanf("%s", temp.name);
	format_print("[+]����� : ");
	scanf("%s", temp.subject);
	format_print("[+]�б� : ");
	scanf("%d", &temp.semester);
	format_print("--------------------------------\n");
	format_print("[*]�ٽ� �Է��Ͻðڽ��ϱ�?(y/n) ");
	char re;
	scanf(" %c", &re);
	if (re == 'y' || re == 'Y')return subjob41();
	return temp;
}

void format_print(char *c)
{
	printf("       \t\t\t\t\t%s", c);
}