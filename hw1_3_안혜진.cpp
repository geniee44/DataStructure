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
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode; //node ����ü �����

ListNode* insert(ListNode* head, element val) { //������������ ��� �߰��ϴ� �޼ҵ�
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = val; //��忡 ������ ����
	if (head == NULL) { //��尡 �ƹ��͵� ���� ���
		p->link = NULL;
		head = p;
		return head; //ù��°�� ��� �߰��ϵ��� ��
	}
	else { //����� ������� ���� ���
		ListNode* check, * find = NULL; //���Ӱ� �� ��带 �����Ͽ� ����Ʈ ��ü ����
		for (check = head; check != NULL; check = check->link)
			if (check->data < p->data)
				find = check; //���� ���� �����Ͱ� ���ο� �����ͺ��� �۴ٸ� find�� ��� check�� �ٲ���

		if (find == NULL) { //���ο� �����Ͱ� ����Ʈ �� ���� ���� ���
			p->link = head;
			head = p; //ù��°�� ��� �߰�
		}
		else { //����Ʈ �߰��� �����ؾ��ϴ� ���
			p->link = find->link; //ã�Ƴ��� find ����� �ڿ� ���ο� ��� ����
			find->link = p;
		}
		return head;
	}
}

void print_list(ListNode* head) { //���Ḯ��Ʈ ����ϴ� �Լ�
	ListNode* p = NULL;
	for (p = head; p->link != NULL; p = p->link) //head���� ��ũ�� ����� ��� �� �������� �����ϰ� ��� 
		printf("  %d  ->", p->data);
	printf("  %d  ->  NULL", p->data); //����Ʈ�� ������ ������ ���
}

int main(void) {
	ListNode* head = NULL; //���ο� ����Ʈ ����
	int num;
	myName();

	while (1) {
		printf("\nInput data to insert to linkedList <0 to quit>\n");
		scanf(" %d", &num); //scanf�� ���ο� ������ �Է� �ޱ�
		if (num == 0)
			break; //�Է°��� 0�� ��� break�ؼ� �Է� �ޱ� �ߴ�
		else {
			head = insert(head, num); //�Է°��� 0�� �ƴϸ� insert �Լ� �̿��ؼ� ����Ʈ �߰�
			print_list(head); //���ݱ��� ������ ����Ʈ ���
		}
	}
	print_list(head); //���� ����Ʈ ���
	printf("\nProgram finished.");
}