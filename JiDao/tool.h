#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct stopStatus{
	int clockwise;
	int counterclockwise;
	int target;
	int clocktime;
	int countertime;
	int targettime;
};
typedef struct stopStatus station;
struct quest{
	int stop;
	int direction;
	struct quest*next;
};
typedef struct quest quest;
void output(int pos,station bay[],int time,int stop)
{//�˲���Ϊ������д
    printf("TIME:%d\n",time);
    printf("BUS:\n");
    printf("position:%d\n",pos);
    printf("target:");
    for (int i=1;i<=stop;i++){
        printf("%d",bay[i].target);
    }
    printf("\n");
    printf("STATION:\n");
    printf("clockwise:");
    for (int i=1;i<=stop;i++){
        printf("%d",bay[i].clockwise);
    }
    printf("\n");
    printf("counterclockwise:");
    for (int i=1;i<=stop;i++){
        printf("%d",bay[i].counterclockwise);
    }
    printf("\n");
}
int statusRead(char inS[],int*inA,station bay[],int time,int*questflag){//�˲���Ϊ������д
    scanf("%s",inS);
    if(strcmp(inS,"end")==0){
        return 0;//����Ѿ����������ٶ��� 
    }
    else{
        if(strcmp(inS,"clock")!=0){//�������룬���Ϊclock�򲻶������� 
            scanf("%d",inA);
            if(strcmp(inS,"clockwise")==0&&bay[*inA].clockwise!=1){
                bay[*inA].clockwise=1;//��Ӧվ��Ķ�Ӧ�����Ϊ1
                bay[*inA].clocktime=time;
                (*questflag)++; 
            }
            else if(strcmp(inS,"counterclockwise")==0&&bay[*inA].counterclockwise!=1){
                bay[*inA].counterclockwise=1;
                bay[*inA].countertime=time;
                (*questflag)++;
            }
            else if(strcmp(inS,"target")==0&&bay[*inA].target!=1){
                bay[*inA].target=1;
                bay[*inA].targettime=time;
                (*questflag)++;
            }
        }
    }
    return 1;//��������
}
void delet(quest *headPtr,station bay[])//ɾ������ɵ�����
{//�˲����ɷ�����д
    quest *tempPtr1=NULL,*tempPtr2=NULL;
    tempPtr1=headPtr->next;
    int task=0;
    task=headPtr->next->stop;
    while (tempPtr1!=NULL){
         if (tempPtr1->stop==task){//�����Ƿ��к͵�ǰ����ɵ�������ͬ����������
            switch (tempPtr1->direction)
            {
            case 1:
                bay[tempPtr1->stop].clockwise=0;
                break;
            case -1:
                bay[tempPtr1->stop].counterclockwise=0;
                break;
            case 0:
                bay[tempPtr1->stop].target=0;
                break;
            default:
                break;
            }
            tempPtr2=tempPtr1;
            headPtr->next=tempPtr1->next;
            tempPtr1=tempPtr1->next;
            free(tempPtr2);
        }
        else {
            break;
        }
    }
}
