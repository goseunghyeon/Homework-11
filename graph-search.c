#include<stdio.h>
#include<stdlib.h>

#define Max 10
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
			//deapthFirstSearch();
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
			//breathFirstSearch();
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

Root* initializeGraph() {
	Root* root = (Root*)malloc(sizeof(Root));
	root->n = 0;

	for (int i = 0; i < Max; i++) {
		root->list[i] = NULL;
	}
	return root;
}

void insertVertex(Root* root) {
	root->list[root->n] = (Node*)malloc(sizeof(Node));
	root->list[root->n]->vertex = root->n;
	root->list[root->n]->next = NULL;

	root->n++;
}
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