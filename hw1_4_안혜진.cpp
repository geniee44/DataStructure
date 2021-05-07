#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100 //element �迭�� �ִ� ���� ���ϱ�
typedef char element;

void myName(void) { //�̸� ����ϴ� �޼ҵ�
	printf("===================\n");
	printf("�а�: ���̹�����\n");
	printf("�й�: 1971077\n");
	printf("����: ������\n");
	printf("===================\n");
}

typedef struct StackType { //stack ����ü
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) { //stack �ʱ�ȭ
	s->top = -1;
}

void error(const char X[]) { //error�� ����ϴ� �Լ�
	fprintf(stderr, X);
}

bool is_full(StackType* s) { //stack�� �� �� �ִ��� Ȯ���ϴ� �Լ�
	return (s->top == (MAX_STACK_SIZE - 1)); //top�� �ִ� ���̺��� 1 ������ �� �� �ִ� ��
}

bool is_empty(StackType* s) { //stack�� ����ִ��� Ȯ���ϴ� �Լ�
	return (s->top == -1); //top�� -1�̸� ����ִ� ��
}

element pop(StackType* s) { //stack�� ���� ���� �ִ� ���� ������ �Լ�
	if (is_empty(s)) { //stack�� ������� ��� error�� ����ϰ� �ý��� ����
		error("Stack empty");
		exit(1);
	}
	else return s->data[(s->top)--]; //�� ������ top 1 ����
}

void push(StackType* s, element item) { //stack�� ���ο� element �߰��ϴ� �Լ�
	if (is_full(s)) { //stack�� �� �������� error�� ����ϰ� �ý��� ����
		error("Overflow");
		return;
	}
	else s->data[++(s->top)] = item; //top �����ؼ� ���ο� �� ����
}

void check_array(char* X) {//��Ī���� �迭�� Ȯ���ϴ� �޼ҵ�
	int l = strlen(X); //���ڿ��� ���̸� ����
	bool tf = true;
	for (int i = 0; i < (l / 2); i++) { //�迭 �߰��� ��Ī���� ������ ���� ������ Ȯ��
		if (X[i] != X[l - i - 1])
			tf = false; //���� �� ���̶� �ٸ� ��� tf�� false�� ����
	}
	if (tf) //tf ���� ���� ��Ī���� ���Ī���� ���
		printf("��Ī(�迭)\n");
	else
		printf("���Ī(�迭)\n");
}

void check_stack(char* X) { //stack���� ��Ī���� Ȯ���ϴ� �޼ҵ�
	StackType* s = (StackType*)malloc(sizeof(StackType)); //s �����Ҵ�
	init_stack(s); //stack �ʱ�ȭ
	bool tf = true;
	int l = strlen(X); //���ڿ� ���� ����
	if (l % 2 == 0) { //���ڿ��� ���̰� ¦���� ���
		for (int i = 0; i < l / 2; i++) {
			push(s, X[i]); //���ڿ��� �ݸ�ŭ ���ÿ� ����
		}
		for (int i = l / 2; i < l; i++) { //������ ���ڿ��� �ݸ�ŭ ���ÿ� �����ߴ� �� ���ͼ� ���� ��
			if (pop(s) != X[i]) tf = false; //�ٸ� ��� tf�� false�� ����
		}
	}
	else { //���ڿ��� ���̰� Ȧ���� ���
		for (int i = 0; i < int(l / 2); i++) { //���ڿ��� �ݸ�ŭ ���ÿ� ����, ������� ���� ����
			push(s, X[i]);
		}
		for (int i = l / 2 + 1; i < l; i++) { //¦���� ���� �����ϰ� ����
			if (pop(s) != X[i]) tf = false;
		}
	}
	if (tf) //tf ���� ���� ��Ī���� ���Ī���� ���
		printf("��Ī(����)\n");
	else
		printf("���Ī(����)\n");
	free(s); //�����Ҵ��ߴ� s Ǯ���ֱ�
}

int main(void) {
	myName();
	while (1) { //���ϴ¸�ŭ �ݺ�
		char str[100];
		printf("\n�ݺ��Ǵ� ���ĺ����� ������ ���ڿ� �Է� (����� 0 �Է�)\n");
		gets_s(str); //���ڿ� �Է� �ޱ�
		if ((strlen(str) == 1) && (str[0] - '0' == 0)) break; //0 �Է� �޾��� ��� ����
		
		check_array(str); //��Ī���� �迭�� Ȯ��
		check_stack(str); //��Ī���� �������� Ȯ��
	}
	return 0;
}