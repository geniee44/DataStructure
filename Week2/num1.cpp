#include <stdio.h>

void bin(int n) {
	int binary[20] = { 0, }; //이진수 저장할 배열 선언
	int place = 0;
	while (1)
	{
		binary[place] = n%2; //2로 나누었을 때 나머지를 배열 중 place 위치에 저장
		n = n/2; //n을 2로 나눈 몫으로 변경
		place++; //나머지 저장할 위치 바꾸기

		if (n==0) //n이 0이 되면 더 이상 나눌 필요 없기 때문에 반복문 종료
			break;
	}
	for (int i = place - 1; i >= 0; i--)
	{
		printf("%d", binary[i]); //for 반복문 이용해서 배열 역수로 출력하기
	}

}

int main(void) {
	int n; //입력 받을 정수 선언
	printf("양의 정수 입력: ");
	scanf("%d", &n); //scanf 이용해서 정수 입력 받기
	printf("십진수 %d의 이진표현: ", n);
	bin(n); //이진수로 변환하는 bin 함수 실행

	return 0;
}
