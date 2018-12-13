#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

typedef struct movInfo{
	char name[200]; //��ȭ �̸� 
	float score; //��ȭ ���� 
	int runTime; //��ȭ ��Ÿ�� 
	char madeIn[10]; //��ȭ ���� ���� 
} movInfo_t; //����ü movInfo�� movInfo_t�� ���� 


void* mv_genMvInfo(char* name, float score, int runTime, char* country)
{
	movInfo_t* mvPtr;
	
	//allocate memory and set the member variables 
	//�޸� ���� �Ҵ� -> malloc �Լ� ��� 
	mvPtr = (movInfo_t*)malloc( sizeof(movInfo_t) ); 
	
	if (mvPtr == NULL)
	{
		printf("ERROR! �޸� �Ҵ� ����\n");
	}
	
	//������ �Ҵ� -> ����ü�� strcpy �̿� 
	strcpy(mvPtr->name, name);
	strcpy(mvPtr->madeIn, country);
	mvPtr->runTime = runTime;
	mvPtr->score = score;
	
	return (void*)mvPtr;
}

void mv_print(void* obj)
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	
	if (mvPtr == NULL)
	{
		printf("[ERROR] failed to print the movie Info! (object is NULL)\n");
	}
	
	printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn); //��ȭ �̸��� ���� ���  
	printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score); //��ȭ ��Ÿ�Ӱ� ���� ��� 
	
	return;
}


//return the score value from the input instance of movInfo_t structure
float mv_getScore(void* obj)
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	return (mvPtr->score); //������ mvPtr�� ���� �� score�� ��ȯ
}

//return the runtime value from the input instance of movInfo_t structure
int mv_getRunTime(void* obj)
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	return (mvPtr->runTime); //������ mvPtr�� ���� �� runTime���� ��ȯ
}

//return the name string pointer from the input instance of movInfo_t structure
char* mv_getName(void* obj)
{
	movInfo_t* mvPtr = (movInfo_t*)obj; 
	return (mvPtr->name); //������ mvPtr�� ���� �� name���� ��ȯ 
}

//return the country string pointer from the input instance of movInfo_t structure
char* mv_getCountry(void* obj)
{
	movInfo_t* mvPtr = (movInfo_t*)obj;
	return (mvPtr->madeIn); //������ mvPtr�� ���� �� madeIn���� ��ȯ
}


