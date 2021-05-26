#include<stdio.h>
#include<stdlib.h>

#define Max 10
#define FALSE 0
#define TRUE 1
short int visited[Max];
int que[10] = { NULL };
int front = 0;
int rear = 0;

typedef struct Node{
	int vertex;
	struct Node* next;
}Node;

typedef struct Root {
	int n;
	Node* list[Max];
}Root;

Root* initializeGraph();
void insertVertex(Root* root);
void printGraph(Root* root);
void insertEdge(Root* root, int x, int y);
void deapthFirstSearch(int n, Root* root);
void arraySet(short int* visited);
void breathFirstSearch(int n, Root* root);
void addQue(int n);
int deleteQue(void);
int main()
{
	char command;
	Root* root = NULL;
	int x, y;
	
	

	do {
		printf("[----- [고승현] [2016039086] -----]\n");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                       \n");
		printf(" Insert Vertex          = v      Insert Edge               = e \n");
		printf(" Depth First Search     = d      Breath First Search       = b \n");
		printf(" Print Graph            = p      Quit                      = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			root=initializeGraph();
			break;
		case 'v': case 'V':
			insertVertex(root);
			break;
		case 'd': case 'D':
			printf("start vertex:");
			scanf("%d", &x);
			arraySet(visited);
			deapthFirstSearch(x,root);
			printf("\n");
			break;
		case 'p': case 'P':
			printGraph(root);
			break;
		case 'e': case 'E':
			printf("insert two key:");
			scanf("%d%d", &x,&y);
			insertEdge(root,x,y);
			break;
		case 'b': case 'B':
			printf("start vertex");
			scanf("%d", &x);
            arraySet(visited);
			breathFirstSearch(x,root);
			break;

		case 'q': case 'Q':
			break;
		
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}
/*그래프의 총개수를 초기화하고
그래프의 연결을 초기화*/
Root* initializeGraph() {
	Root* root = (Root*)malloc(sizeof(Root));
	root->n = 0;

	for (int i = 0; i < Max; i++) {
		root->list[i] = NULL;
	}
	return root;
}
/*정점을 생성하는 함수로 호출시마다
순번대로 정점생성*/
void insertVertex(Root* root) {
	root->list[root->n] = (Node*)malloc(sizeof(Node));
	root->list[root->n]->vertex = root->n;
	root->list[root->n]->next = NULL;

	root->n++;
}
/*엣지를 추가하는 함수로 
정점을 생성후 원하는 엣지끼리 서로연결
각 연결은 정점의 크기순서로 연결되게 구현*/
void insertEdge(Root* root, int x, int y) {
	Node* prev=NULL;
	Node* sel=NULL;
	if (x >= root->n || y >= root->n) {
		printf("range out\n");
		return;
	}
	else if (root->list[x] == NULL || root->list[y] == NULL) {
		printf("no vertex\n");
		return;
	}
	else {
		Node* temp_x = (Node*)malloc(sizeof(Node));
		Node* temp_y = (Node*)malloc(sizeof(Node));

		temp_x->vertex = x;
		temp_y->vertex = y;
		temp_x->next = NULL;
		temp_y->next = NULL;
		if (root->list[y]->next == NULL) {
			root->list[y]->next = temp_x;
		}
		else {
			sel = root->list[y]->next;
			prev = root->list[y];
			while (sel != NULL) {
				if (sel->vertex > temp_x->vertex) {
					temp_x->next = sel;
					prev->next = temp_x;
					break;
				}
				prev = sel;
				sel = sel->next;

				if (sel == NULL) {
					prev->next = temp_x;
					break;
				}
			}
			
		}

		if (root->list[x]->next == NULL) {
			root->list[x]->next = temp_y;
		}
		else {
			sel = root->list[x]->next;
			prev = root->list[x];
			while (sel != NULL) {
				if (sel->vertex > temp_y->vertex) {
					temp_y->next = sel;
					prev->next = temp_y;
					break;
				}
				prev = sel;
				sel = sel->next;

				if (sel == NULL) {
					prev->next = temp_y;
					break;
				}
			}
		}
		
	}
}
/*각 정점에 연결된 노드를 출력하는 함수*/
void printGraph(Root* root) {
	int i = 0;
	for (i; i < Max; i++) {
		Node* sel = root->list[i];
		printf("vertex:%d:", i);
		if(sel!=NULL)
		sel = sel->next;
		for (; sel; sel = sel->next) {
			printf("%d->", sel->vertex);
		}
		printf("\n");
	}
}
/*탐색을 위한 배열 초기화*/
void arraySet(short int* visited) {
	for (int i = 0; i < Max; i++) {
		visited[i] = 0;
	}
}
/*깊이 우선탐색으로 재귀를 이용하여 배열을 탐색시1로 
바꾸면서 출력한다 한번 탐색한 위치는 탐색을 안한다*/
void deapthFirstSearch(int n, Root* root) {
	
	Node* sel=root->list[n];
	if (sel == NULL) {
		printf("No such vertex\n");
		return;
	}
	visited[n] = TRUE;
	printf("%5d", n);
	for (sel = sel->next; sel; sel = sel->next) {
		if (!visited[sel->vertex])
			deapthFirstSearch(sel->vertex,root);
	}

}
/*너비우선 탐색으로 기준 정점에서 큐를 이용하여
레벨별로 상대적으로 출력한다*/
void breathFirstSearch(int n, Root* root) {
	front = 0;
	rear = 0;
	for (int i = 0; i < Max; i++) {
		que[i] = NULL;
	}
	Node* sel = root->list[n];
	if (sel == NULL) {
		printf("No such vertex\n");
		return;
	}
	printf("%5d", n);
	visited[n] = TRUE;
	addQue(n);

	while(front!=rear){
		n=deleteQue();
		
		for (sel = root->list[n]->next; sel; sel = sel->next) {
			if (!visited[sel->vertex]) {
				printf("%5d", sel->vertex);
				addQue(sel->vertex);
				visited[sel->vertex] = TRUE;
			}
		}
	}


}
/*큐를 추가 원형큐*/
void addQue(int n) {

	if ((rear+1)%Max== front) {
		printf("Queue is full.");
	}
	else {
		rear = (rear+1)%Max;
		que[rear] = n; 
	}

}
/*큐제거 */
int deleteQue(void) {

	int x = NULL;
	if (front == rear) {
	   printf("Queue is empty.");
	}
	else {
        x = que[front];
		front = (front+1)%Max;
		que[front]=NULL;
	}
	return x;
	
}
