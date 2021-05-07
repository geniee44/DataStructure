#include <stdio.h>
#include <malloc.h>

void myName(void) { //�̸� ����ϴ� �޼ҵ�
	printf("===================\n");
	printf("�а�: ���̹�����\n");
	printf("�й�: 1971077\n");
	printf("����: ������\n");
	printf("===================\n");
}

typedef int element;
typedef struct ListNode { //���߿������� ��� ����
	element data;
	struct ListNode* llink; //���� ��ũ
	struct ListNode* rlink; //������ ��ũ
}ListNode;

void init(ListNode* phead) { //���߿������Ḯ��Ʈ �ʱ�ȭ
	phead->rlink = phead;
	phead->llink = phead;
}

ListNode* insert_last(ListNode* head, element val) { //���ο� ��带 ����Ʈ�� �������� �����ϴ� �Լ�
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //���ο� ��� ����
	p->data = val; //������ ����
	if (head == NULL) { //����Ʈ�� ����ִ� ���
		head = p;
		p->rlink = head;
		p->llink = head;
	}
	else { //����Ʈ�� ������� ���� ���
		p->llink = head->llink;
		p->rlink = head;
		p->llink->rlink = p;
		p->rlink->llink = p;
	}
	return head;
}


void print_list(ListNode* head) { //���Ḯ��Ʈ ����ϴ� �Լ�
	ListNode* p = head->rlink; //����Ʈ�� ó�� ���Ҹ� ����Ű�� �ּ�
	do { //����Ʈ�� ������ ���� �����ϰ� ���
		printf(" %d <->", p->data);
		p = p->rlink; //��� �� ĭ�� ���������� �̵�
	} while (p != head->llink); //���������� ���� ���� �ݺ��� ����
	printf(" %d \n", p->data); //����Ʈ�� ������ ���� ���
}

void reverse_print_list(ListNode* head) { //���Ḯ��Ʈ �ݴ�� ����ϴ� �Լ�
	ListNode* p = head->llink; //����Ʈ�� ������ ���Ҹ� ����Ű�� �ּ�
	do { //����Ʈ�� ù��° ���� �����ϰ� ���
		printf(" %d <->", p->data);
		p = p->llink; //��� �� ĭ�� �������� �̵�
	} while (p != head->rlink);
	printf(" %d \n", p->data); //����Ʈ�� ù��° ���� ���
}

int main(void) {
	myName();

	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	init(head); //head ��� �ʱ�ȭ
	int num;
	bool tf = true; //�ݺ��� ���������� ���� ����
	printf("Input an integer to add <0 to quit>\n");

	while(tf){
		scanf("%d", &num);
		if (num == 0) tf=false; //�Է¹��� ���� 0�� ��� ����
		else head = insert_last(head, num); //�Է¹��� �� ����Ʈ�� �������� ����
	}
	print_list(head); //����Ʈ ���
	printf("Print the list in reverse order\n");
	reverse_print_list(head); //����Ʈ ���� ���
}