#include <stdio.h>
#define ROWS 4
#define COLS 3

void matrixInput(int (*mat)[COLS]) { //행렬값 입력받는 메소드
	for (int i = 0; i < ROWS; i++) { //for문 이용해서 행, 열 크기만큼 반복
		for (int j = 0; j < COLS; j++) {
			scanf("%d", &mat[i][j]); //scanf로 행렬에 값 저장
		}
	}
}

void matrixPrint(int (*mat)[COLS]) { //행렬 출력하는 메소드
	for (int i = 0; i < ROWS; i++) { //for문 이용해서 행, 열 크기만큼 반복
		for (int j = 0; j < COLS; j++) {
			printf("%2d", *(*(mat+i)+j)); //주소에 저장된 값 출력
		}
		putchar('\n'); //행 하나 끝날 때마다 엔터
	}
}

void matrixAdd(int (*a)[COLS], int (*b)[COLS], int (*c)[COLS]) { //행렬 더하는 메소드
	for (int i = 0; i < ROWS; i++) { //for문 이용해서 행, 열 크기만큼 반복
		for (int j = 0; j < COLS; j++) {
			c[i][j] = *(*(a+i)+j)+ *(*(b+i)+j); //새로운 행렬 c에 a와 b의 행렬값 더해서 넣기
		}
	}
}

int main(void) {
	int A[ROWS][COLS], B[ROWS][COLS], C[ROWS][COLS];
	printf("Input values for %dX%d matrix A\n", ROWS, COLS);
	matrixInput(A); //행렬 A 입력 받기
	printf("Input values for %dX%d matrix B\n", ROWS, COLS);
	matrixInput(B); //행렬 B 입력 받기
	puts("<A>");
	matrixPrint(A); //행렬 A 출력
	puts("<B>");
	matrixPrint(B); //행렬 B 출력
	puts("<A+B>");
	matrixAdd(A, B, C);
	matrixPrint(C); //A와 B 더한 행렬 C 출력

	return 0;
}
