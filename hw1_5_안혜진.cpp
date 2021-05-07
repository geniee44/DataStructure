#include <stdio.h>
#include <stdlib.h>

void myName(void) { //�̸� ����ϴ� �޼ҵ�
	printf("===================\n");
	printf("�а�: ���̹�����\n");
	printf("�й�: 1971077\n");
	printf("����: ������\n");
	printf("===================\n");
}

typedef int element;
typedef struct QueueNode {
	element data;
	struct QueueNode* link;
}QueueNode;

typedef struct { //front ���� rear ��� ����
	QueueNode* front, * rear;
}LinkedQueueType;

void error(const char* message) { //���� �޽��� ���
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(LinkedQueueType* q) { //queue ��� �ʱ�ȭ
	q->front = NULL;
	q->rear = NULL;
}

bool is_full(LinkedQueueType* q) { //���Ḯ��Ʈ�� full�� ��� ����
	return 0;
}

bool is_empty(LinkedQueueType* q) { //front�� NULL�� ��� empty
	return (q->front == NULL);
}

void enqueue(LinkedQueueType* q, element item) {
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode)); //�� ��� �����Ҵ�
	temp->data = item;	//������ ����
	temp->link = NULL;	//��ũ�� NULL
	if (is_empty(q)) {	//queue�� empty�� ���� �߰��� node�� front���� rear�� ��
		q->front = temp;
		q->rear = temp;
	}
	else {				//������ �ƴϸ� ������ rear�� �� ��带 ����Ű�� ��
		q->rear->link = temp;
		q->rear = temp;	//�� ��尡 rear�� ��
	}
}

element dequeue(LinkedQueueType* q) {
	if (is_empty(q))	error("queue is empty");
	element data;
	QueueNode* temp = q->front;				//������ front�� ����Ű�� ��� ��ġ�� ����
	data = temp->data;						//������ front�� ����Ű�� ���� �̸� ����
	q->front = q->front->link;				//������ front�� ����Ű�� ��尡 ���Ӱ� front�� ��
	if (q->front == NULL)	q->rear = NULL;	//��尡 �ϳ��� �־��ٸ� queue ��ü�� �������� �������
	free(temp);								//���� front ��� �޸𸮸� ��ȯ
	return data;							//dequeue�� ������ ��ȯ
}

void print_queue(LinkedQueueType* q) {	//����Ʈ�� �ִ� �� ��ü ���
	for (QueueNode* p = q->front; p != NULL; p = p->link) {
		printf("%3d |", p->data);
	}
	printf("\n");
}

int count_que(LinkedQueueType* q) {		//����Ʈ�� ��� element�� ����ִ��� for �ݺ������� count
	int count = 0;
	for (QueueNode* p = q->front; p != NULL; p = p->link) {
		count++;
	}
	return count;
}

void card_queue(LinkedQueueType* q, int num) {	//ī�� ���� �޼ҵ�
	print_queue(q);			//���� ����Ʈ ���� ���
	if (is_empty(q)) error("queue empty");	//�Է¹��� ���� 0�̶� ����Ʈ�� ������� ��� ���
	while (1) {				//queue�� element�� �ϳ� ���� break �Ǳ� ������ ����
		if (count_que(q) == 1)	break;
		dequeue(q);			//���� �տ� �ִ� ī�� ����
		print_queue(q);
		if (count_que(q) == 1)	break;
		enqueue(q, dequeue(q));	//���� �տ� �ִ� ī�带 �ڷ� ������
		print_queue(q);
	}
	printf("Final element is %d", q->front->data);	//element�� �ϳ� ���Ƽ� �ݺ����� ���������� ��� �����ִ� element�� �������� ���
}

int main(void) {
	myName();				//�̸� ���
	LinkedQueueType q;
	init_queue(&q);			//����Ʈ �ʱ�ȭ

	int num;
	printf("Input number of cards: ");
	scanf("%d", &num);		//ī�� �������� �Է� �ޱ�
	
	for (int i = 1; i < num + 1; i++) {	//ī�� ������ŭ ť�� element ����
		enqueue(&q, i);
	}
	card_queue(&q, num);	//ī�� ���� �޼ҵ� ����

	return 0;
}