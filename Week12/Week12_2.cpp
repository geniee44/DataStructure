#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphNode {
	int weight;
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

int found[MAX_VERTICES];
int distance[MAX_VERTICES];

void init(GraphType* g) {
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
		g->adj_list[i] = NULL;
}

void insert_vertex(GraphType* g, int v) {
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과\n");
		return;
	}
	else g->n++;
}

void insert_edge(GraphType* g, int u, int v, int w) {
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류\n");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->weight = w;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_status(GraphType* g) {
	static int step = 1;
	printf("STEP %d: \n", step++);
	printf(" distance: ");
	int i = step - 1;
	GraphNode* node = g->adj_list[i];
	while (node != NULL) {
		distance[i] = node->weight;
		node = node->link;
	}
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
	int i, u, w;
	//for (i = 0; i < g->n; i++) {
	//	distance[i] = g->adj_list[i]->weight;
	//	found[i] = FALSE;
	//}
	/*for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];
		while (node != NULL) {
			distance[i] = node->weight;
			node = node->link;
		}
	}*/
	found[start] = TRUE;
	distance[start] = 0;
	printf("<Shortest Path - Dijkstra 결과>\n");
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++) {
			if (!found[w])
				//if (distance[u] + g->weight[u][w] < distance[w])
				//	distance[w] = distance[u] + g->weight[u][w];
				if (distance[u] + g->adj_list[u]->weight < distance[w])
					distance[w] = distance[u] + g->adj_list[u]->weight;
		}
	}
	print_status(g);
}

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 7; i++) insert_vertex(g, i);
	insert_edge(g, 0, 1, 7);
	insert_edge(g, 0, 4, 3);
	insert_edge(g, 0, 5, 10);
	insert_edge(g, 1, 0, 7);
	insert_edge(g, 1, 2, 4);
	insert_edge(g, 1, 3, 10);
	insert_edge(g, 1, 4, 2);
	insert_edge(g, 1, 5, 6);
	insert_edge(g, 2, 1, 4);
	insert_edge(g, 2, 3, 2);
	insert_edge(g, 3, 1, 10);
	insert_edge(g, 3, 2, 2);
	insert_edge(g, 3, 4, 11);
	insert_edge(g, 3, 5, 9);
	insert_edge(g, 3, 6, 4);
	insert_edge(g, 4, 0, 3);
	insert_edge(g, 4, 1, 2);
	insert_edge(g, 4, 3, 11);
	insert_edge(g, 4, 6, 5);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 5, 1, 6);
	insert_edge(g, 5, 3, 9);
	insert_edge(g, 6, 3, 4);
	insert_edge(g, 6, 4, 5);
	shortest_path(g, 0);
	return 0;
}
