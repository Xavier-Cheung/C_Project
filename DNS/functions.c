
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include <process.h>
#include "definition.h"

#pragma  comment(lib, "Ws2_32.lib") //���� ws2_32.dll

extern Translate DNSTable[AMOUNT];		//DNS����������
extern IDTransform IDTransTable[AMOUNT];	//IDת����
extern int IDcount;					//ת�����е���Ŀ����
extern char Url[LENGTHOFURL];					//����
extern SYSTEMTIME TimeOfSys;                     //ϵͳʱ��
extern int Day, Hour, Minute, Second, Milliseconds;//����ϵͳʱ��ı���

//���ر���txt�ļ�
int InitialDNSTable(char* path)
{
	int i = 0, j = 0;
	int num = 0;
	char* Temp[AMOUNT];//char��ָ��1500����
	FILE* fp = fopen(path, "ab+");
	if (!fp)
	{
		printf("Open file failed.\n");
		exit(-1);
	}
	char* reac;
	while (i < AMOUNT - 1)//ʵ�ְ�ÿһ�зֿ��Ĳ���
	{
		Temp[i] = (char*)malloc(sizeof(char)*200);
		//Temp[200];
		//fscanf(fp, "%*c%*[^\n]", IPTemp[i]);
		if (fgets(Temp[i],1000,fp)== NULL)//���������߶������������ͷ���NULL��
			break;
		else
		{
			//reac = strchr(Temp[i], '\n');          //���һ��з�
			//if (reac)                            //���find��Ϊ��ָ��
			//	*reac = '\0';
			;//printf("%s", Temp[i]);
		}
		i++;
	}
	if (i == AMOUNT - 1)
		printf("The DNS record memory is full.\n");


	for (j; j < i; j++)//�����Ѹշֺõ�TEMP��i���ٴ��и��IP��domain
	{
		char* ex1 = strtok(Temp[j], " ");
		char* ex2 = strtok(NULL, " ");
		if (ex2 == NULL)
		{
			printf("The record is not in a correct format.\n");
		}
		else
		{

			DNSTable[j].IP = ex1;
			DNSTable[j].domain = ex2;
			//DNSTable[j].IP[strlen(DNSTable[j].IP) - 1] = 0;

			//DNSTable[j].domain[strlen(DNSTable[j].domain) - 1] = '\0';
			//printf("%d\n%s\n%s\n",j, DNSTable[j].IP, DNSTable[j].domain);
			//printf("%d %s %s\n", j,  Temp[j], DNSTable[j].domain);
			num++;
		}
	}

	//printf("%d\n", num);
    //
	fclose(fp);
	printf("Load records success.\n");
	return num;
}

//��ȡDNS�����е�����
void GetUrl(char* recvbuf, int recvnum)
{
	char urlname[LENGTHOFURL];
	int i = 0, j, k = 0;

	memset(Url, 0, LENGTHOFURL); //ȫ��0��ʼ��
	memcpy(urlname, &(recvbuf[sizeof(DNSHDR)]), recvnum - 12);	//��ȡ�������е�������ʾ��Ҫȥ��DNS�����ײ���12�ֽ�

	int len = strlen(urlname);

	//����ת��
	while (i < len)
	{
		if (urlname[i] > 0 && urlname[i] <= 63)
			for (j = urlname[i], i++; j > 0; j--, i++, k++)
				Url[k] = urlname[i];

		if (urlname[i] != 0)
		{
			Url[k] = '.';
			k++;
		}
	}

	Url[k] = '\0';
}

//�ж��ܲ����ڱ����ҵ�DNS�����е��������ҵ������±�
int IsFind(char* url, int num)
{
	int find = NOTFOUND;
	char* domain;

	char* NUrl;
	NUrl = (char*)malloc(sizeof(char)*210);
	strcpy(NUrl, url);
	strcat(NUrl, "\r\n");

	//printf("URL: %sabab\n", url);
	//printf("%sabab\n", DNSTable[20].domain);

	for (int i = 0; i < num+2; i++)
	{
		if (DNSTable[i].domain)
		{
			domain = DNSTable[i].domain;
			/*printf("%s", domain);
			printf("%s", NUrl);
			printf("%d\n", strcmp(domain, NUrl));
			printf("wwwwwwwwwwwwwwwwwwwwwwwwwwww\n");*/

			if (strcmp(domain, NUrl) == 0)
			{
				//printf("!~!FOUND!~!\n");
				find = i;
				break;
			}
		}
	}

	//printf("find:%d\n", find);

	return find;
}

//������IDת��Ϊ�µ�ID��������Ϣд��IDת������
unsigned short ReplaceNewID(unsigned short OldID, SOCKADDR_IN temp, BOOL ifdone)
{
	srand(time(NULL)); //���������
	IDTransTable[IDcount].oldID = OldID;
	IDTransTable[IDcount].client = temp;
	IDTransTable[IDcount].done = ifdone;
	IDcount++; //IDת������ĿҪ����~

	return (unsigned short)(IDcount - 1);	//�Ա����±���Ϊ�µ�ID
}

//��ӡ ʱ�� newID ���� ���� IP
void PrintInfo(unsigned short newID, int find)
{
	//��ӡʱ��
	GetLocalTime(&TimeOfSys);
	//���ָ�����ȵ��ַ���, ����ʱ���ض�, ����ʱ�����:
	//printf("%-ns", str);            --n Ϊָ�����ȵ�10������ֵ
	int Btime;
	int Ltime;
	Btime = ((((TimeOfSys.wDay - Day) * 24 + TimeOfSys.wHour - Hour) * 60 + TimeOfSys.wMinute - Minute) * 60) + TimeOfSys.wSecond - Second;
	Ltime = abs(TimeOfSys.wMilliseconds - Milliseconds);
	printf("%d.%d   %d", Btime, Ltime, newID);
	printf("    ");

	//�ڱ���û���ҵ�DNS�����е�����
	if (find == NOTFOUND)
	{
		//�м̹���
		printf("�м�");
		printf("    ");
		//��ӡ����
		printf("%s",Url);
		printf("    ");
		//��ӡIP
		printf("\n");
	}

	//�ڱ����ҵ�DNS�����е�����
	else
	{
		if (strcmp(DNSTable[find].IP, "0.0.0.0") == 0)  //������վ����
		{
			//���ι���
			printf("����");
			printf("    ");
			//��ӡ����(��*)
			//��ӡ����
			printf("***%s", Url);
			printf("    ");
			//��ӡIP
			printf("%s\n", DNSTable[find].IP);
		}

		//�������Ϊ��ͨIP��ַ������ͻ����������ַ
		else
		{
			//����������
			printf("Local������");
			printf("    ");
			//��ӡ����
			printf("***%s", Url);
			printf("    ");
			//��ӡIP
			printf("%s\n", DNSTable[find].IP);
		}
	}
}