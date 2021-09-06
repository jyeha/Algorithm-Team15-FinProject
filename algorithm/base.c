#include "base.h"
#define _CRT_SECURE_NO_WARNINGS
Hotel * TREE = NULL;
//Person* nil;

/*
void Person_init(Person * p , char * destination)
{
	p->dst = (char*)malloc(sizeof(char) * dst_size);
	strcpy_s(p->dst,100,destination);
}
*/

Hotel * NEW_NODE(Hotel * parent, float z)
{
	Hotel * newnode = (Hotel*)malloc(sizeof(Hotel));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->price = z;
	newnode->parent = parent;
	newnode->color = RED;
	return newnode;
}

Hotel * RR_ROTATE(Hotel * par)
{
	Hotel * child = par->right;
	par->right = child->left;
	child->left= par;

	return child;
}
Hotel * LL_ROTATE(Hotel * par)
{

	Hotel * child = par->left;
	par->left = child->right;
	child->right = par;

	return child;
}

Hotel * LR_ROTATE(Hotel * par)
{
	Hotel * child = par->left;
	par->left = RR_ROTATE(child);
	return LL_ROTATE(par);
}

Hotel * RL_ROTATE(Hotel * par)
{
	Hotel * child = par->right;
	par->right = LL_ROTATE(child);
	return RR_ROTATE(par);
}
void FIX_FUNCTION(Hotel * node, Hotel * root)
{
	Hotel * parent_node = NULL;
	Hotel * grand_parent_node = NULL;
	Hotel * uncle_node;
	while( (node != root) && (node->color != BLACK) && (node->parent->color == RED)) // successive two red node
	{
	
		parent_node = node->parent;
		grand_parent_node = parent_node->parent;
		uncle_node = grand_parent_node->right;

		if(grand_parent_node == NULL) 
		{
			break;
		}
		if(uncle_node != NULL && uncle_node->color == RED)
		{
			grand_parent_node->color = RED;
			parent_node->color = BLACK;
			uncle_node->color = BLACK;
	
		}
		else
		{
			if(parent_node == grand_parent_node->left)
			{
				
				Hotel * par = grand_parent_node -> parent;
				if(par != NULL)
				{
					if(node == parent_node -> left)
					{
						grand_parent_node -> color = RED;
						parent_node -> color = BLACK;
						if(par->left == grand_parent_node)
							par->left = LL_ROTATE(grand_parent_node);
						else
							par->right = LL_ROTATE(grand_parent_node);
					}
					else
					{
						grand_parent_node -> color = RED;
						node -> color = BLACK;
						if(par->left == grand_parent_node)
							par->left = LR_ROTATE(grand_parent_node);
						else
							par->right = LR_ROTATE(grand_parent_node);
					}
				}
			}
		
			else if(parent_node == grand_parent_node -> right)
			{
				Hotel * par = grand_parent_node -> parent;
				if(par != NULL)
				{
					
					if(node == parent_node -> left)
					{
		
						grand_parent_node -> color = RED;
						node -> color = BLACK;
					
						if(par->left == grand_parent_node)
							par->left = RL_ROTATE(grand_parent_node);
						else							
							par->right = RL_ROTATE(grand_parent_node);
					}
					else
					{
					
						grand_parent_node -> color = RED;
						parent_node -> color = BLACK;
				
						if(par->left == grand_parent_node)
							par->left = RR_ROTATE(grand_parent_node);
						else
							par->right = RR_ROTATE(grand_parent_node);
					}
				}
			}
		}
		node = grand_parent_node;
	}
}

Hotel * TREE_SEARCH(Hotel * root,float k)
{
	Hotel * cur = root;
	Hotel * result;
	if(cur == NULL || cur->price == k) return cur;
	if(k > cur->price) result = TREE_SEARCH(cur->right,k);
	else result =TREE_SEARCH(cur->left,k);
	return result;
}

Hotel *  RB_INSERT(Hotel * root, float z)
{
	Hotel * t = TREE_SEARCH(root,z);
	Hotel * parent = NULL;
	Hotel * child = root;	
	/*----------------------------------------------추가------------------*/
	//z = rand() % 10 + 5;//가격 5만원~15만원 사이 --------

	if(root == NULL)
	{
		root = NEW_NODE(parent,z);
		root->color = BLACK;
		//printf("tree is null %f \n",z);
		return root;
	}
	while(child != NULL)
	{
		if(z == child->price) return root;
		else if(z > child->price) 
		{
			parent = child;
			child = child->right;
		}
		else
		{
			parent = child;
			child = child->left;
		}
	}
	if(z > parent->price)
	{
		parent->right = NEW_NODE(parent,z);
		FIX_FUNCTION(parent->right,root);
	}
	else
	{
		parent->left = NEW_NODE(parent,z);
		FIX_FUNCTION(parent->left,root);
	}
	root->color = BLACK;

	return root;
}

void PRINT_BST(Hotel * root)
{
	if(root == NULL) return;
	printf("%.2lf ",root->price);
	PRINT_BST(root->left);
	PRINT_BST(root->right);
	
}

int height(Hotel * root)
{
	if(root == NULL) return 0;
	else
	{
		int l = height(root->left);
		int r = height(root->right);
		if( l > r )
			return l+1;
		else
			return r+1;
	}
}


void swapColors(Hotel *x1, Hotel *x2)
{
	enum Color temp;
	temp = x1->color;
	x1->color = x2->color;
	x2->color = temp;
}

void swapValues(Hotel *u, Hotel *v)
{
	float temp;
	temp = u->price;
	u->price = v->price;
	v->price = temp;
}

Hotel *successor(Hotel *x)
{
	Hotel *temp = x;

	while (temp->left != NULL)
		temp = temp->left;

	return temp;
}
int isOnLeft(Hotel * self)
{
	if (self == self->parent->left)	return 1;
	else return 0;
}

Hotel * uncle(Hotel * parent)
{
	// If no parent or grandparent, then no uncle 
	if (parent == NULL || parent->parent == NULL)
		return NULL;

	if (isOnLeft(parent)) return parent->parent->right;
	else return parent->parent->left;

}

Hotel * find_replace(Hotel *x)
{
	// when node have 2 children 
	if (x->left != NULL && x->right != NULL)
		return successor(x->right);

	// when leaf 
	if (x->left == NULL && x->right == NULL)
		return NULL;

	// when single child 
	if (x->left != NULL)
		return x->left;
	else
		return x->right;
}
void moveDown(Hotel * nParent, Hotel * v)
{
	if (v->parent != NULL) {
		if (isOnLeft(v)) {
			v->parent->left = nParent;
		}
		else {
			v->parent->right = nParent;
		}
	}
	nParent->parent = v->parent;
	v->parent = nParent;
}

int hasRedChild(Hotel * v) {
	return (v->left != NULL && v->left->color == RED) || (v->right != NULL && v->right->color == RED);
}
Hotel * sibling(Hotel * v) {
	if (v->parent == NULL) return NULL;
	if (isOnLeft(v)) return v->parent->right;
	else return v->parent->left;
}

void leftRotate(Hotel *x, Hotel * root)
{
	Hotel * nParent = x->right;

	if (x == root) root = nParent;
	moveDown(nParent, x);

	
	x->right = nParent->left;

	if (nParent->left != NULL) nParent->left->parent = x;

	nParent->left = x;
}


void rightRotate(Hotel * x, Hotel * root)
{
	Hotel *nParent = x->left;

	// update root if current node is root 
	if (x == root)
		root = nParent;

	moveDown(nParent,x);

	// connect x with new parent's right element 
	x->left = nParent->right;
	// connect new parent's right element with node 
	// if it is not null 
	if (nParent->right != NULL)
		nParent->right->parent = x;

	// connect new parent with x 
	nParent->right = x;
}

void fixRedRed(Hotel * x,Hotel * root)
{
	if (x == root) {
		x->color = BLACK;
		return;
	}

	// initialize parent, grandparent, uncle 
	Hotel *parent = x->parent;

	Hotel *grandparent = parent->parent;

	Hotel * unclee = uncle(x);
		

	if (parent->color != BLACK) {
		if (unclee != NULL && unclee->color == RED) {
			// uncle red, perform recoloring and recurse 
			parent->color = BLACK;
			unclee->color = BLACK;
			grandparent->color = RED;
			fixRedRed(grandparent,root);
		}
		else {
			// Else perform LR, LL, RL, RR 
			if (isOnLeft(parent)) {
				if (isOnLeft(x)) {
					// for left right 
					swapColors(parent, grandparent);
				}
				else {
					leftRotate(parent,root);
					swapColors(x, grandparent);
				}
				// for left left and left right 
				rightRotate(grandparent,root);
			}
			else {
				if (isOnLeft(x)) {
					// for right left 
					rightRotate(parent,root);
					swapColors(x, grandparent);
				}
				else {
					swapColors(parent, grandparent);
				}

				// for right right and right left 
				leftRotate(grandparent,root);
			}
		}
	}
}
void fixDoubleBlack(Hotel * x, Hotel * root)
{
	if (x == root)
		// Reached root 
		return;

	Hotel *siblingg = sibling(x), *parent = x->parent;
	if (siblingg == NULL) {
		// No sibiling, double black pushed up 
		fixDoubleBlack(parent,root);
	}
	else {
		if (siblingg->color == RED) {
			// Sibling red 
			parent->color = RED;
			siblingg->color = BLACK;
			if (isOnLeft(siblingg)) {
				// left case 
				rightRotate(parent,root);
			}
			else {
				// right case 
				leftRotate(parent,root);
			}
			fixDoubleBlack(x,root);
		}
		else {
			// Sibling black 
			if (hasRedChild(siblingg)) {
				// at least 1 red children 
				if (siblingg->left != NULL && siblingg->left->color == RED) {
					if (isOnLeft(siblingg)) {
						// left left 
						siblingg->left->color = siblingg->color;
						siblingg->color = parent->color;
						rightRotate(parent,root);
					}
					else {
						// right left 
						siblingg->left->color = parent->color;
						rightRotate(siblingg,root);
						leftRotate(parent,root);
					}
				}
				else {
					if (isOnLeft(siblingg)) {
						// left right 
						siblingg->right->color = parent->color;
						leftRotate(siblingg,root);
						rightRotate(parent,root);
					}
					else {
						// right right 
						siblingg->right->color = siblingg->color;
						siblingg->color = parent->color;
						leftRotate(parent,root);
					}
				}
				parent->color = BLACK;
			}
			else {
				// 2 black children 
				siblingg->color = RED;
				if (parent->color == BLACK)
					fixDoubleBlack(parent,root);
				else
					parent->color = BLACK;
			}
		}
	}
}
void deleteNode(Hotel * v, Hotel * root)
{
	Hotel * u = find_replace(v);
	int uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
	Hotel * parent = v->parent;

	if (u == NULL) {
		//u is null -> v is leaf
		if (v == root) {
			// v is root, make root null
			root = NULL;
		}
		else {
			if (uvBlack) {
				// u and v are both black 
				// v is leaf, fix double black at v
				fixDoubleBlack(v,root);
			}
			else {
				// u or v is red
				if (sibling(v) != NULL)
				{
					sibling(v)->color = RED;
				}
			}
		}
		//delete v from the tree
		if (isOnLeft(v)) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
		free(v);
		return;
		
	}

	if (v->left == NULL || v->right == NULL) {
		//v has one child
		if (v == root) {
			//v is root, set the value of u to v, and delete u
			v->price = u->price;
			v->left = v->right = NULL;
			free(u);
		}
		else {
			//detach v from tree and move u up
			if (isOnLeft(v)) {
				parent->left = u;
			}
			else {
				parent->right = u;
			}
			free(v);
			u->parent = parent;
			if (uvBlack) {
				fixDoubleBlack(u,root);
			}
			else {
				u->color = BLACK;
			}
		}
		return;
	}

	//v has two children, swap values with successor and recurse
	swapValues(u, v);
	deleteNode(u,root);
}
void deleteByVal(float n, Hotel * root) {
	if (root == NULL)
		// Tree is empty 
		return;

	Hotel *v = TREE_SEARCH(root,n), *u;

	if (v->price != n) {
		printf("Cannot find node!\n");
		return;
	}

	deleteNode(v,root);
}

//sites: 각 사이트는 이름포인터와 시간을 가진 루트 & 그래프의 vertex
//그래프의 vertex는 구조체 안에 sitename


void make_sites (sites * S) {
	
	for (int i = 1; i <= 100; i++) {
		int time = (rand() % 6) + 5;   //한 관광지를 관광하는 시간 5~10시간				
	//	S[i]가 site이름으로도 작용
		S[i].tourtime = time;
		//printf("site %d : %d\n", i, S[i].tourtime);
	}

}

void make_graph(int graph[][SIZE+1]) {		//matrix 그래프
	int i, j ,k;
	
	//printf("done\n");
	for (i = 1; i <= SIZE; i++) {
		for (j = i; j <= SIZE; j++) {
			
			graph[i][j]=(rand() % 10001) + 500;		//여행거리 500~10500km
		
		}
	}
	for (k = 0; k < 4650; k++) {
	
		i = rand() % SIZE + 1;
		j = rand() % SIZE + 1;
		if (graph[i][j] == 0)
		{
			continue;
		}
		graph[i][j] = 0;
	}

	for (i = 1; i <= SIZE; i++) {
		for (j = i; j <= SIZE; j++) {
			graph[j][i] = graph[i][j];
		}
	}
}


Priority_Node * Priority_New_Node(int vertex, int priority)
{
	Priority_Node * temp = (Priority_Node*)malloc(sizeof(Priority_Node));
	temp->priority = priority;
	temp->vertex = vertex;
	temp->next = NULL;
	return temp;
}

Priority_Node *  peek(Priority_Node ** head)
{
	return (*head);
}

void pop(Priority_Node ** head)
{
	Priority_Node * temp = *head;
	(*head) = (*head)->next;
	free(temp);
}

void push(Priority_Node ** head, int vertex, int priority)
{
	Priority_Node * start = (*head);

	Priority_Node * temp = Priority_New_Node(vertex, priority);
	
	if (*head == NULL) {
		
		*head = temp;
		
	}
	else if ((*head)->priority >= priority) {
		temp->next = (*head);
		(*head) = temp;
		
	}
	else
	{
	
		// Traverse the list and find a position to insert new node
		while (start->next != NULL && (start->next->priority < priority)) {
			start = start->next;
		}

		temp->next = start->next;
		start->next = temp;
	}
}

int isEmpty(Priority_Node ** head)
{
	return (*head) == NULL;
}

void dijkstra(int graph[][SIZE + 1], int * parent_vertex, int start_vertex) {

	int memo[SIZE + 1];
	Priority_Node * pq = Priority_New_Node(start_vertex, 0); // initialization of priority queue with start_vertex

	// start ,end is pointing variable in queue data structure

	for (int n = 1; n <= SIZE; n++) {
		memo[n] = INF;
	}
	memo[start_vertex] = 0;

	//make all value of value except for start vertex "INF"
	Priority_Node * temp;
	int vertex;
	int temp_priority;
	while (!isEmpty(&pq))
	{
		temp = peek(&pq);
		temp_priority = temp->priority;
		vertex = temp->vertex;
		pop(&pq);
		if (memo[vertex] < temp_priority) continue;


		for (int i = 1; i <= SIZE; i++)
		{
			if (graph[vertex][i] != 0) // graph[vertex][i] 가 0 이면 연결정보가 아예없는것이므로 볼 필요도 없다.
			{
				if (memo[vertex] + graph[vertex][i] <= memo[i])
				{
					memo[i] = memo[vertex] + graph[vertex][i];
					parent_vertex[i] = vertex;
					push(&pq, i, memo[i]);
				}
			}

		}

	}
}
int *  print_path(int start, int end, int* parent_vertex) 
{
	int path[SIZE + 1];
	int i = 0;
	int flag = 0;
	int next = end;
	memset(path, 0, sizeof(path));
	path[i++] = end;
	while (next != start && next != 0)
	{
		next = parent_vertex[next];
		if(next != 0) path[i++] = next;
		
	}
	for (int idx = 0; idx <= i; idx++)
	{
		if (path[idx] == start) flag = 1;
	}
	if (flag != 1) {
		//printf("Path does not exist!\n");
	}
	else
	{
		for (int idx = i; idx >= 0; idx--)
		{
			if (path[idx] != 0) {
				//printf("%d ->", path[idx]);
			}
		}
		//printf("end\n");
		
	}
	
	//printf("\n");

	return path;
}

float find_cheapest_hotel(Hotel * root)
{
	Hotel * cur = root;
	if (cur == NULL) {
		return 0;
	}
	while (cur->left != NULL)
	{
		cur = cur->left;
	}
	//if (cur == NULL) printf("it's null\n");
	return cur->price;
}
	
int check_route(Person* p, sites * S, int *path_vertex, int graph[][SIZE + 1])
{	
	int i = 0;

	for (i; path_vertex[i] != 0; i++);
	float total_price=0;
	float total_date = 0;
	int idx = i-1;
	int val = 1;
	int j = 0;

	for (idx; idx >= 0; idx--) {
		val = path_vertex[idx];
		float price = find_cheapest_hotel(S[val].H);

		p->data[0][j] = val;
		p->data[1][j] = price;
		p->data[2][j] = S[val].tourtime;
		if (idx ==0) {
			p->data[3][j] = 0;
		}
		else {
			p->data[3][j] = graph[val][path_vertex[idx - 1]];
		}
		j++;
	}
	
	for (int k = 0; k < i; k++) {
		total_price += p->data[1][k] * p->data[2][k];
		total_price += p->data[3][k] * 4;
		total_date += p->data[2][k];
		total_date += p->data[3][k] / 1000;
	}
	//printf("price : %f | date : %f\n", total_price, total_date);

	if (p->budget < total_price || p->date < total_date) return 0;
	return 1;
}


/*추가 : site[1~100]에다가 rb insert하기*/
void Connect(sites *S){
	int i, j;
	//루트노트: S[i].H
	for (i = 1; i <= 100; i++) {//site랑 호텔 연결 100번
		//RB_INSERT(S[i].H, rand() % 10 + 5.0);
		for (j = 0; j < 100; j++) {//각 사이트에 호텔 100개 rbinsert 100번
			S[i].H=RB_INSERT(S[i].H, rand() % 10 + 5.0);
		}
		
	}
}






/*추가 : 가진 시간/돈에서 site지날때마다 빼기 . 다익 코드 안에 함수 넣으면 될 것 같아요
void Wallet (int **graph, sites *S, Person *P, int p, int j, Hotel *H, int idx) {
	Hotel currentHotel = *S[idx].H;
	float won = currentHotel.price;
	P->budget -= won;//형태확인
	P->date -= S->tourtime;
}*/

Person* left_rotate(Person* tree, Person* base)
{
	Person* y = base->right;
	base->right = y->left;

	if (y->left != nil)
		y->left->p = base;

	y->p = base->p;

	if (base->p == nil)
		tree = y;
	else if (base == base->p->left)
		base->p->left = y;
	else
		base->p->right = y;

	y->left = base;
	base->p = y;

	return tree;
}

// 우회전 함수

Person* right_rotate(Person* tree, Person* base)
{
	Person* y = base->left;
	base->left = y->right;

	if (y->right != nil)
		y->right->p = base;

	y->p = base->p;

	if (base->p == nil)
		tree = y;
	else if (base == base->p->right)
		base->p->right = y;
	else
		base->p->left = y;

	y->right = base;
	base->p = y;

	return tree;
}


Person* RB_insert_fixup(Person* tree, Person* input)
{
	Person* y;

	while (input->p->color == RED)
	{
		if ((input->p) == (input->p->p->left))
		{
			y = input->p->p->right;
			if (y->color == RED)
			{
				input->p->color = BLACK;
				y->color = BLACK;
				input->p->p->color = RED;
				input = input->p->p;
			}
			else
			{
				if (input == input->p->right)
				{
					input = input->p;
					tree = left_rotate(tree, input);
				}
				input->p->color = BLACK;
				input->p->p->color = RED;
				tree = right_rotate(tree, input->p->p);
			}
		}
		else
		{
			y = input->p->p->left;
			if (y->color == RED)
			{
				input->p->color = BLACK;
				y->color = BLACK;
				input->p->p->color = RED;
				input = input->p->p;
			}
			else
			{
				if (input == input->p->left)
				{
					input = input->p;
					tree = right_rotate(tree, input);
				}
				input->p->color = BLACK;
				input->p->p->color = RED;
				tree = left_rotate(tree, input->p->p);
			}
		}
	}
	tree->color = BLACK;
	return tree;
}
// 삽입 함수
// tree 에다가 input을 넣어서 새로운 tree를 반환
Person* RB_insert(Person* tree, Person* input)
{
	Person* y = nil;
	Person* x = tree;
	while (x != nil)
	{
		y = x;
		if ((input->id) < (x->id)) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	input->p = y;
	if (y == nil)
		tree = input;
	else if ((input->id) < (y->id))
		y->left = input;
	else
		y->right = input;

	input->left = nil;
	input->right = nil;
	input->color = RED;
	return RB_insert_fixup(tree, input);
}


//----------노드 생성 관련 ------------//
Person* make_node(int i, float bud, int dat, int st, int ds)
{
	Person* tmp;
	tmp = (Person*)malloc(sizeof(Person));
	tmp->id = i;
	tmp->budget = bud;
	tmp->date = dat;
	tmp->dst = ds;
	tmp->start = st;
	tmp->left = nil;
	tmp->right = nil;
	tmp->p = nil;
	return tmp;
}
Person* make_nil()
{
	Person* tmp;
	tmp = (Person*)malloc(sizeof(Person));
	tmp->id = 0;
	tmp->budget = 0;
	tmp->date = 0;
	tmp->dst = 0;
	tmp->start = 0;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->p = NULL;
	tmp->color = BLACK;
	return tmp;
}
//-----------------------------------//

Person* tree_minimum(Person* root)
{
	Person* tmp = root;

	while (tmp->left != nil)
	{
		tmp = tmp->left;
	}
	return tmp;
}

Person* tree_successor(Person* root)
{
	Person* tmp;
	if (root->right != nil)
		return tree_minimum(root->right);

	tmp = root->p;

	while ((tmp != nil) && (root == tmp->right))
	{
		root = tmp;
		tmp = tmp->p;
	}
	return tmp;
}
Person* RB_delete_fixup(Person* tree, Person* put)
{
	Person* w;
	while ((put != tree) && (put->color == BLACK))
	{
		if (put == put->p->left)
		{
			w = put->p->right;
			if (w->color == RED)
			{
				w->color = BLACK;
				put->p->color = RED;
				tree = left_rotate(tree, put->p);
				w = put->p->right;
			}
			if ((w->left->color == BLACK) && (w->right->color == BLACK))
			{
				w->color = RED;
				put = put->p;
			}
			else
			{
				if (w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					tree = right_rotate(tree, w);
					w = put->p->right;
				}
				w->color = put->p->color;
				put->p->color = BLACK;
				w->right->color = BLACK;
				tree = left_rotate(tree, put->p);
				put = tree;
			}
		}
		else
		{
			w = put->p->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				put->p->color = RED;
				tree = right_rotate(tree, put->p);
				w = put->p->left;
			}
			if ((w->right->color == BLACK) && (w->left->color == BLACK))
			{
				w->color = RED;
				put = put->p;
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					tree = left_rotate(tree, w);
					w = put->p->left;
				}
				w->color = put->p->color;
				put->p->color = BLACK;
				w->left->color = BLACK;
				tree = right_rotate(tree, put->p);
				put = tree;
			}
		}
	}
	put->color = BLACK;
	return tree;
}

Person* RB_delete(Person* tree, Person* put)
{
	Person* y;
	Person* x;
	if ((put->left == nil) || (put->right == nil))
		y = put;
	else
		y = tree_successor(put);
	if (put->left != nil)
		x = y->left;
	else
		x = y->right;

	x->p = y->p;

	if (y->p == nil)
		tree = x;
	else
	{
		if (y == y->p->left)
			y->p->left = x;
		else
			y->p->right = x;
	}
	if (y != put)
		put->id = y->id;
	if (y->color == BLACK)
		tree = RB_delete_fixup(tree, x);

	return tree;
}
// 트리에서 데이터 찾는다.
Person* tree_search(Person* tree, int d)
{
	Person* root;
	root = tree;

	while ((root != nil) && (d != root->id))
	{
		if (d < root->id)
			root = root->left;
		else
			root = root->right;
	}
	return root;
}

// INORDER 로 탐색하면서 깊이만큼 출력합니다.
// 출력되는 모양은 트리가 옆으로 누운 모양입니다.
void print_inorder(Person* tree, int level)
{
	int i;
	if (tree != nil)
	{
		print_inorder(tree->right, level + 1);

		for (i = 0; i<level; i++)
			printf("    |");
		//color
		if (tree->color == RED)
			printf("R");
		else
			printf("B");

		printf("[%d]\n", tree->id);

		print_inorder(tree->left, level + 1);
	}
}

// 트리를 모두 지웁니다. (레드블랙은 이진트리 기반)
void delete_all(Person* tree)
{
	if (tree != nil)
	{
		delete_all(tree->left);
		delete_all(tree->right);
		free(tree);
	}
}