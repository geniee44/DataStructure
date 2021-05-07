#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//다항식 항마다 생성되는 노드
typedef struct ListNode {
	int coef; //계수
	int expon; //차수
	struct ListNode* link; //다음 연결리스트 노드
} ListNode;

//연결리스트 헤더
typedef struct ListType { //다항식 정보를 저장하는 노드
	int size; //다항식의 항수
	ListNode* head; //다항식 처음 노드 주소
	ListNode* tail; //다항식 마지막 노드 주소
} ListType;

void error(const char* message) { //오류 메시지 출력하는 메소드
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListType* create(void) { //다항식 정보를 저장하는 노드 생성
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->head = NULL;
	plist->tail = NULL;
	plist->size = 0;
	return plist;
}

void insert_last(ListType* plist, int coef, int expon) { //리스트 마지막에 항 추가
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode)); //추가할 노드 생성
	if (temp == NULL) error("memory allocation error\n"); //메모리할당 실패시 오류 메시지 출력
	temp->coef = coef; //임시노드의 계수, 차수 대입
	temp->expon = expon;
	temp->link = NULL; //마지막에 추가하기 때문에 링크에 NULL 대입
	if (plist->tail == NULL) //빈 리스트일 경우
		plist->head=plist->tail= temp; //새로운 노드가 유일한 노드가 됨
	else { //기존에 노드 있을 경우
		plist->tail->link = temp; //다항식의 리스트의 맨 마지막에 새 노드 추가
		plist->tail = temp; //다항식의 마지막 항의 정보를 새 노드 주소로 수정
	}
	plist->size++; //다항식의 갯수 증가
}

void poly_print(ListType* plist) { //다항식 출력
	ListNode* node = plist->head; //다항식의 처음 원소를 가리키는 주소
	printf("\n<Polynomial>\n");
	for (int i = 0; i < plist->size - 1; i++) { //리스트의 처음부터 마지막의 전까지 출력
		printf("%dx^%d + ", node->coef, node->expon);
		node = node->link; //노드는 한 칸씩 이동
	}
	printf("%dx^%d \n", node->coef, node->expon); //마지막 항 출력
}

int poly_cal(ListType* plist, int x) { //입력받은 값으로 계산하는 메소드
	ListNode* node = plist->head; //다항식의 처음 원소를 가리키는 주소
	int sum = 0; //결과를 더할 값
	while (node) {
		sum += (node->coef) * pow(x, (node->expon)); //x 값에 차수만큼 제곱하여 계수 곱해서 sum에 더하기
		node = node->link; //노드는 한 칸씩 이동
	}
	return (int)sum;
}

int main(void) {
	ListType* list;
	list = create(); //다항식 생성
	printf("Input coef and exponent of polynomial(마지막항:exponent를 0으로 입력)\n");
	int coef, exponent, x;
	bool tf = true; //반복문 빠져나오기 위한 변수

	while(tf){
		scanf("%d %d", &coef, &exponent); //계수, 차수 입력 받기
		insert_last(list, coef, exponent); //입력 받을 때마다 리스트에 추가
		if (exponent == 0) tf=false; //차수가 0일 경우 반복문 나오기
	}
	poly_print(list); //입력받은 다항식 출력

	printf("Input the value x: ");
	scanf("%d", &x); //x값 입력 받기
	int result = poly_cal(list, x); //계산 결과 저장하여 출력
	printf("Result of polynomial with x: %d", result);

}
