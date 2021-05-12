#include <stdio.h>
#define MAX_L 100 //배열 최대 길이 100으로 고정

void elementPrint(int* a, int l) { //배열 원소 출력하는 메소드
	printf("Array:");
	for (int i = 0; i < l; i++) { //for문 이용해서 배열 전체 원소 출력
		printf("  %d", *(a + i));
	}
	printf("\n\n"); //출력 끝나면 줄 바꿈
}

void elementGeneration(int *a, int l) { //배열 생성하는 메소드
	for (int i = 0; i < l; i++) { //인자로 받은 길이 l만큼 반복하여 배열 생성
		scanf("%d", &a[i]);
	}
}

int elementInsertion(int *a, int l) { //배열에 원소 삽입하는 메소드
	int location, value;
	puts("Input location and value to insert");
	scanf("%d %d", &location, &value); //scanf로 삽입할 원소의 위치와 값 입력 받기
	if (location > (l + 1)) { //입력받은 위치가 배열의 길이보다 클 경우
		printf("Choose between 1 and %d\n", (l + 1));
		return l; //길이 변하지 않았기 때문에 그대로 l return하기
	}
	else { //입력받은 location이 정상인 경우
		for (int i = (l - 1); i >= (location - 1); i--) { //배열의 가장 끝부터 location까지의 원소들 오른쪽으로 한 칸씩 이동
			a[i + 1] = a[i];
		}
		a[location - 1] = value; //지정한 위치에 원소 삽입
		elementPrint(a, (l+1)); //달라진 배열 출력
		return (l + 1); //원소 하나 삽입했기 때문에 l에 1 더해서 리턴
	}
}

int elementDeletion(int *a, int l) { //배열의 원소 제거하는 메소드
	int location;
	puts("Input location to delete");
	scanf("%d", &location); //scanf로 제거할 원소 위치 입력 받기
	if (location > l) { //입력받은 위치가 배열의 길이보다 클 경우
		printf("No element in location %d\n", location);
		return l; //배열 길이 달라지지 않았기 때문에 그대로 l 리턴
	}
	else { //입력받은 위치가 정상인 경우
		for (int i = location; i < l; i++) {
			a[i - 1] = a[i]; //제거할 원소의 오른쪽 원소부터 차례대로 왼쪽으로 한 칸씩 이동
		}
		a[l] = '\0'; //원래 배열의 마지막 원소는 제거하기
		elementPrint(a, (l - 1)); //달라진 배열 출력
		return (l - 1); //원소 하나 제거했기 때문에 l에 1 빼서 리턴
	}
}

int main(void) {
	int len;
	int arr[MAX_L]; //지정된 길이만큼 배열 선언
	printf("How many numbers? ");
	scanf("%d", &len); //배열의 길이 입력 받기
	printf("Input %d numbers\n", len);
	elementGeneration(arr, len); //generation 메소드 이용해서 배열 입력 받기
	elementPrint(arr, len); //입력받은 배열 출력하기

	while (1) { //시스템이 끝나기 전까지 반복
		int n;
		puts("Choose operation:");
		puts("1. insertion  2. deletion  3.output  0:program end");
		scanf("%d", &n); //어떤 동작 수행할건지 입력 받기
		switch (n) { //switch문으로 각 번호 당 메소드 실행
		case 1:
			len=elementInsertion(arr, len); //원소 삽입하기
			break;
		case 2:
			len=elementDeletion(arr, len); //원소 제거하기
			break;
		case 3:
			elementPrint(arr, len); //배열 출력하기
			break;
		default:
			return -1; //1~3 외의 다른 숫자 입력했을 경우 종료하기
		}
	}
	return 0;
}
