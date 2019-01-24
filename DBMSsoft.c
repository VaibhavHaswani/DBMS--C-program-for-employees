#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
void gotoxy(int x,int y)
{
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
main()
{
	struct emp{
		char name[20];
		int age;
		float bs;
	};
	FILE *fp,*ft;
	struct emp e;
	long int recsize;
	char empname[20];
	char a,choice;
	fp=fopen("emp.dat","rb+");
	recsize=sizeof(e);
	if(fp==NULL)
	{
		fp=fopen("emp.dat","wb+");
		if(fp==NULL)
		{
			printf("error loading file..");
			exit(1);
		}
	}
	while(1)
	{
		system("cls");
		gotoxy(45,2);
		printf("'DOS DBMS Software (v1.0)'\n");
		gotoxy(50,4);
		printf("1). Add Entries");
		gotoxy(50,6);
		printf("2). List Entries");
		gotoxy(50,8);
		printf("3). Modify Entries");
		gotoxy(50,10);
		printf("4). Delete Entries");
		gotoxy(50,12);
		printf("0). Exit");
		gotoxy(54,14);
		printf("Select Option:\n");
		fflush(stdin);
		choice=getch();
		switch(choice)
		{
			case '1':
				printf("Add new entries-\n");
				a='y';
				fseek(fp,0,SEEK_END);
				while(a=='y' || a=='n')
				{
					if(a=='n')
					break;
					printf("NAME:");
					scanf("%[^\n]s",&e.name);
					printf("Age:");
					scanf("%d",&e.age);
					printf("Salary:");
					scanf("%f",&e.bs);
					fwrite(&e,recsize,1,fp);
					printf("Add more entries? (y/n):\n");
					fflush(stdin);
					a=getch();
				}
				break;
			case '2':
			rewind(fp);
			while(fread(&e,recsize,1,fp)==1)
			{
			printf("Name:%s \t Age:%d \t Salary:%f\n",e.name,e.age,e.bs);
		    }
		    getch();
			break;
		    case '3':
		    	do
		    	{
		    		rewind(fp);
		    		printf("Enter name of employee to modify details:");
		    	    scanf("%[^\n]s",&empname);
				while(fread(&e,recsize,1,fp)==1)
		    	{
		    		if(strcmp(empname,e.name)==0)
		    		{
		    		 printf("Enter New details-\n");
		    		fflush(stdin);
					 printf("Name:");
					 scanf("%[^\n]s",&e.name);
					 printf("Age:");
					 scanf("%d",&e.age);
					 printf("Salary:");
					 scanf("%f",&e.bs);
					 fseek(fp,-recsize,SEEK_CUR);
					 fwrite(&e,recsize,1,fp);
					 break;	
					}
				}
				printf("Modify more details?(y/n)\n");
					fflush(stdin);
					a=getch();
			}while(a=='y');
			break;	
		case '4':
		    do{
		    	rewind(fp);
		    	ft=fopen("temp.dat","wb");
		    	printf("Enter name of employee to delete:");
		    	scanf("%[^\n]s",&empname);
		    	while(fread(&e,recsize,1,fp)==1)
		    	{
		    		if(strcmp(empname,e.name)!=0)
		    		{
		    			fwrite(&e,recsize,1,ft);
					}
				}
				fclose(fp);
				fclose(ft);
				remove("emp.dat");
				rename("temp.dat","emp.dat");
				fp=fopen("emp.dat","rb+");
				printf("Delete more records? (y/n)");
				fflush(stdin);
				a=getch();
			}while(a=='y');
			break;
		case '0':
		fclose(fp);
		exit(0);	
		}
	}
}
