#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define length 3

typedef struct record											//一条记录的结构体
{
	long long int number;
	char name[100];
}REC;
REC person[length];
int no=0;
int fullflag=0;

void menu()
{
	printf("\t\t 欢迎进入迷你电话簿管理系统\n");
	
	printf("***************************MENU*****************************\n");
	printf("*** 1. 添加一条电话簿记录                                ***\n");
	printf("*** 2. 按姓名查找电话号码                                ***\n");
	printf("*** 3. 删除一条电话簿记录                                ***\n");
	printf("*** 4. 修改一条电话簿记录                                ***\n");
	printf("*** 5. 显示所有电话簿记录                                ***\n");
	printf("*** 6. 保存到文件                                        ***\n");
	printf("*** 7. 打开文件                                          ***\n");
	printf("*** 0. 退出                                              ***\n");
	printf("************************************************************\n");
}

void newguy()													//添加一条电话簿记录
{	
	int i; 
	if(no<=length-1&&fullflag==0){
	
		printf("input name:");
		gets(person[no].name);
		printf("input number:");
		scanf("%lld", &person[no].number);
		no++;
		printf("complete!\n");
	}
	else {
		fullflag=1;
		for(i=0;i<=length-1;i++)
		{
			if(person[i].name[0]=='0')
			{
				printf("input name:");
				gets(person[i].name);
				printf("input number:");
				scanf("%lld", &person[i].number);
				printf("complete!\n");
				break;
			}
		}
		if(i==length) printf("The notebook is full!\n");
	}
	
}

void num(char name[])											//按姓名查找电话
{
	int i,m;
	for (i = 0;i <= length-1; i++)
	{
		m = strcmp(name, person[i].name);
		if (m == 0) { printf("His/Her number is:%lld\n", person[i].number);	break; }
		if (i == length-1 && m != 0) printf("This person is not included.\n");
		else continue;
	}
}

void dele()														//删除一条电话簿记录
{
	char name[100];
	int m, i;
	printf("input the name you want to delete:");
	gets(name);
	for (i = 0;i <= length-1; i++)
	{
		m = strcmp(name, person[i].name);
		if (m == 0) 
		{ person[i].number = 0;
		person[i].name[0] = '0'; 
		printf("complete!\n");
		break;
		}
		if (i == length-1 && m != 0) printf("This person is not included\n");
		else continue;
	}
}

void edit()														//修改一条电话簿记录
{
	int i,m;
	char name[100];
	printf("input the name of the person you want to edit:");
	gets(name);
	for (i = 0;i <= length-1; i++)
	{
		m = strcmp(name, person[i].name);
		if (m == 0)
		{
			printf("input his/her new name:");
			gets(person[i].name);
			printf("input his/her new number:");
			scanf("%lld", &person[i].number);
			printf("complete!\n");
			break;
		}
		if (i == length-1 && m != 0) printf("This person is not included.\n");
		else continue;
	}
}

void output()													//输出所有电话簿记录
{
	int a;
	for (a = 0;a <(no<=length?no:length);a++)
	{
		if (person[a].name[0] == '0') continue;
		printf("person code%d:%s\n", a+1, person[a].name);
		printf("His/Her number is:%lld\n\n", person[a].number);
	}
	printf("Complete!\n");
}

void out()														//保存电话簿记录到文件
{
	FILE* fp;
	int  i;
	char filename[50];
	printf("input filename to save:");
	gets(filename);
	if ((fp = fopen(filename, "wb")) == NULL)
	{
		printf("Cannot open file\n");
		return;
	}
	for (i = 0;i < length;i++)
		if (fwrite(&person[i], sizeof(REC), 1, fp) != 1)
			printf("File write error\n");
	fclose(fp);
}

void in()														//从文件读出电话簿记录
{
	FILE* fp;
	int  i;
	char filename[50];
	printf("input filename to open:");
	scanf("%s", filename);
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("cannot open file\n");
		return;
	}
	for (i = 0;i < length;i++)
	{
		fread(&person[i], sizeof(REC), 1, fp);
		printf("%-10s %lld\n", person[i].name, person[i].number);
		if(no<=length-1) no++; 
	}
	fclose(fp);	
} 

int main()
{
	int key = 1;
	char name[100];
	while (1)
	{
		system("cls");
		menu();
		printf("请输入数字选择对应功能：");
		scanf("%d", &key);
		getchar();
		switch (key)
		{
		case 1: newguy(); break;										//新增一条电话簿记录
		case 2:
		{	
			printf("input name to search:");
			gets( name);
			num(name);

		}
			break;														//按姓名查询电话号码 
		case 3:	dele(); break;											//删除一条电话簿记录
		case 4: edit();	break;											//修改一条电话簿记录
		case 5: output();  break;										//输出所有电话簿记录
		case 6:	out();  break;											//保存电话簿记录到文件
		case 7:	in();  break;											//从文件读出电话簿记录
		case 0:	printf("欢迎下次使用！\n");   return 0;
		default:printf("不存在该数字对应的功能，请重新输入！\n");
		}
		system("pause");
	}

	return 0;
} 
