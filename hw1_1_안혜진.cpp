#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void myName(void) { //�̸� ����ϴ� �޼ҵ�
	printf("===================\n");
	printf("�а�: ���̹�����\n");
	printf("�й�: 1971077\n");
	printf("����: ������\n");
	printf("===================\n");
}

//���׽� �׸��� �����Ǵ� ���
typedef struct ListNode {
	int coef; //���
	int expon; //����
	struct ListNode* link; //���� ���Ḯ��Ʈ ���
} ListNode;

//���Ḯ��Ʈ ���
typedef struct ListType { //���׽� ������ �����ϴ� ���
	int size; //���׽��� �׼�
	ListNode* head; //���׽� ó�� ��� �ּ�
	ListNode* tail; //���׽� ������ ��� �ּ�
} ListType;

void error(const char* message) { //���� �޽��� ����ϴ� �޼ҵ�
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListType* create(void) { //���׽� ������ �����ϴ� ��� ����
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->head = NULL;
	plist->tail = NULL;
	plist->size = 0;
	return plist;
}

void insert_last(ListType* plist, int coef, int expon) { //����Ʈ �������� �� �߰�
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode)); //�߰��� ��� ����
	if (temp == NULL) error("memory allocation error\n"); //�޸��Ҵ� ���н� ���� �޽��� ���
	temp->coef = coef; //�ӽó���� ���, ���� ����
	temp->expon = expon;
	temp->link = NULL; //�������� �߰��ϱ� ������ ��ũ�� NULL ����
	if (plist->tail == NULL) //�� ����Ʈ�� ���
		plist->head=plist->tail= temp; //���ο� ��尡 ������ ��尡 ��
	else { //������ ��� ���� ���
		plist->tail->link = temp; //���׽��� ����Ʈ�� �� �������� �� ��� �߰�
		plist->tail = temp; //���׽��� ������ ���� ������ �� ��� �ּҷ� ����
	}
	plist->size++; //���׽��� ���� ����
}

void poly_print(ListType* plist) { //���׽� ���
	ListNode* node = plist->head; //���׽��� ó�� ���Ҹ� ����Ű�� �ּ�
	printf("\n<Polynomial>\n");
	for (int i = 0; i < plist->size - 1; i++) { //����Ʈ�� ó������ �������� ������ ���
		printf("%dx^%d + ", node->coef, node->expon);
		node = node->link; //���� �� ĭ�� �̵�
	}
	printf("%dx^%d \n", node->coef, node->expon); //������ �� ���
}

int poly_cal(ListType* plist, int x) { //�Է¹��� ������ ����ϴ� �޼ҵ�
	ListNode* node = plist->head; //���׽��� ó�� ���Ҹ� ����Ű�� �ּ�
	int sum = 0; //����� ���� ��
	while (node) {
		sum += (node->coef) * pow(x, (node->expon)); //x ���� ������ŭ �����Ͽ� ��� ���ؼ� sum�� ���ϱ�
		node = node->link; //���� �� ĭ�� �̵�
	}
	return (int)sum;
}

int main(void) {
	myName();
	ListType* list;
	list = create(); //���׽� ����
	printf("Input coef and exponent of polynomial(��������:exponent�� 0���� �Է�)\n");
	int coef, exponent, x;
	bool tf = true; //�ݺ��� ���������� ���� ����

	while(tf){
		scanf("%d %d", &coef, &exponent); //���, ���� �Է� �ޱ�
		insert_last(list, coef, exponent); //�Է� ���� ������ ����Ʈ�� �߰�
		if (exponent == 0) tf=false; //������ 0�� ��� �ݺ��� ������
	}
	poly_print(list); //�Է¹��� ���׽� ���

	printf("Input the value x: ");
	scanf("%d", &x); //x�� �Է� �ޱ�
	int result = poly_cal(list, x); //��� ��� �����Ͽ� ���
	printf("Result of polynomial with x: %d", result);

}