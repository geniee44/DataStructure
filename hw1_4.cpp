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

void push(StackType* s, element item) { //stack에 새로운 element 추가하는 함수
	if (is_full(s)) { //stack이 다 차있으면 error문 출력하고 시스템 종료
		error("Overflow");
		return;
	}
	else s->data[++(s->top)] = item; //top 증가해서 새로운 값 저장
}

void check_array(char* X) {//대칭인지 배열로 확인하는 메소드
	int l = strlen(X); //문자열의 길이를 저장
	bool tf = true;
	for (int i = 0; i < (l / 2); i++) { //배열 중간을 대칭으로 양쪽의 값이 같은지 확인
		if (X[i] != X[l - i - 1])
			tf = false; //값이 한 번이라도 다를 경우 tf를 false로 변경
	}
	if (tf) //tf 값에 따라 대칭인지 비대칭인지 출력
		printf("대칭(배열)\n");
	else
		printf("비대칭(배열)\n");
}

void check_stack(char* X) { //stack으로 대칭인지 확인하는 메소드
	StackType* s = (StackType*)malloc(sizeof(StackType)); //s 동적할당
	init_stack(s); //stack 초기화
	bool tf = true;
	int l = strlen(X); //문자열 길이 저장
	if (l % 2 == 0) { //문자열의 길이가 짝수인 경우
		for (int i = 0; i < l / 2; i++) {
			push(s, X[i]); //문자열의 반만큼 스택에 저장
		}
		for (int i = l / 2; i < l; i++) { //나머지 문자열의 반만큼 스택에 저장했던 값 빼와서 서로 비교
			if (pop(s) != X[i]) tf = false; //다를 경우 tf를 false로 변경
		}
	}
	else { //문자열의 길이가 홀수인 경우
		for (int i = 0; i < int(l / 2); i++) { //문자열의 반만큼 스택에 저장, 가운데값은 저장 안함
			push(s, X[i]);
		}
		for (int i = l / 2 + 1; i < l; i++) { //짝수인 경우와 동일하게 진행
			if (pop(s) != X[i]) tf = false;
		}
	}
	if (tf) //tf 값에 따라 대칭인지 비대칭인지 출력
		printf("대칭(스택)\n");
	else
		printf("비대칭(스택)\n");
	free(s); //동적할당했던 s 풀어주기
}

int main(void) {
	while (1) { //원하는만큼 반복
		char str[100];
		printf("\n반복되는 알파벳으로 구성된 문자열 입력 (종료시 0 입력)\n");
		gets_s(str); //문자열 입력 받기
		if ((strlen(str) == 1) && (str[0] - '0' == 0)) break; //0 입력 받았을 경우 종료
		
		check_array(str); //대칭인지 배열로 확인
		check_stack(str); //대칭인지 스택으로 확인
	}
	return 0;
}
