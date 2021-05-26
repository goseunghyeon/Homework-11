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
//void printGraph(Root* root);
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
			//printGraph(root);
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
	root->list[root->n]->vertex = -1;
	root->list[root->n]->next = NULL;

	root->n++;
}
void insertEdge(Root* root, int x, int y) {
	if (x >= root->n || y >= root->n) {
		printf("full");
		return;
	}
	else {
		Node* temp_x = (Node*)malloc(sizeof(Node));
		Node* temp_y = (Node*)malloc(sizeof(Node));

		temp_x->vertex = x;
		temp_y->vertex = y;

		temp_x->next = root->list[y];
		root->list[y]->next = temp_x;
		temp_y->next = root->list[x];
		root->list[x]->next = temp_y;

	}
}