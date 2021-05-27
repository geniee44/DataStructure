#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100 //element 배열의 최대 크기 지정
typedef int element;

typedef struct StackType {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) { //stack 초기화하는 메소드
	s->top = -1;
}

void error(const char X[]) { //error문 출력하는 메소드
	fprintf(stderr, X);
}

bool is_full(StackType* s) { //stack이 모두 차 있는지 확인하는 메소드
	return (s->top == (MAX_STACK_SIZE- 1)); //top이 최대 길이보다 1 작으면 full인 상태
}

bool is_empty(StackType* s) {
	return (s->top == -1);
}

element pop(StackType* s) { //stack에 저장된 값 나오게 하는 메소드
	if (is_empty(s)) { //stack이 비어있는 경우 에러문 출력하고 프로그램 종료
		error("Stack empty");
		exit(1);
	}
	else return s->data[(s->top)--]; //top이 가르키고 있는 값 변환하고 top 1 감소
}

void push(StackType* s, element item) { //stack에 새로운 값 저장하는 메소드
	if (is_full(s)) { //stack이 다 차 있는 경우 에러문 출력하고 프로그램 종료
		error("Overflow");
		return;
	}
	else s->data[++(s->top)] = item; //top 1 증가시켜 새로운 값 저장
}

void makeBinary(StackType* s, int n) { //이진수로 변환하는 메소드
	while (n>0) { //n이 0보다 클 때까지 반복
		push(s, n % 2); //2로 나눈 나머지 값을 stack에 저장
		n /= 2; //n을 2로 나누어 다시 반복
	}
	printf("이진수 표현:");
	while (1) {
		if (s->top == -1) { //stack이 empty한 경우 pop 그만하기
			printf("\n\n"); break;
		}
		printf("%d", pop(s)); //stack에 있는 값 pop시켜서 print하기
	}
}

int main(void) {
	int n;
	while (1) {
		printf("십진수 입력 (종료: 0 이하 입력)\n");
		scanf("%d", &n); //변환할 값 입력 받기
		if (n <= 0) break; //0 이하의 값이면 반복문 종료
		StackType s; //stacktype 선언
		init_stack(&s); //stack 초기화
		makeBinary(&s, n); //2진수로 변환
	}
	return 0;
}
