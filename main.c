#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"
#include "linkedList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	FILE *fp; //FILE pointer for reading movie data 
	char name[200]; //movie name
	char country[10]; //movie country
	int runTime; //movie runtime
	float score; //movie score
	
	int exit_flag = 0; //flag variable for while loop
	int option; //user input option
	void *list, *mvInfo; //pointers for linked list and a specific structure instance for a movie data
	void *ndPtr; //void pointer for linked list node
	
	char selectCountry[10]; //사용자가 선택하는 나라 
	int selectRuntime; //사용자가 선택하는 최저 런타임
	float selectScore; //사용자가 선택하는 최저 평점 
	 
	int num; //검색에 해당되는 영화 개수를 세는 변수 
	
	//1. reading the movie.dat-----------------------------
	//1.1 FILE open
	
	printf("Reading the data files...\n");
	
	fp = fopen("movie.dat","r"); //파일을 읽기 모드로 열기
	
	if(fp == NULL)
	{
		printf("ERROR! The data files could not be read.\n"); //파일이 읽히지 않는 경우(없는 경우) 
		
		return 0;
	}
	
	//1.2 list generation (use function list_genList() )
	list = list_genList(); //리스트 생성 
	
	//1.3 read each movie data from the file and add it to the linked list
	while ((fgetc(fp) != EOF)) /* read name, country, runtime and score*/
	{	
		fscanf(fp, "%s %s %d %f", name, country, &runTime, &score); //파일에서 영화 정보 가져오기 
		
		//generate a movie info instance(mvInfo) with function mv_genMvInfo()
		
		mvInfo = mv_genMvInfo(name, score, runTime, country); //영화 정보 만들기 
		
		list_addTail(mvInfo, list); //리스트 끝에 꼬리 달기 
	}

	//1.4 FILE close
	fclose(fp); //파일 닫기 
	
	//2. program start
	
	printf("Read done! %d items are read.\n", list_len(list)); //읽힌 파일 개수 출력되도록 하기 
	
	
	while(exit_flag == 0) 
	{
		//2.1 print menu message and get input option
		printf("-----------------------------Menu-----------------------------\n"); //메뉴 출력 
		printf("1. print all the movies\n"); //모든 영화 출력하게 하는 옵션 
		printf("2. search for specific country movies\n"); //특정 나라의 영화 출력하게 하는 옵션 
		printf("3. search for specific runtime movies\n"); //특정 런타임 이상의 영화 출력하게 하는 옵션 
		printf("4. search for specific score movies\n"); //특정 평점 이상의 영화 출력하게 하는 옵션 
		printf("5. exit\n"); //나가기 옵션 
		printf("-----------------------------Menu-----------------------------\n\n");
		printf("-- select an option : ");
		scanf("%d", &option);  //사용자로부터 옵션을 선택 받음 
		
		switch(option)
		{
			case 1: //print all the movies
				printf("printing all the movies in the list.....\n\n\n");
				printf("----------------------------------------------\n");
				
				ndPtr = list; //ndPtr이 리스트 가리킴 
				while (list_isEndNode(ndPtr) == 0) /* repeat until the ndPtr points to the end node */
				{
					//2.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNode(ndPtr);
					
					//get object of ndPtr to mvInfo void pointer
					mvInfo = list_getNdObj(ndPtr);
					
					//print the contents of the mvInfo
					mv_print(mvInfo);
					printf("----------------------------------------------\n\n");
				}
				printf(" - totally %d movies are listed!\n", list_len(list)); //출력된 영화 개수 출력하기 
				
				break;
				
			case 2: //print movies of specific country
				//2.3.1 get country name to search for
				printf("select a country : ");
				scanf("%s", &selectCountry); //특정 나라 입력받기 
				printf("----------------------------------------------\n");
				
				num = 0; //변수 초기화 
				
				ndPtr = list; //ndPtr이 리스트 가리킴 
					while (list_isEndNode(ndPtr) == 0) /* repeat until the ndPtr points to the end node */
				{
					//2.3.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNode(ndPtr);
					
					//get object of ndPtr to mvInfo void pointer
					mvInfo = list_getNdObj(ndPtr);
					
					//if the input country matches to the country of the movie,
					if(strncmp(selectCountry, mv_getCountry(mvInfo), strlen(selectCountry)) == 0) //입력받은 나라 문자열 비교하여 일치하는 경우 
					{
						//then print the contents of the mvInfo
					    mv_print(mvInfo);
					    printf("----------------------------------------------\n\n");
					    num++; //총 영화 개수 출력하기 위해 1씩 증가 
					}
				}
				printf(" - totally %d movies are listed!\n", num); //출력된 영화 개수 출력하기
				
				break;
				
			case 3:
				//2.4.1 get minimal runtime value to search for
				printf("select a runtime : ");
				scanf("%d", &selectRuntime); //특정 런타임 입력받기 
				printf("----------------------------------------------\n");
				
				num = 0; //변수 초기화 
				
				ndPtr = list; //ndPtr이 리스트 가리킴 
					while (list_isEndNode(ndPtr) == 0) /* repeat until the ndPtr points to the end node */
				{
					//2.4.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNode(ndPtr);
					
					//get object of ndPtr to mvInfo void pointer
					mvInfo = list_getNdObj(ndPtr);
					
					//if the input runtime is lower than the runtime of the movie,
					if(selectRuntime <= mv_getRunTime(mvInfo)) //입력받은 런타임보다 런타임이 클 경우 
					{
						//then print the contents of the mvInfo
						mv_print(mvInfo);
						printf("----------------------------------------------\n\n");
					    num++; //총 영화 개수 출력하기 위해 1씩 증가 
					}
				}
				printf(" - totally %d movies are listed!\n", num); //출력된 영화 개수 출력하기
				
				break;
				
			case 4:
				//2.5.1 get minimal score value to search for
				printf("select a score : ");
				scanf("%f", &selectScore); //특정 평점 입력받기 
				printf("----------------------------------------------\n");
				
				num = 0; //변수 초기화 
				
				ndPtr = list; //ndPtr이 리스트 가리킴 
					while (list_isEndNode(ndPtr) == 0) /* repeat until the ndPtr points to the end node */
				{
					//2.5.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNode(ndPtr);
					
					//get object of ndPtr to mvInfo void pointer
					mvInfo = list_getNdObj(ndPtr);
					
					//if the input score is lower than the score of the movie,
					if(selectScore <= mv_getScore(mvInfo)) //입력받은 평점보다 평점이 클 경우 
					{
						//then print the contents of the mvInfo
						mv_print(mvInfo);
						printf("----------------------------------------------\n\n");
					    num++; //총 영화 개수 출력하기 위해 1씩 증가 
						
					}
				}
				printf(" - totally %d movies are listed!\n", num); //출력된 영화 개수 출력하기 
				
				break;
				
			case 5:
				//exit의 경우 
				printf("Bye!\n\n");
				exit_flag = 1;
				break;
				
			default:
				//사용자가 입력한 옵션이 1~5의 경우가 아닐 때 
				
				printf("wrong command! input again\n"); //다시 입력받기 
				break;
		}
	}
	
	return 0;
}
