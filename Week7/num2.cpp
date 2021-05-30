#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 5 //배열 최대 크기 5로 지정

typedef int element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
}QueueType;

void error(const char* message) {
	fprintf(stderr, "%s\n", message);
}

void init_queue(QueueType* q) {	//queue 초기화
	q->front = 0;
	q->rear = 0;
}

bool is_full(QueueType* q) {	//rear를 증가시킨 값이 front와 같으면 full인 상태
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

bool is_empty(QueueType* q) {	//front와 rear이 같으면 empty
	return (q->front == q->rear);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))	error("queue is full");
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;	//rear를 증가시킴
		q->data[q->rear] = item;					//증가된 rear 위치에 새로운 값 삽입
	}
}

element dequeue(QueueType* q) {
	if (is_empty(q))	error("queue is empty");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;		//front를 증가시킴
	return q->data[q->front];						//증가된 front 위치에 있는 값 반환
}

void print_queue(QueueType* q) {
	printf("Queue(front:%d, rear: %d) = ", q->front, q->rear);	//front와 rear의 위치 출력
	if (!is_empty(q)) {				//큐에 데이터 있을 경우
		int i = q->front;			//현재 front부터 시작
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;	//front+1부터 출력
			printf("%3d |", q->data[i]);
			if (i == q->rear)	break;		//끝에 달해서 rear과 같다면 종료
		} while (i != q->front);
	}
	printf("\n");
}

int main(void) {
	QueueType q;
	init_queue(&q);		//배열 초기화
	char c;
	while (1) {
		printf("원하는 작업(E/e:enqueue, D/d:dequeue, P/p:output, 0:quit): ");
		scanf(" %c", &c);
		if (c=='0') {
			printf("현재 원소 갯수는: %2d\n", (q.rear - q.front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE); //front와 rear값 적절히 계산하여 원소 갯수 출력
			print_queue(&q); //지금까지 저장된 배열 출력
			break;
		}
		else if (c=='D' || c=='d') {	//dequeue하는 경우
			printf("%3d\n", dequeue(&q));
		}
		else if (c=='E' || c=='e') {	//enqueue하는 경우
			int num;
			printf("정수입력: ");		//새롭게 저장할 값 입력 받기
			scanf("%d", &num);
			enqueue(&q, num);
		}
		else if (c=='P' || c=='p') {	//print하는 경우
			print_queue(&q);
		}
		else
			printf("Wrong Input\n");	//잘못된 입력일 경우 출력하고 다시 반복문 돌기
	}
	return 0;
}
