#include <stdio.h>
#include <malloc.h>
#define MAX_LENGTH 100 //최대 길이 지정

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode; //node 구조체 만들기

ListNode* insert(ListNode* head, element val) { //맨 뒤에 노드 추가하는 함수
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	if (head == NULL) { //노드가 아무것도 없을 경우
		p->data = val; //데이터 저장
		p->link = head;
		head = p;
		return head; //첫번째에 노드 추가하듯이 함
	}
	else { //헤더가 비어있지 않을 경우
		ListNode* t = head; //새롭게 t를 만들어 가장 뒤까지 가게 while문 돌림
		while (t->link != NULL)
			t = t->link;
		p->data = val; //데이터 저장
		t->link = p; //링크 조정
		p->link = NULL;
		return head;
	}
}

void find_max_min(ListNode* head) { //최대, 최소 찾는 함수
	int max = head->data; //비교하기 위해 max에 헤더에 저장된 데이터 대입
	for (ListNode* p = head; p != NULL; p = p->link) //헤더에서 링크로 연결된 모든 노드 돌기
		if (max < p->data)	max = p->data; //max보다 더 큰 값 찾으면 교체
	
	int min = head->data; //max와 동일
	for (ListNode* p = head; p != NULL; p = p->link)
		if (min > p->data) min = p->data; //min보다 더 작은 값 찾으면 교체

	printf("\nMax: %-3d   Min: %-3d", max, min); //찾은 최대, 최소 출력
}

void print_list(ListNode*head){ //연결리스트 출력하는 함수
	for (ListNode* p = head; p != NULL; p = p->link) //head부터 링크로 연결된 노드의 data 전부 출력
		printf("%3d ", p->data);
}

int main(void) {
	ListNode* head = NULL;
	int num;

	while (1) {
		printf("Input an integer to add <0 to quit>: ");
		scanf(" %d", &num); //scanf로 입력 받기
		if (num == 0)
			break; //입력값이 0일 경우 break해서 입력 받기 중단
		else {
			head = insert(head, num); //입력값이 0이 아니면 insert 함수 이용해서 리스트 추가
		}
	}
	insert(head, 6);
	printf("\n<List>\n");
	print_list(head); //리스트 출력
	find_max_min(head); //최대, 최소 찾기
}
