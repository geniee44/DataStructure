#include <stdio.h>
#include <stdlib.h>

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

void print_queue(LinkedQueueType* q) {	//리스트에 있는 값 전체 출력
	for (QueueNode* p = q->front; p != NULL; p = p->link) {
		printf("%3d |", p->data);
	}
	printf("\n");
}

int count_que(LinkedQueueType* q) {		//리스트에 몇개의 element가 들어있는지 for 반복문으로 count
	int count = 0;
	for (QueueNode* p = q->front; p != NULL; p = p->link) {
		count++;
	}
	return count;
}

void card_queue(LinkedQueueType* q, int num) {	//카드 섞는 메소드
	print_queue(q);			//현재 리스트 먼저 출력
	if (is_empty(q)) error("queue empty");	//입력받은 값이 0이라서 리스트가 비어있을 경우 출력
	while (1) {				//queue에 element가 하나 남아 break 되기 전까지 돌기
		if (count_que(q) == 1)	break;
		dequeue(q);			//가장 앞에 있는 카드 제거
		print_queue(q);
		if (count_que(q) == 1)	break;
		enqueue(q, dequeue(q));	//가장 앞에 있던 카드를 뒤로 보내기
		print_queue(q);
	}
	printf("Final element is %d", q->front->data);	//element가 하나 남아서 반복문을 빠져나왔을 경우 남아있는 element가 무엇인지 출력
}

int main(void) {
	LinkedQueueType q;
	init_queue(&q);			//리스트 초기화

	int num;
	printf("Input number of cards: ");
	scanf("%d", &num);		//카드 몇장인지 입력 받기
	
	for (int i = 1; i < num + 1; i++) {	//카드 갯수만큼 큐에 element 저장
		enqueue(&q, i);
	}
	card_queue(&q, num);	//카드 섞는 메소드 실행

	return 0;
}
