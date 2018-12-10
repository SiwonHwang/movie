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
	
	char selectCountry[10]; //����ڰ� �����ϴ� ���� 
	int selectRuntime; //����ڰ� �����ϴ� ���� ��Ÿ��
	float selectScore; //����ڰ� �����ϴ� ���� ���� 
	 
	int num; //�˻��� �ش�Ǵ� ��ȭ ������ ���� ���� 
	
	//1. reading the movie.dat-----------------------------
	//1.1 FILE open
	
	printf("Reading the data files...\n");
	
	fp = fopen("movie.dat","r"); //������ �б� ���� ����
	
	if(fp == NULL)
	{
		printf("ERROR! The data files could not be read.\n"); //������ ������ �ʴ� ���(���� ���) 
		
		return 0;
	}
	
	//1.2 list generation (use function list_genList() )
	list = list_genList(); //����Ʈ ���� 
	
	//1.3 read each movie data from the file and add it to the linked list
	while ((fgetc(fp) != EOF)) /* read name, country, runtime and score*/
	{	
		fscanf(fp, "%s %s %d %f", name, country, &runTime, &score); //���Ͽ��� ��ȭ ���� �������� 
		
		//generate a movie info instance(mvInfo) with function mv_genMvInfo()
		
		mvInfo = mv_genMvInfo(name, score, runTime, country); //��ȭ ���� ����� 
		
		list_addTail(mvInfo, list); //����Ʈ ���� ���� �ޱ� 
	}

	//1.4 FILE close
	fclose(fp); //���� �ݱ� 
	
	//2. program start
	
	printf("Read done! %d items are read.\n", list_len(list)); //���� ���� ���� ��µǵ��� �ϱ� 
	
	
	while(exit_flag == 0) 
	{
		//2.1 print menu message and get input option
		printf("-----------------------------Menu-----------------------------\n"); //�޴� ��� 
		printf("1. print all the movies\n"); //��� ��ȭ ����ϰ� �ϴ� �ɼ� 
		printf("2. search for specific country movies\n"); //Ư�� ������ ��ȭ ����ϰ� �ϴ� �ɼ� 
		printf("3. search for specific runtime movies\n"); //Ư�� ��Ÿ�� �̻��� ��ȭ ����ϰ� �ϴ� �ɼ� 
		printf("4. search for specific score movies\n"); //Ư�� ���� �̻��� ��ȭ ����ϰ� �ϴ� �ɼ� 
		printf("5. exit\n"); //������ �ɼ� 
		printf("-----------------------------Menu-----------------------------\n\n");
		printf("-- select an option : ");
		scanf("%d", &option);  //����ڷκ��� �ɼ��� ���� ���� 
		
		switch(option)
		{
			case 1: //print all the movies
				printf("printing all the movies in the list.....\n\n\n");
				printf("----------------------------------------------\n");
				
				ndPtr = list; //ndPtr�� ����Ʈ ����Ŵ 
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
				printf(" - totally %d movies are listed!\n", list_len(list)); //��µ� ��ȭ ���� ����ϱ� 
				
				break;
				
			case 2: //print movies of specific country
				//2.3.1 get country name to search for
				printf("select a country : ");
				scanf("%s", &selectCountry); //Ư�� ���� �Է¹ޱ� 
				printf("----------------------------------------------\n");
				
				num = 0; //���� �ʱ�ȭ 
				
				ndPtr = list; //ndPtr�� ����Ʈ ����Ŵ 
					while (list_isEndNode(ndPtr) == 0) /* repeat until the ndPtr points to the end node */
				{
					//2.3.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNode(ndPtr);
					
					//get object of ndPtr to mvInfo void pointer
					mvInfo = list_getNdObj(ndPtr);
					
					//if the input country matches to the country of the movie,
					if(strncmp(selectCountry, mv_getCountry(mvInfo), strlen(selectCountry)) == 0) //�Է¹��� ���� ���ڿ� ���Ͽ� ��ġ�ϴ� ��� 
					{
						//then print the contents of the mvInfo
					    mv_print(mvInfo);
					    printf("----------------------------------------------\n\n");
					    num++; //�� ��ȭ ���� ����ϱ� ���� 1�� ���� 
					}
				}
				printf(" - totally %d movies are listed!\n", num); //��µ� ��ȭ ���� ����ϱ�
				
				break;
				
			case 3:
				//2.4.1 get minimal runtime value to search for
				printf("select a runtime : ");
				scanf("%d", &selectRuntime); //Ư�� ��Ÿ�� �Է¹ޱ� 
				printf("----------------------------------------------\n");
				
				num = 0; //���� �ʱ�ȭ 
				
				ndPtr = list; //ndPtr�� ����Ʈ ����Ŵ 
					while (list_isEndNode(ndPtr) == 0) /* repeat until the ndPtr points to the end node */
				{
					//2.4.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNode(ndPtr);
					
					//get object of ndPtr to mvInfo void pointer
					mvInfo = list_getNdObj(ndPtr);
					
					//if the input runtime is lower than the runtime of the movie,
					if(selectRuntime <= mv_getRunTime(mvInfo)) //�Է¹��� ��Ÿ�Ӻ��� ��Ÿ���� Ŭ ��� 
					{
						//then print the contents of the mvInfo
						mv_print(mvInfo);
						printf("----------------------------------------------\n\n");
					    num++; //�� ��ȭ ���� ����ϱ� ���� 1�� ���� 
					}
				}
				printf(" - totally %d movies are listed!\n", num); //��µ� ��ȭ ���� ����ϱ�
				
				break;
				
			case 4:
				//2.5.1 get minimal score value to search for
				printf("select a score : ");
				scanf("%f", &selectScore); //Ư�� ���� �Է¹ޱ� 
				printf("----------------------------------------------\n");
				
				num = 0; //���� �ʱ�ȭ 
				
				ndPtr = list; //ndPtr�� ����Ʈ ����Ŵ 
					while (list_isEndNode(ndPtr) == 0) /* repeat until the ndPtr points to the end node */
				{
					//2.5.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNode(ndPtr);
					
					//get object of ndPtr to mvInfo void pointer
					mvInfo = list_getNdObj(ndPtr);
					
					//if the input score is lower than the score of the movie,
					if(selectScore <= mv_getScore(mvInfo)) //�Է¹��� �������� ������ Ŭ ��� 
					{
						//then print the contents of the mvInfo
						mv_print(mvInfo);
						printf("----------------------------------------------\n\n");
					    num++; //�� ��ȭ ���� ����ϱ� ���� 1�� ���� 
						
					}
				}
				printf(" - totally %d movies are listed!\n", num); //��µ� ��ȭ ���� ����ϱ� 
				
				break;
				
			case 5:
				//exit�� ��� 
				printf("Bye!\n\n");
				exit_flag = 1;
				break;
				
			default:
				//����ڰ� �Է��� �ɼ��� 1~5�� ��찡 �ƴ� �� 
				
				printf("wrong command! input again\n"); //�ٽ� �Է¹ޱ� 
				break;
		}
	}
	
	return 0;
}
