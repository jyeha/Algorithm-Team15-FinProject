#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#define dst_size 100
#define INF 987654321
#define SIZE 100
#define MIN(A,B) A<B? A:B

enum Color{RED,BLACK};

typedef struct __Hotel
{
	
	float price;
	int id;
	enum Color color;
	struct __Hotel * left;
	struct __Hotel * right;
	struct __Hotel * parent;
	 
}Hotel;

/*
typedef struct __Person
{
	int id;
	float budget;
	int date;
	int dst;
	float data[4][101];
	enum Color color;

	struct __Person* parent;
	struct __Person* left;
	struct __Person* right;
}Person;
*/

typedef struct __priority_node {
	int priority;
	int vertex;
	struct __priority_node * next;
}Priority_Node;

//void Person_init(Person * p , char * destination);
Hotel * NEW_NODE(Hotel * parent, float z);
void swapColors(Hotel *x1, Hotel *x2);
void swapValues(Hotel *u, Hotel *v);
Hotel *successor(Hotel *x);
int isOnLeft(Hotel * self);
Hotel * uncle(Hotel * parent);
Hotel * find_replace(Hotel *x);
Hotel * RR_ROTATE(Hotel * par);
Hotel * LL_ROTATE(Hotel * par);
Hotel * LR_ROTATE(Hotel * par);
Hotel * RL_ROTATE(Hotel * par);
void FIX_FUNCTION(Hotel * node, Hotel * root);
Hotel * TREE_SEARCH(Hotel * root,float k);
Hotel * RB_INSERT(Hotel * root, float z);
void PRINT_BST(Hotel * root);
int height(Hotel * root);
void deleteNode(Hotel * v, Hotel * root);
void fixDoubleBlack(Hotel * x, Hotel * root);
void fixRedRed(Hotel * x, Hotel * root);
void rightRotate(Hotel * x, Hotel * root);
void leftRotate(Hotel *x, Hotel * root);
int hasRedChild(Hotel * v);
void moveDown(Hotel * nParent, Hotel * v);
Hotel * find_replace(Hotel *x);
Hotel * uncle(Hotel * parent);
int isOnLeft(Hotel * self);
void deleteByVal(float n, Hotel * root);



int isEmpty(Priority_Node ** head);
void push(Priority_Node ** head, int vertex, int priority);
void pop(Priority_Node ** head);
Priority_Node * peek(Priority_Node ** head);
Priority_Node * Priority_New_Node(int vertex, int priority);

//void dijkstra(double * (graph)[SIZE + 1], double * value, int * f, int * index);




typedef struct _sites {
	//char sitename[10];
	//int sitename; 필요 없을 것 같아요. P.dst에서 1~100사이의 숫자로 받아서 sites s[i]로 연결한다.

	int tourtime; //여행시간
	Hotel *H;
}sites;


void make_sites(sites * S);
void make_graph(int graph[][SIZE+1]);
void dijkstra(int graph[][SIZE + 1], int * index, int start_vertex);
//void Wallet(int **graph, sites *S, Person *P, int p, int j, Hotel *H, int idx);


//typedef int 		DATA;

typedef struct __Person
{
	int id;
	float budget;
	int date;
	int dst;
	int start;
	float data[4][101];

	enum Color color;
	struct __Person 	*left;
	struct __Person 	*right;
	struct __Person	*p;
}Person;
Person* nil;

Person* left_rotate(Person* tree, Person* base);
Person* right_rotate(Person* tree, Person* base);
Person* RB_insert_fixup(Person* tree, Person* input);
Person* RB_insert(Person* tree, Person* input);
Person* make_node(int i, float bud, int dat, int st, int ds);
Person* make_nil();
Person* tree_minimum(Person* root);
Person* tree_successor(Person* root);
Person* RB_delete_fixup(Person* tree, Person* put);
Person* RB_delete(Person* tree, Person* put);
Person* tree_search(Person* tree, int d);
void print_inorder(Person* tree, int level);
void delete_all(Person* tree);
