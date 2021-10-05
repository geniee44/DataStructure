#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0
#define INF 1000

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

int vertex[MAX_VERTICES];
int parent[MAX_VERTICES];

struct Edge {
	int start, end, weight;
};

typedef struct GraphType {
	int n;
	int vertextCnt;
	struct Edge edges[2 * MAX_VERTICES];
}GraphType;


/*================= Quick Sort =================*/
int partition(struct Edge edges[], int left, int right)
{
	struct Edge pivot, temp;
	int low, high;
	low = left;
	high = right + 1;
	pivot.weight = edges[left].weight;
	do {
		do
			low++;
		while (low <= right && edges[low].weight < pivot.weight);
		do
			high--;
		while (high >= left && edges[high].weight > pivot.weight);
		if (low < high) SWAP(edges[low], edges[high], temp);
	} while (low < high);
	SWAP(edges[left], edges[high], temp);
	return high;
}
void quick_sort(struct Edge edges[], int left, int right)
{
	if (left < right) {
		int q = partition(edges, left, right);
		quick_sort(edges, left, q - 1);
		quick_sort(edges, q + 1, right);
	}
}

/*================= Union-Find =================*/
void set_init(int n) {
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int curr) {
	if (parent[curr] == -1)	return curr;
	while (parent[curr] != -1)	curr = parent[curr];
	return curr;
}

void set_union(int a, int b) {
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2)parent[root1] = root2;
}

/*================= Graph drawing =================*/
void graph_init(GraphType* g) {
	g->n = 0;
	g->vertextCnt = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void insert_edge(GraphType* g, int start, int end, int w) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

/*================= Kruskal =================*/
void kruskal(GraphType* g) {
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	set_init(g->n);
	quick_sort(g->edges, 0, g->n - 1);
	printf("\n<Sort 결과>\n");
	for (int i = 0; i < g->n; i++)
		printf("%2d - %2d: %2d\n", g->edges[i].start, g->edges[i].end, g->edges[i].weight);
	printf("\n<Kruskal MST 결과>\n");
	int i = 0;
	while (edge_accepted < (g->vertextCnt - 1)) {
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			printf("Edge (%d,%d) %d \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}

void vertex_cnt(GraphType* g) {
	int cnt = 0;
	for (int i = 0; i < g->n; i++) {
		if (vertex[g->edges[i].start] == 0) {
			vertex[g->edges[i].start] = 1;
			cnt++;
		}
		if (vertex[g->edges[i].end] == 0) {
			vertex[g->edges[i].end] = 1;
			cnt++;
		}
	}
	g->vertextCnt = cnt;
}

/*================= Main=================*/
int main(void) {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 6, 3, 18);
	insert_edge(g, 6, 4, 25);
	vertex_cnt(g);
	kruskal(g);
	free(g);
	return 0;
}
