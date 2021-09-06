#include "base.h"
#define _CRT_SECURE_NO_WARNINGS
int check[50];
int A[20];
Hotel * T = NULL;
Hotel hotel[101];
//Person* nil;

int main(void)
{
	srand((unsigned int)time(NULL));
	sites S[SIZE + 1];
	Person *tree;
	Person *p;
	int graph[SIZE + 1][SIZE + 1];
	int parent_vertex[SIZE + 1];
	int * path_arr;

	memset(parent_vertex, -1, sizeof(SIZE + 1));
	// Creation of graph(distance information of edge weight) and site
	make_graph(graph);
	nil=make_nil();
	tree = nil;
	make_sites(S);
	Connect(S);
	//char c = _getch();


	while (1) {
		int menu, bud, dat, i, ds, st;
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("\n");
		printf("      1. Input User Info\n");
		printf("      2. Search User Reservation Info\n");
		printf("      3. Cancel Reservation\n");
		printf("      4. Exit\n");
		printf("\n");
		printf("      Input Number :\n");
		printf("\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

		scanf("%d", &menu);

		if (menu == 1) {
			system("cls");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("\n");
			printf("      1. User ID :\n");
			printf("      2. Budget :\n");
			printf("      3. Travel Date :\n");
			printf("      4. Start City :\n");
			printf("      5. Destination :\n");
			printf("\n");
			printf("      Input ID in integer type\n");
			printf("\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

			scanf("%d", &i);
			system("cls");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("\n");
			printf("      1. User ID : %d\n", i);
			printf("      2. Budget :\n");
			printf("      3. Travel Date :\n");
			printf("      4. Start City :\n");
			printf("      5. Destination :\n");
			printf("\n");
			printf("      Input Budget\n");
			printf("\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

			scanf("%d", &bud);
			system("cls");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("\n");
			printf("      1. User ID : %d\n", i);
			printf("      2. Budget :  %d\n", bud);
			printf("      3. Travel Date : \n");
			printf("      4. Start City : \n");
			printf("      5. Destination : \n");
			printf("\n");
			printf("      Input Travel Date in Day (EX : 4 days - 4)\n");
			printf("\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

			scanf("%d", &dat);
			system("cls");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("\n");
			printf("      1. User ID : %d\n", i);
			printf("      2. Budget :  %d\n", bud);
			printf("      3. Travel Date : %d\n", dat);
			printf("      4. Start City : \n");
			printf("      5. Destination : \n");
			printf("\n");
			printf("      Input Start City in integer type\n");
			printf("\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

			scanf("%d", &st);
			system("cls");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("\n");
			printf("      1. User ID : %d\n", i);
			printf("      2. Budget :  %d\n", bud);
			printf("      3. Travel Date : %d\n", dat);
			printf("      4. Start City : %d\n", st);
			printf("      5. Destination : \n");
			printf("\n");
			printf("      Input Destination in integer type\n");
			printf("\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

			scanf("%d", &ds);
			system("cls");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("\n");
			printf("      1. User ID : %d\n", i);
			printf("      2. Budget :  %d\n", bud);
			printf("      3. Travel Date : %d\n", dat);
			printf("      4. Start City : %d\n", st);
			printf("      5. Destination : %d\n", ds);
			printf("\n");
			printf("      Making Travel Route...\n");
			printf("\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

			p = make_node(i, bud, dat * 24, st, ds);
			dijkstra(graph, parent_vertex, st);
			int dst = ds; // 목적지 노드
			int start = st; // 출발 노드 


			//for (int i = 1; i <= SIZE; i++)  if (parent_vertex[i] != 0) printf("parent : %d , child : %d\n", parent_vertex[i], i);

			//printf("It is path before checking : ");
			path_arr = print_path(start, dst, parent_vertex);
			
			Sleep(3000);
			int chk = check_route(p, S, path_arr, graph);
			if (chk) {
				tree = RB_insert(tree, p);
				system("cls");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("      Save Completely\n");
				printf("      Press Any Key to go to menu\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");				
				char c = _getch();
			}
			else {
				system("cls");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("      Can't Build Travel Path\n");
				printf("      Please Input Another Plan\n");
				printf("      Press Any Key to go to menu\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				char c = _getch();
			}
		}
		else if(menu==2){
			int id;
			system("cls");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("      Enter Your ID : \n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			scanf("%d", &id);

			p = tree_search(tree, id);
			if (p != nil)
			{
				system("cls");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				printf("\n");
				printf("      id : %d\n", p->id);
				printf("      budget : %f\n", p->budget);
				printf("      date : %d\n", p->date / 24);
				printf("      start : %d\n", p->start);
				printf("      destination : %d\n", p->dst);
				printf("\n");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

				int i;
				for (i = 0; p->data[0][i] != 0; i++);

				for (int j=0; j < i; j++) {
					printf("      ┌───────────────────────────────────────────────────┐\n");
					printf("                           site : %.0f\n", p->data[0][j]);
					printf("                           hotel : $ %.0f\n", p->data[1][j]);
					printf("                           time: %.0f hours\n", p->data[2][j]);
					printf("      └───────────────────────────────────────────────────┘\n");
					if (j == (i - 1)) {
						break;
					}
					printf("                                │ price : $ %.0f\n", p->data[3][j] * 4);
					printf("                                │ time  : %.3f hours\n", p->data[3][j] / 1000);
					printf("                                ∨\n");
				}
				

				printf("\n");
				printf("      Press Any key to back to menu\n");
				printf("\n");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

				char c = _getch();

			}
			else {
				system("cls");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				printf("\n");
				printf("\n");
				printf("      No such id : %d\n", id);
				printf("      Press Any key to go to menu\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				char c = _getch();
			}
				

		}
		else if (menu == 3) {
			int id;
			system("cls");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("      Enter Your ID : \n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			scanf("%d", &id);

			p = tree_search(tree, id);
			if (p != nil)
			{
				tree = RB_delete(tree, p);
				system("cls");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("      Deleting...\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

				Sleep(3000);

				system("cls");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				printf("\n");
				printf("\n");
				printf("      Delete Completely\n");
				printf("      Press Any key to go to menu\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				char c = _getch();

			}
			else {
				system("cls");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				printf("\n");
				printf("\n");
				printf("      No such id : %d\n", id);
				printf("      Press Any key to go to menu\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				char c = _getch();
			}


		}
		else if(menu==4){
			return 0;
		}
		else {
			system("cls");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("\n"); 
			printf("\n");
			printf("      Please choose correct menu\n");
			printf("      Press Any Key to go to menu\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

			char c = _getch();
		}

	}

	

/*
	for (int i = 1; i <= SIZE; i++)
	{
		for (int j = 1; j <= SIZE; j++)
		{
			if(graph[i][j] != 0) printf("%d ", 1);
			else printf("%d ", 0);
		}
		printf("\n");
	}
		
	*/  // GRAPH 연결 정보 확인 용 코드 ( 1: 연결 , 0 : 미연결)
	/*
	dijkstra(graph, parent_vertex,2);
	int dst = p.dst; // 목적지 노드
	int start = 2; // 출발 노드 


	for (int i = 1; i <= SIZE; i++)  if(parent_vertex[i] != 0) printf("parent : %d , child : %d\n",parent_vertex[i],i);
	
	printf("It is path before checking : ");
	path_arr = print_path(start,dst,parent_vertex);
	
	if (check_route(&p, S, path_arr)) printf("It is correct\n");
	else printf("It is not correct\n");
	*/




	//system("pause");
	return 0;
}

