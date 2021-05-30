#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct QueueNode {
	element data;
	struct QueueNode* link;
}QueueNode;

typedef struct { //front 노드와 rear 노드 저장
	QueueNode* front, * rear;
}LinkedQueueType;

void error(const char* message) { //에러 메시지 출력
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(LinkedQueueType* q) { //queue 노드 초기화
	q->front = NULL;
	q->rear = NULL;
}

bool is_full(LinkedQueueType* q) { //연결리스트는 full일 경우 없음
	return 0;
}

bool is_empty(LinkedQueueType* q) { //front가 NULL일 경우 empty
	return (q->front == NULL);
}

void enqueue(LinkedQueueType* q, element item) {
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode)); //새 노드 동적할당
	temp->data = item;	//데이터 저장
	temp->link = NULL;	//링크는 NULL
	if (is_empty(q)) {	//queue가 empty면 새로 추가된 node가 front이자 rear이 됨
		q->front = temp;
		q->rear = temp;
	}
	else {				//공백이 아니면 기존의 rear가 새 노드를 가리키게 함
		q->rear->link = temp;
		q->rear = temp;	//새 노드가 rear이 됨
	}
}

element dequeue(LinkedQueueType* q) {
	if (is_empty(q))	error("queue is empty");
	element data;
	QueueNode* temp = q->front;				//기존의 front가 가리키던 노드 위치를 저장
	data = temp->data;						//기존의 front가 가리키던 값을 미리 저장
	q->front = q->front->link;				//기존의 front가 가리키던 노드가 새롭게 front가 됨
	if (q->front == NULL)	q->rear = NULL;	//노드가 하나만 있었다면 queue 자체를 공백으로 만들어줌
	free(temp);								//기존 front 노드 메모리를 반환
	return data;							//dequeue된 데이터 반환
}

element peek(LinkedQueueType* q) { //노드를 삭제하지는 않고 값을 반환만 함
	if (is_empty(q))	return NULL;
	return q->rear->data;
}

void print_queue(LinkedQueueType* q) {	//리스트에 있는 값 전체 출력
	for (QueueNode* p = q->front; p != NULL; p = p->link) {
		printf("%5d", p->data);
	}
	printf("\n");
}

void fibo_queue(LinkedQueueType* q, int num) {
	LinkedQueueType t;	//계산을 위한 새로운 리스트 생성
	init_queue(&t);		//리스트 초기화
	enqueue(&t, 0);		//q와 동일한 값 저장
	enqueue(&t, 1);

	int first, second;
	for (int i = 3; i < num + 2; i++) { //새로 추가할 위치부터 반복문 돌기
		first = dequeue(&t);	//앞앞에 있는 숫자는 t에서 빼오기
		second = peek(&t);		//앞에 있는 숫자는 t에서 값만 가져오기
		enqueue(q, first + second);	//둘을 더해서 새롭게 q에 저장
		enqueue(&t, first + second);//t에도 저장, 앞앞에 있던 숫자는 제거되었음
	}
	print_queue(q);				//결과 출력
}

int main(void) {
	LinkedQueueType q;
	init_queue(&q);	//리스트 초기화
	enqueue(&q, 0);	//기본값 저장
	enqueue(&q, 1);

	int num;
	printf("Input a fibonacci location: ");
	scanf("%d", &num);

	fibo_queue(&q, num);	//피보나치 수열 계산

	return 0;
}
