#include"FCFS.h"
#include"SSTF.h"
#include"SCAN.h"
#include"dicRead.h"
#include"tool.h"
int main(void){
    char strategy[5]="FCFS";
    int stop=5;
    int distance=2;
    FILE*fPtr=fopen("dict.dic","r");
    dicRead(fPtr,strategy,&stop,&distance);//��ȡ����
    station*bay=(station*)malloc((stop+1)*sizeof(station));//����һ������Ϊstop�Ľṹ�������¼վ��״�? 
    for(int i=1;i<=stop;i++){
        bay[i].clockwise=0;
        bay[i].counterclockwise=0;
        bay[i].target=0;
        bay[i].countertime=-1;
        bay[i].clocktime=-1;
        bay[i].targettime=-1;
    }
    if(strcmp(strategy,"FCFS")==0){
        FCFS(stop,distance,bay);
    }
    else if(strcmp(strategy,"SSTF")==0){
        SSTF(stop,distance,bay);
    }
    if(strcmp(strategy,"SCAN")==0){
        SCAN(stop,distance,bay);
    }
    free(bay);
    return 0;
}
 
