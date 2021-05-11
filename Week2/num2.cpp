#include <stdio.h>

void iterative(int n) {
	for (int i = n; i >= 0; i--) {
		printf("%d ", i); //for 반복문 이용해서 1씩 빼면서 0까지 출력
	}
	printf("\n");
}

void recursive(int n) {
	printf("%d ", n); //우선 해당 숫자 출력하기
	if (n != 0) {
		recursive(n - 1); //0일 때 제외하고 1 빼서 함수 실행해서 재귀함수 만들기
	}
}

int main(void) {
	int n; //입력 받을 정수 선언
	printf("양의 정수 입력:");
	scanf("%d", &n); //scanf로 정수 입력 받기

	printf("반복함수호출:");
	iterative(n); //반복함수 실행

	printf("재귀함수호출:");
	recursive(n); //재귀함수 실행
	printf("\n");

	return 0;
}
