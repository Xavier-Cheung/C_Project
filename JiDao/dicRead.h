#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void dicRead(FILE*fPtr,char strategy[],int*stop,int*distance){
    char tempS[200];
    char tempC;
    int tempA;
    while(!feof(fPtr)){//���û�е��ı�ĩβ�����������
        fscanf(fPtr,"%c",&tempC);//����̽�Ƿ���#��������Ϊע���У�
        if(tempC=='#'){
            fgets(tempS,200,fPtr);//�����ע���У���ֱ�ӽ�����ȫ����������
        }
        else{
            fseek(fPtr,-1,1);//�������Ч����ص���һλ�����¿�ʼ��
            fscanf(fPtr,"%s",tempS);
            fgetc(fPtr);//���ߡ� �� 
            fgetc(fPtr);//���ߡ�=��
            if(strcmp(tempS,"TOTAL_STATION")==0){
                fscanf(fPtr,"%d",stop);
                fgetc(fPtr);
            }
            else if(strcmp(tempS,"STRATEGY")==0){
                fscanf(fPtr,"%s",strategy);
                fgetc(fPtr);
            }
            else if(strcmp(tempS,"DISTANCE")==0){
                fscanf(fPtr,"%d",distance);
                fgetc(fPtr);
            }
        }
    }
}
 
