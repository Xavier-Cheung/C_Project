#include<stdio.h>
#include<stdlib.h>
#include"tool.h"
void FCFS(int stop,int distance,station bay[]);
quest *fcfs(quest *lastPtr,int inA,station bay[],quest *headPtr,char inS[]);
int posJudge(int pos,int direction,int len);
quest *refindLastPtr(quest *headPtr,quest *lastPtr);
int dirJudge(int pos,int destination,int len);

void FCFS(int stop,int distance,station bay[])
{
    char inS[20];//���������
    int pos=0,time=0,flag=0,direction=0,destination=0,len=0,questflag=0,inA=0;
    len=stop*distance-1;
    quest *headPtr=NULL,*lastPtr=NULL;
    headPtr=(quest *)malloc(sizeof(quest));
    headPtr->next=NULL;
    headPtr->stop=-1;
    lastPtr=headPtr;
    output(pos,bay,time,stop);//��ʱ��״̬���
 
    while (statusRead(inS,&inA,bay,time,&questflag)==1){
        if (flag==0&&headPtr->next!=NULL){//��ǰ������ִ�е������Ҵ���δִ�е�����
            destination=(headPtr->next->stop-1)*distance;//�����յ�վ
            direction=dirJudge(pos,destination,len);
            flag=1;
            }
        if (flag==0&&headPtr->next==NULL) {//������Ŷ�������ԭ�ز���
            direction=0;
        }
        if (strcmp(inS,"clock")!=0){//�ӵ�����
            lastPtr=fcfs(lastPtr,inA,bay,headPtr,inS);//�������ӵ�����
        }
        else {//����clock�����״̬��TIME��һ
            time++;
            pos=posJudge(pos,direction,len);//λ�øı�
            output(pos,bay,time,stop);
        }
        if (pos==destination&&flag==1){//����Ŀ��վ��
            time++;//ͣһ����ɷ���
            while (statusRead(inS,&inA,bay,time,&questflag)==1){
                if (strcmp(inS,"clock")==0){
                    break;
                }
                else {
                    lastPtr=fcfs(lastPtr,inA,bay,headPtr,inS);//���ӵ����� 
                }
            }
            direction=0;
            destination=0;
            delet(headPtr,bay);//ɾ�����������
            lastPtr=refindLastPtr(headPtr,lastPtr);
            flag=0;
            output(pos,bay,time,stop);
        }
    }
    printf("end\n");
}

quest *fcfs(quest *lastPtr,int inA,station bay[],quest *headPtr,char inS[])
{
    int add=1;
    quest *tempPtr=NULL;
    tempPtr=headPtr;
    if (strcmp(inS,"clockwise")==0){
        while (tempPtr!=NULL){//�����Ƿ������ͬ����
            if (tempPtr->stop==inA&&tempPtr->direction==1){
                add=0;
                break;
            }
            tempPtr=tempPtr->next;
        }
    }
    if (strcmp(inS,"counterclockwise")==0){
        while (tempPtr!=NULL){
            if (tempPtr->stop==inA&&tempPtr->direction==-1){
                add=0;
                break;
            }
            tempPtr=tempPtr->next;
        }
    }
    if (strcmp(inS,"target")==0){
        while (tempPtr!=NULL){
            if (tempPtr->stop==inA&&tempPtr->direction==0){
                add=0;
                break;
            }
        tempPtr=tempPtr->next;
        }
    }
    if (add==1){
        quest *tempPtr=NULL;
        tempPtr=(quest *)malloc(sizeof(quest));
        tempPtr->stop=inA;
        if (strcmp(inS,"clockwise")==0){
            tempPtr->direction=1;
        }
        else if (strcmp(inS,"counterclockwise")==0){
            tempPtr->direction=-1;
        }
        else {
            tempPtr->direction=0;//˵����target
        }
        tempPtr->next=NULL;
        lastPtr->next=tempPtr;
        lastPtr=tempPtr;
    }
    return lastPtr;
}
int posJudge(int pos,int direction,int len)
{
    pos+=direction;
    if (pos==-1){
        pos=len;
    }
    if (pos==len+1){
        pos=0;
    }
    return pos;
}
quest *refindLastPtr(quest *headPtr,quest *lastPtr)
{
    quest *tempPtr=NULL;
    tempPtr=headPtr;
    while (tempPtr->next!=NULL){
        tempPtr=tempPtr->next; 
    }
    return tempPtr;
}
int dirJudge(int pos,int destination,int len)
{   int s=0,direction=0;
    if (destination>pos){
        s=destination-pos;
    }
    else {
        s=len-pos+destination+1;
    }
    if (s<=(len+1)/2){
        direction=1;
    }
    else {
        direction=-1;
    }
    return direction;
}
