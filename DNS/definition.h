#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <iomanip>
#include <WinSock2.h>
#include <windows.h>
#include <time.h>

#define BUFSIZE 1024 //����Ļ����С
#define PORT 53   //53�˿ں�
#define DEF_DNS_ADDRESS "223.5.5.5"	//ipconfig/all ��֪�ⲿ������dns��ַ
#define LOCAL_DNS_ADDRESS "127.0.0.1" //����DNS��������ַ
#define AMOUNT 1500//���IDת�����С
#define NOTFOUND 32767 //û���ҵ�
#define LENGTHOFURL 64 //0~63

//DNS�����ײ� 12�ֽ�
typedef struct DNSHeader
{
	unsigned short ID; //��־
	unsigned short Flags; //��ʶ
	unsigned short QuestionNum;  //������
	unsigned short AnswerNum; //��Դ��¼��
	unsigned short AuthorNum; //��Ȩ��Դ��¼��
	unsigned short AdditionNum; //������Դ��¼��
} DNSHDR, * pDNSHDR;

//DNS����������ṹ
typedef struct translate
{
	char * IP;						//IP��ַ
	char * domain;					//����
} Translate;

//IDת����ṹ
typedef struct IDChange
{
	unsigned short oldID;			//ԭ��ID
	BOOL done;						//����Ƿ���ɽ���
	SOCKADDR_IN client;				//�������׽��ֵ�ַ
} IDTransform;



#endif // DEFINITION_H_INCLUDED