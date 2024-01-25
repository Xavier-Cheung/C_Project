#include<stdio.h>
#include<stdlib.h>
#include"tool.h"
void SCAN(int stop,int distance,station bay[]);
int findGoal(int stop,int bus,int distance,station bay[],int*direction,int clock);
void move(int*bus,int*goal,int stop,int distance,int direction,station bay[],int time,int*stay);
int firstgoal(station bay[],int distance,int stop,int*direction,int bus);
int count(station bay[],int stop);

void SCAN(int stop,int distance,station bay[]){
    int inputFlag=1,bus=0,direction=0,goal=-1,time=0,clock=1,questflag=0,firstflag=1,stay=-1;
    char inS[20];
    int inA;
    output(bus,bay,time,stop);//��ʼʱ�����һ�γ�ʼ״̬ 
    while(inputFlag!=0){ 
        inputFlag=statusRead(inS,&inA,bay,time,&questflag);
        if(strcmp(inS,"clock")==0){//���������clock����ʼ����
            time++;
            if(direction!=0){//ͣ��ʱ��¼ͣ��ǰ�ķ��� 
                clock=direction;
            }
            if(stay==-1){
                goal=firstgoal(bay,distance,stop,&direction,bus);
                bus+=direction;
                if(goal!=-1){
                    stay=0;
                }
                if(bus<0){
                    bus+=stop*distance;
                }
                else if(bus>=stop*distance){
                    bus-=stop*distance;
                } 
            }
            else if(goal==-1){//�����ʱû��Ŀ���������һ�� 
                goal=findGoal(stop,bus,distance,bay,&direction,clock);
                bus+=direction;//����ǰ������ 
                if(bus<0){
                    bus+=stop*distance;
                }
                else if(bus>=stop*distance){
                    bus-=stop*distance;
                }
            } 
            else {
                move(&bus,&goal,stop,distance,direction,bay,time,&stay);//�������������������������ƶ� 
            }
            output(bus,bay,time,stop);
        }
    }
    printf("end\n");
}

int findGoal(int stop,int bus,int distance,station bay[],int*direction,int clock){
    int goal=-1;
    int ahead=clock;
    int temp=bus/distance+1;//�����ʱδȷ��Ŀ����ʼȷ��Ŀ�ꣻ 
    for(int i=1;i<=stop/2;i++){//���յ�ǰ�������һ��·���ڵ����һ��Ŀ�� 
        temp+=ahead;
        if(temp>stop){
            temp-=stop;
        }
        else if(temp<=0){
            temp+=stop;
        }
        if(bay[temp].clockwise==1||bay[temp].counterclockwise==1||bay[temp].target==1){
            goal=temp;
            *direction=ahead;
            return goal;    
        }
    }
    if(goal==-1){
        ahead=-ahead;//������ǰ������Һ���δȷ��Ŀ��˵��Ӧ�û��� ���������� 
        temp=bus/distance+1;//�����ʱδȷ��Ŀ����ʼȷ��Ŀ�ꣻ 
        for(int i=1;i<=stop/2;i++){//���յ�ǰ�������һ��·���ڵ����һ��Ŀ�� 
            temp+=ahead;
            if(temp>stop){
                temp-=stop;
            }
            else if(temp<=0){
                temp+=stop;
            }
            if(bay[temp].clockwise==1||bay[temp].counterclockwise==1||bay[temp].target==1){
                goal=temp;
                *direction=ahead; 
                return goal;
            }
        }
    } 
    if(goal==-1){
        *direction=0;//�����δȷ��Ŀ��˵����ʱû������Ӧֹͣǰ��
        return -1; 
    }
    return 0;
}
 
void move(int*bus,int*goal,int stop,int distance,int direction,station bay[],int time,int*stay){
    if(*stay==1){//��վ״̬ 
        bay[*bus/distance+1].clockwise=0;
        bay[*bus/distance+1].counterclockwise=0;
        bay[*bus/distance+1].target=0;
        bay[*bus/distance+1].countertime=-1;
        bay[*bus/distance+1].clocktime=-1;
        bay[*bus/distance+1].targettime=-1;
        *stay=2; 
        if(*bus/distance+1==*goal){
            *goal=-1;//��Ϊ�����վ״̬  
            *stay=-3; 
        }
    }
    else if(*stay==2){//��վ״̬ 
        *stay=0;//��Ϊ��վ״̬ 
        *bus+=direction;
        if(*bus<0){
            *bus+=stop*distance;
        }
        else if(*bus>=stop*distance){
            *bus-=stop*distance;
        }
    }
    else{//��վ״̬ 
        *bus+=direction;
        if(*bus<0){
            *bus+=stop*distance;
        }
        else if(*bus>=stop*distance){
            *bus-=stop*distance;
        }
        if(*bus%distance==0&&count(bay,stop)==0){
            *stay=-1;//���������� 
        }
        else if(*bus%distance==0&&(bay[*bus/distance+1].clockwise==1||bay[*bus/distance+1].counterclockwise==1||bay[*bus/distance+1].target==1)&&((bay[*bus/distance+1].clocktime!=time&&bay[*bus/distance+1].clocktime!=-1)||(bay[*bus/distance+1].countertime!=time&&bay[*bus/distance+1].countertime!=-1)||(bay[*bus/distance+1].target!=time&&bay[*bus/distance+1].targettime!=-1))){
            *stay=1;//��Ϊ��վ״̬  
        }
    }
}
     
int firstgoal(station bay[],int distance,int stop,int*direction,int bus){//�������;��Ѱ�ҵ�һ��Ŀ�� 
    int clockside=bus/distance+1,counterside=bus/distance+1;
    if(bay[clockside].clockwise==1||bay[clockside].counterclockwise==1||bay[clockside].target==1){
        bay[clockside].clockwise=0;
        bay[clockside].counterclockwise=0;
        bay[clockside].target=0;
        bay[clockside].countertime=-1;
        bay[clockside].clocktime=-1;
        bay[clockside].targettime=-1;
    }
    while(clockside<=counterside){
        clockside++;
        counterside--;
        if(clockside>stop){
            clockside-=stop;
        }
        if(counterside<=0){
            counterside+=stop;
        }
        if((bay[clockside].clockwise==1||bay[clockside].counterclockwise==1||bay[clockside].target==1)&&(bay[counterside].clockwise==1||bay[counterside].counterclockwise==1||bay[counterside].target==1)){//��������������Ŀ����������˳ʱ�� 
            *direction=1;
            return clockside;
        }
        else if(bay[clockside].clockwise==1||bay[clockside].counterclockwise==1||bay[clockside].target==1){
            *direction=1;
            return clockside;
        }
        else if(bay[counterside].clockwise==1||bay[counterside].counterclockwise==1||bay[counterside].target==1){
            *direction=-1;
            return counterside;
        }
    }
    *direction=0;
    return -1;
}
int count(station bay[],int stop){
    int sum=0;
    for(int i=1;i<=stop;i++){
        sum+=bay[i].clockwise+bay[i].counterclockwise+bay[i].target;
    }
    return sum;
}
