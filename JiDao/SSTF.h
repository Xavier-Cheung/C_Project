#include<stdio.h>
#include<stdlib.h>
#include"tool.h"
void SSTF(int stop,int distance,station bay[]);//ʵ��SSTF
void findTargetStation(station  bay[],int position,int p[],int stop,int distance);//Ѱ��Ŀ��վ��
void zero(station bay[],int purpose[]);//���㺯��
int everycommand_shortest(int a,int b,int *direction,int stop,int distance);//������룬�жϷ�����
int passing(station bay[],int stop,int distance,int purpose[],int position,int temp_time);//˳�������
void passing_timeJudge(station bay[],int stop,int distance,int purpose[],int position,int time,int *temp_time);

void SSTF(int stop,int distance,station bay[])
{
    int shortest_Direction=0;//��Ŀ��վ��ķ���
    int position=0;
    int main_purpose[3]={0,-1,0};//������Ŀ��վ���Ŀ��վ����������̾���ͷ���
    int time=0;
    int flag1=1,flag2=1;//flag1�ж������Ƿ���ɣ�flag2�ж������Ƿ����
    int questflag=0;
    int location;//�����������վ��
    char command[20];//���������������
    int t=0;
    int temp_time;
    output(position,bay,time,stop);//Ĭ�������ʼ״̬
    if(flag1)
    {
        flag1=statusRead(command,&location,bay,time,&questflag);
            while(flag1){//˳�����
                if(strcmp(command,"clock")==0){
                    if(main_purpose[1]==-1){
                        findTargetStation(bay,position,main_purpose,stop,distance);//Ѱ��Ŀ��վ��
                    }
                    passing_timeJudge(bay,stop,distance,main_purpose,position,time,&temp_time);
                    time++;
                    t=passing(bay,stop,distance,main_purpose,position,temp_time);
                    if(position==main_purpose[1]*distance-distance){
                        zero(bay,main_purpose);
                        main_purpose[1]=-1;
                    }
                    else if(t){
                        t=0;
                    }
                    else{
                        position+=main_purpose[0];
                        if(position<0){
                            position+=stop*distance;
                        }
                        else if(position>stop*distance-1){
                            position-=distance*stop;
                        }
                    }
                    output(position,bay,time,stop);
                }
                flag1=statusRead(command,&location,bay,time,&questflag);
            }
    }
    printf("end\n");
}
void findTargetStation(station  bay[],int position,int p[],int stop,int distance)
{
    int temp_command=0;//���������ָ��
    int temp_station=-1;//����Ŀ��վ�㣨��û��Ϊ-1��
    int temp_direction=0;//�����ж�ÿ����̾���ָ��ķ���
    int direction=0;//�����������յ�������ķ���
    int shortest_Distance=stop*distance;//��������ÿһ��ָ�����̾���
    int i=0,j=0;
    int allDirection[50]={0};//����ÿ��ָ��ķ��������
    int arr[50]={0};//���������������̾��������
    for(i=0;i<50;){
        for(j=1;j<=stop;j++){//����clockwiseָ��
            if(bay[j].clockwise==1){
                arr[i]=everycommand_shortest(position,j,&temp_direction,stop,distance);//����ÿ��ָ���Ӧ����̾��벢�жϷ���
                allDirection[i]=temp_direction;//���ÿ��ָ��ķ���
                if(arr[i]<shortest_Distance){//������̾��롢��̾���ָ��ķ���վ�㡢ָ��
                    shortest_Distance=arr[i];
                    direction=temp_direction;
                    temp_station=j;
                    temp_command=1;
                }
            }
            i++;
        }
        for(j=1;j<=stop;j++){//����counterclockwiseָ��
            if(bay[j].counterclockwise==1){//ͬ��
                arr[i]=everycommand_shortest(position,j,&temp_direction,stop,distance);
                allDirection[i]=temp_direction;
                if(arr[i]<shortest_Distance){
                    shortest_Distance=arr[i];
                    direction=temp_direction;
                    temp_station=j;
                    temp_command=2;
                }
            }
            i++;
        }
        for(j=1;j<=stop;j++){//����targetָ��
            if(bay[j].target==1){//ͬ��
                arr[i]=everycommand_shortest(position,j,&temp_direction,stop,distance);
                allDirection[i]=temp_direction;
                if(arr[i]<shortest_Distance){
                    shortest_Distance=arr[i];
                    direction=temp_direction;
                    temp_station=j;
                    temp_command=3;
                }
            }
            i++;
        }
        break;
    }
    for(int k=0;k<i;k++){//�ж�����վ�������ͬ����˳ʱ��
        if(arr[k]!=0&&arr[k]==shortest_Distance){
            if(allDirection[k]==1){//�ҵ�˳ʱ��������ָ���������վ�㡢ָ�����
                direction=1;
                temp_station=k%stop+1;
                if(k>=0&&k<stop){
                    temp_command=1;
                }
                else if(k>=stop&&k<2*stop){
                    temp_command=2;
                }
                else{
                    temp_command=3;
                }
            }
        }
    }
    p[0]=direction;//�ҵ�����̾��뷽��
    p[1]=temp_station;//��̾����վ��
    p[2]=temp_command;//��̾��������
}
 
void zero(station bay[],int purpose[])//����ɵ�ָ������
{
    bay[purpose[1]].clockwise=0;
    bay[purpose[1]].counterclockwise=0;
    bay[purpose[1]].target=0;
 
}
 
int everycommand_shortest(int a,int b,int *direction,int stop,int distance)//����ÿһ��ָ������·���������жϷ���
{//a��position��b��Ŀ��stop
    int purpose_position=b*distance-distance;//����Ŀ��վ���position
    int dis1,dis2;//����˳��ʱ��ľ��롾��ͬ��
    if(purpose_position>a){
        dis1=purpose_position-a;
        dis2=stop*distance-dis1;
        if(dis1<=dis2){//������ͬ����˳ʱ��
            *direction=1;//ͬʱ�жϷ�����ͬ��
            return dis1;
        }
        else{
            *direction=-1;
            return dis2;
        }
    }
    else if(a>purpose_position){
        dis1=a-purpose_position;
        dis2=stop*distance-dis1;
        if(dis1<dis2){
            *direction=-1;
            return dis1;
        }
        else{//������ͬ���ȿ���˳ʱ��
            *direction=1;
            return dis2;
        }
    }
    else{
        *direction=0;
        return 0;
    }
}
 
void passing_timeJudge(station bay[],int stop,int distance,int purpose[],int position,int time,int *temp_time){
    if(bay[position/distance+1].clockwise==1&&purpose[0]==1&&position%distance==0){
        *temp_time=time;
    }
    else if(bay[position/distance+1].counterclockwise==1&&purpose[0]==-1&&position%distance==0){
        *temp_time=time;
    }
    else if(bay[position/distance+1].target==1&&position%distance==0){
        *temp_time=time;
    }
}
 
int passing(station bay[],int stop,int distance,int purpose[],int position,int temp_time)//˳�����������������˳����񣬷���1
{
    int flag=0;
    if(bay[position/distance+1].clockwise==1&&purpose[0]==1&&position%distance==0&&bay[position/distance+1].clocktime<temp_time){//˳�����˳ʱ���ϳ�����
        bay[(position+distance)/distance].clockwise=0;
        flag=1;
    }
    if(bay[position/distance+1].counterclockwise==1&&purpose[0]==-1&&position%distance==0&&bay[position/distance+1].countertime<temp_time){//˳�������ʱ���ϳ�����
        bay[(position+distance)/distance].counterclockwise=0;
        flag=1;
    }
    if(bay[position/distance+1].target==1&&position%distance==0&&bay[position/distance+1].targettime<temp_time){//˳������ϵ�����
        bay[(position+distance)/distance].target=0;
        flag=1;
    }
    return flag;
}
