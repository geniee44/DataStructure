#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func_recursive(char *s) { //문자열 역순 출력 재귀함수. 인자는 포인터로 받음
	if (*s == 0) //만약 문자열의 가장 끝에 도달했다면 아무것도 하지 않고 리턴
		return;
	else { //문자열의 끝이 아닐 경우
		func_recursive(s + 1); //주소에 1을 더해 재귀 호출
		printf("%c", *s); //가장 끝부터 문자 출력
	}
}

int main(void) {
	char X[100]; //문자열 선언
	printf("Input string\n");
	gets_s(X); //문자열 입력받기
	puts("변경 전:");
	puts(X); //입력받은 문자열 출력
	puts("변경 후:");
	func_recursive(X); //재귀함수 실행해서 문자열 역순으로 출력하기
	
	return 0;
}
