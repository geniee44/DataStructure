#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

//여기부터 stack code
#define MAX_STACK_SIZE 100
typedef int element;

typedef struct StackNode {
	element data[MAX_STACK_SIZE];	//배열의 요소 element 타입
	int top;						//top 값을 구조체에 포함
}StackType;

void init_stack(StackType* s) {		//stack 초기화
	s->top = -1;
}

void error(const char X[]) {		//오류 메시지 출력
	fprintf(stderr, X);
}

bool is_full(StackType* s) {		//top이 최대일 경우 true 반환
	return (s->top == (MAX_STACK_SIZE - 1));
}

bool is_empty(StackType* s) {		//top이 최소인 -1일 경우 true 반환
	return (s->top == -1);
}

element pop(StackType* s) {
	if (is_empty(s)) {
		error("Stack empty");
		exit(1);
	}								//top이 가리키는 원소값 반환 후 top -1
	else return s->data[(s->top)--];
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		error("Overflow");
		return;
	}								//top에 +1하고 해당 위치에 값 저장
	else s->data[++(s->top)] = item;
}
//여기까지 stack code

typedef struct GraphType {	//그래프 기본 구조
	int n;	//vertex의 수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

void init(GraphType* g) {	//그래프 초기화
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;	//그래프의 모든 원소 0으로 초기화
}

void insert_vertex(GraphType* g, int v) {	//vertex insertion 연산
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과\n");
		return;
	}
	else g->n++;	//vertex 증가
}

void insert_edge(GraphType* g, int start, int end) {	//edge insertion 연산
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류\n");
		return;
	}
	g->adj_mat[start][end] = 1;	//vertex 중 한 쪽만 1로 set
}

void print_adf_mat(GraphType* g) {	//그래프 출력
	int r, c;
	printf("<Graph Matrix>\n");
	for (r = 0; r < g->n; r++) {
		for (c = 0; c < g->n; c++)
			printf("%2d", g->adj_mat[r][c]);
		printf("\n");
	}
}
//전역변수로 visited 선언(자동 초기화)
int visited[MAX_VERTICES];

void dfs_mat_recursive(GraphType* g, int v) {
	int w;
	visited[v] = true;						//dfs로 시작된 vertex는 방문한 것으로 표시
	printf("vertex%d  ", v);				//방문한 vertex 출력
	for (w = 0; w < g->n; w++)				//해당 vertex의 row 값을 하나씩 검사
		if (g->adj_mat[v][w] && !visited[w])//특정 vertex 값이 1인데 아직 방문 안했을 경우
			dfs_mat_recursive(g, w);		//그 vertex(w)로 이동해서 dfs 재귀실행
}

void dfs_mat_stack(GraphType* g, int v) {
	for (int j = 0; j < MAX_VERTICES; j++)	//전역변수인 visited 다시 초기화
		visited[j] = 0;
	StackType s;							//스택 생성
	int w;
	init_stack(&s);							//스택 초기화
	push(&s, v);							//스택에 v push
	while (!is_empty(&s)) {					//스택이 비지 않을 동안 실행
		v = pop(&s);						//스택에 있던 값 pop
		if (!visited[v]) {					//v가 방문되지 않았으면
			visited[v] = true;				//v를 방문했다고 표시
			printf("vertex%d  ", v);		//해당값 출력
			for (w = 0; w < g->n; w++)		//v에 인접한 정점으로 넘어가
				if (g->adj_mat[v][w] && !visited[w])	//u가 아직 방문 안됐으면
					push(&s, w);			//스택에 u push
		}
	}
	for (int j = 0; j < MAX_VERTICES; j++)	//다음 실행 위해서 visited 0으로 초기화
		visited[j] = 0;
}

int main(void) {
	//첫번째 그래프 실행
	GraphType* g1;
	g1 = (GraphType*)malloc(sizeof(GraphType));
	init(g1);
	for (int i = 0; i < 5; i++)
		insert_vertex(g1, i);
	insert_edge(g1, 0, 1);
	insert_edge(g1, 0, 2);
	insert_edge(g1, 0, 3);
	insert_edge(g1, 1, 0);
	insert_edge(g1, 1, 4);
	insert_edge(g1, 2, 0);
	insert_edge(g1, 2, 4);
	insert_edge(g1, 3, 0);
	insert_edge(g1, 4, 1);
	insert_edge(g1, 4, 2);

	print_adf_mat(g1);
	printf("<Depth First Search-recursive>\n");
	dfs_mat_recursive(g1, 0);
	printf("\n");
	printf("<Depth First Search-stack>\n");
	dfs_mat_stack(g1, 0);
	printf("\n\n");
	free(g1);

	//두번째 그래프 실행
	GraphType* g2;
	g2 = (GraphType*)malloc(sizeof(GraphType));
	init(g2);
	for (int i = 0; i < 6; i++)
		insert_vertex(g2, i);
	insert_edge(g2, 0, 2);
	insert_edge(g2, 0, 4);
	insert_edge(g2, 1, 5);
	insert_edge(g2, 2, 1);
	insert_edge(g2, 2, 3);
	insert_edge(g2, 4, 5);

	print_adf_mat(g2);
	printf("<Depth First Search-recursive>\n");
	dfs_mat_recursive(g2, 0);
	printf("\n");
	printf("<Depth First Search-stack>\n");
	dfs_mat_stack(g2, 0);
	printf("\n");
	free(g2);
	return 0;
}
