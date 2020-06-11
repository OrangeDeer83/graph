#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct Node {
	int vertice;
	struct Node* next;
};

struct List {
	int size;
	struct Node* first;
};

struct Graph {
	int vertice;
	struct List* fir_array;
};

struct Queue {
	struct Node* front;
	struct Node* rear;
	int size;
};

void creat_graph(int, struct Graph*);
void add_edge(int, int, struct Graph*);
bool find(int, struct List*);
void BFS(int, struct Graph*);
void add_queue(int, struct Queue*);
int de_queue(struct Queue*);
void DFS(int, struct Graph*);
void dfs(int, struct Graph*, int*);
void delete_graph(struct Graph*);


int main(void) {
	int number, one, two;

	printf("Enter the vertice of the graph: ");
	scanf("%d", &number);
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph) * number);
	creat_graph(number, graph);
	do {
		printf("Enter the path you want to insert(ex: 1 2, 3 4, 5 2) and -1 to exit: ");
		scanf("%d", &one);
		if (one == -1) {
			break;
		}
		scanf("%d", &two);
		while (one >= graph->vertice || one < 0 || two >= graph->vertice || two < 0) {
			if (one == -1) {
				break;
			}
			printf("Number out of range, please enter again: ");
			scanf("%d", &one);
			scanf("%d", &two);
		}
		if (one == -1) {
			break;
		}
		add_edge(one, two, graph);
	} while (true);

	printf("Enter the vertix you want to visit: ");
	scanf("%d", &number);
	while (number > graph->vertice || number < 0) {
		printf("Number out of range, please enter again: ");
	}

	printf("\nBFS:");
	BFS(number, graph);
	printf("\nDFS:");
	DFS(number, graph);

	delete_graph(graph);

	system("PAUSE");
	return 0;
}

void creat_graph(int number, struct Graph* graph) {
	graph->vertice = number;
	struct List* newList = (struct List*)malloc(sizeof(struct List) * number);
	graph->fir_array = newList;

	for (int i = 0; i < number; i++) {
		graph->fir_array[i].first = NULL;
	}
}

void add_edge(int one, int two, struct Graph* graph) {
	if (!find(one, &(graph->fir_array[two]))) {
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->next = graph->fir_array[two].first;
		newNode->vertice = one;
		graph->fir_array[two].first = newNode;
		graph->fir_array[two].size++;
		newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->next = graph->fir_array[one].first;
		newNode->vertice = two;
		graph->fir_array[one].first = newNode;
		graph->fir_array[one].size++;
	}
	else {
		printf("The edge is already exist!!\n");
	}
}

bool find(int target, struct List* list) {
	struct List* temp = list;
	bool found = false;
	while (temp->first) {
		if ((temp->first)->vertice == target) {
			found = true;
			break;
		}
		temp->first = (temp->first)->next;
	}

	return found;
}

void BFS(int number, struct Graph* graph) {
	struct List* temp;
	struct Queue* que = (Queue*)malloc(sizeof(struct Queue));
	que->size = 0;
	int* path = (int*)malloc(sizeof(int) * graph->vertice);
	int next;

	for (int j = 0; j < graph->vertice; j++) {
		path[j] = 0;
	}

	add_queue(number, que);
	while (que->size != 0) {
		next = de_queue(que);
		path[next] = 1;

		printf("%d -> ", next);

		
		temp = &(graph->fir_array[next]);
		struct Node* newNode = temp->first;
		while (newNode) {
			if (!path[newNode->vertice]) {
				path[newNode->vertice] = 1;
				add_queue(newNode->vertice, que);
			}
			newNode = newNode->next;
		}
	}

	printf("end ");

	for (int i = 0; i < graph->vertice; i++) {
		if (!path[i]) {
			path[i] = 1;
			add_queue(i, que);
			while (que->size != 0) {
				next = de_queue(que);
				printf("%d -> ", next);

				temp = &(graph->fir_array[next]);
				struct Node* newNode = temp->first;
				while (newNode) {
					if (!path[newNode->vertice]) {
						path[newNode->vertice] = 1;
						add_queue(newNode->vertice, que);
					}
					newNode = newNode->next;
				}
			}
			printf("end ");
		}
	}

	printf("\n");
	free(que);
	free(path);
}

void add_queue(int add, struct Queue* que) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->vertice = add;
	
	if (que->size == 0) {
		que->front = newNode;
		que->rear = newNode;
	}
	else {
		que->rear->next = newNode;
		que->rear = newNode;
	}

	que->size++;
}

int de_queue(struct Queue* que) {
	if (que->size == 0) {
		return -1;
	}
	else {
		struct Node* node = que->front;
		int number = node->vertice;

		que->front = node->next;
		que->size--;

		free(node);
		return number;
	}
}

void DFS(int number, struct Graph* graph) {
	int cur;
	int* path = (int*)malloc(sizeof(int) * graph->vertice);
	int next = number;

	for (int j = 0; j < graph->vertice; j++) {
		path[j] = 0;
	}

	dfs(number, graph, path);
	printf("end ");
	
	for (int i = 0; i < graph->vertice; i++) {
		if (!path[i]) {;
			dfs(i, graph, path);
			printf("end ");
		}
	}

	printf("\n");
	free(path);
}

void dfs(int cur, struct Graph* graph, int* path) {
	struct Node* temp = graph->fir_array[cur].first;
	
	if (!path[cur]) {
		printf("%d -> ", cur);
		path[cur] = 1;
	}
	while (temp) {
		if (!path[temp->vertice]) {
			dfs(temp->vertice, graph, path);
		}

		temp = temp->next;
	}
}

void delete_graph(struct Graph* graph) {
	struct Node *del_node, *temp;
	for (int i = 0; i < graph->vertice; i++) {
		del_node = graph->fir_array[i].first;
		
		while (del_node) {
			temp = del_node;
			del_node = del_node->next;
			free(temp);
		}
	}
	free(graph->fir_array);
}