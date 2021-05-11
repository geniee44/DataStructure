#include <stdio.h>

double iterative(int n) { //반복함수
	double result = 0.0; //더해서 리턴할 변수 선언
	for (double i = 1; i <= n; i++) { //for 반복문으로 1부터 n까지 반복
		result += (double)1 / i; //리턴할 변수에 1/n씩 더하기
	}
	return result; //다 더한 값 리턴
}

double recursive(int n) { //재귀함수
	if (n == 1) return 1.0; //계속 재귀로 반복되다가 1 됐을 때 1리턴
	else {
		return (double)1 / n + recursive(n - 1); //1이 아니면 n에 1씩 감소해서 재귀로 더하기
	}
}
int main(void) {
	while (1) { //break 나올 때까지 반복하기
		int n; //입력받을 정수 선언
		printf("양의 정수 입력:");
		scanf("%d", &n); //scanf로 정수 입력 받기
		if (n == 0) break; //입력 받은 정수가 0일 경우에는 반복 종료

		printf("Result from iterative: %.2f\n", iterative(n)); //반복함수 실행해서 출력
		printf("Result from recursive: %.2f\n", recursive(n)); //재귀함수 실행해서 출력
	}
	return 0;
}
