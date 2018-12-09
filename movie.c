#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

typedef struct movInfo{
	char name[200];
	float score;
	int runTime;
	char madeIn[10];
} movInfo_t;


void* mv_genMvInfo(char* name, float score, int runTime, char* country)
{
	movInfo_t* mvPtr;
	
	//allocate memory and set the member variables 
	//메모리 할당 -> malloc 함수 사용 
	mvPtr = (movInfo_t*)malloc( sizeof(movInfo_t) ); 
	
	if (mvPtr == NULL)
	{
		printf("메모리 할당 오류\n");
	}
	
	//변수값 할당 -> 구조체는 strcpy 이용 
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
	
	printf("Name : %s (%s)\n", mvPtr->name, mvPtr->madeIn);
	printf("running time : %i, score : %f\n", mvPtr->runTime, mvPtr->score);
	
	return;
}


//return the score value from the input instance of movInfo_t structure
float mv_getScore(void* obj)
{
	return (movInfo_t->score);
}

//return the runtime value from the input instance of movInfo_t structure
int mv_getRunTime(void* obj)
{
	return (movInfo_t->runTime);
}

//return the name string pointer from the input instance of movInfo_t structure
char* mv_getName(void* obj)
{
	return (movInfo_t->name);
}

//return the country string pointer from the input instance of movInfo_t structure
char* mv_getCountry(void* obj)
{
	return (movInfo_t->madeIn);
}


