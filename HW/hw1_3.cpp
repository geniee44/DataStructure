#include <stdio.h>
#include <malloc.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode; //node 구조체 만들기

ListNode* insert(ListNode* head, element val) { //오름차순으로 노드 추가하는 메소드
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = val; //노드에 데이터 저장
	if (head == NULL) { //노드가 아무것도 없을 경우
		p->link = NULL;
		head = p;
		return head; //첫번째에 노드 추가하듯이 함
	}
	else { //헤더가 비어있지 않을 경우
		ListNode* check, * find = NULL; //새롭게 두 노드를 생성하여 리스트 전체 검토
		for (check = head; check != NULL; check = check->link)
			if (check->data < p->data)
				find = check; //만약 기존 데이터가 새로운 데이터보다 작다면 find를 계속 check로 바꿔줌

		if (find == NULL) { //새로운 데이터가 리스트 중 가작 작을 경우
			p->link = head;
			head = p; //첫번째에 노드 추가
		}
		else { //리스트 중간에 삽입해야하는 경우
			p->link = find->link; //찾아놓은 find 노드의 뒤에 새로운 노드 삽입
			find->link = p;
		}
		return head;
	}
}

void print_list(ListNode* head) { //연결리스트 출력하는 함수
	ListNode* p = NULL;
	for (p = head; p->link != NULL; p = p->link) //head부터 링크로 연결된 노드 중 마지막을 제외하고 출력 
		printf("  %d  ->", p->data);
	printf("  %d  ->  NULL", p->data); //리스트의 마지막 데이터 출력
}

int main(void) {
	ListNode* head = NULL; //새로운 리스트 생성
	int num;

	while (1) {
		printf("\nInput data to insert to linkedList <0 to quit>\n");
		scanf(" %d", &num); //scanf로 새로운 데이터 입력 받기
		if (num == 0)
			break; //입력값이 0일 경우 break해서 입력 받기 중단
		else {
			head = insert(head, num); //입력값이 0이 아니면 insert 함수 이용해서 리스트 추가
			print_list(head); //지금까지 저장한 리스트 출력
		}
	}
	print_list(head); //최종 리스트 출력
	printf("\nProgram finished.");
}
