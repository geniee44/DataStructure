#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100 //element 배열의 최대 길이 정하기
typedef char element;

typedef struct StackType { //stack 구조체
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) { //stack 초기화
	s->top = -1;
}

void error(const char X[]) { //error문 출력하는 함수
	fprintf(stderr, X);
}

bool is_full(StackType* s) { //stack이 다 차 있는지 확인하는 함수
	return (s->top == (MAX_STACK_SIZE - 1)); //top이 최대 길이보다 1 작으면 다 차 있는 것
}

bool is_empty(StackType* s) { //stack이 비어있는지 확인하는 함수
	return (s->top == -1); //top이 -1이면 비어있는 것
}

element pop(StackType* s) { //stack의 가장 위에 있는 값을 빼오는 함수
	if (is_empty(s)) { //stack이 비어있을 경우 error문 출력하고 시스템 종료
		error("Stack empty");
		exit(1);
	}
	else return s->data[(s->top)--]; //값 빼오고 top 1 감소
}

element peek(StackType* s) { //stack의 가장 위에 있는 값을 확인하는 함수
	if (is_empty(s)) { //stack이 비어있을 경우 error문 출력하고 시스템 종료
		error("Stack empty");
		exit(1);
	}
	else return s->data[(s->top)];
}

void push(StackType* s, element item) { //stack에 새로운 element 추가하는 함수
	if (is_full(s)) { //stack이 다 차있으면 error문 출력하고 시스템 종료
		error("Overflow");
		return;
	}
	else s->data[++(s->top)] = item; //top 증가해서 새로운 값 저장
}

void simplePrint(char* X) { //간단하게 프린트해주는 함수
	StackType* s = (StackType*)malloc(sizeof(StackType)); //stack 구조체 동적 할당
	init_stack(s); //stack 초기화
	char ch, c;
	int count; //글자 몇개있는지 세는 변수
	for (int i = 0; i < strlen(X); i++) { //입력 받은 문자열만큼 반복
		ch = X[i];
		if (is_empty(s)||peek(s)==ch) push(s, ch); //stack이 비어있거나 제일 위에 있는 값이 현재 문자와 같을 때 push
		else { //위의 두 경우에 모두 해당되지 않으면
			count = 0;
			c = peek(s);
			while (!is_empty(s)) { //stack이 빌 때까지 pop해서 문자 몇개 들었나 카운트
				pop(s);
				count++;
			}
			printf("%d%c", count, c); //센만큼 프린트
			push(s, ch); //원래 현재의 문자는 push
		}
	}
	//for문 다 돌아서 stack에 마지막 글자들 남아있는 경우
	c = peek(s);
	count = 0;
	while (!is_empty(s)) { //위와 같은 방법으로 글자 세기
		pop(s);
		count++;
	}
	printf("%d%c", count, c); //마지막 stack에 몇개 들었나 프린트
	free(s); //동적할당한 s free해주기
}

int main(void) {
	while (1) { //원하는만큼 반복
		char str[100];
		printf("반복되는 알파벳으로 구성된 문자열 입력 (종료시 0 입력)\n");
		gets_s(str); //문자열 입력 받기
		if ((strlen(str)==1)&&(str[0] - '0' == 0)) break; //0 입력 받았을 경우 종료
		simplePrint(str); //simplePrint 이용해서 간단하게 프린트하기
		printf("\n");
	}
	return 0;
}
