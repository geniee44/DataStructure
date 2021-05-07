#include <stdio.h>
#include <malloc.h>

typedef int element;
typedef struct ListNode { //이중원형연결 노드 구조
	element data;
	struct ListNode* llink; //왼쪽 링크
	struct ListNode* rlink; //오른쪽 링크
}ListNode;

void init(ListNode* phead) { //이중원형연결리스트 초기화
	phead->rlink = phead;
	phead->llink = phead;
}

ListNode* insert_last(ListNode* head, element val) { //새로운 노드를 리스트의 마지막에 저장하는 함수
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //새로운 노드 생성
	p->data = val; //데이터 대입
	if (head == NULL) { //리스트가 비어있는 경우
		head = p;
		p->rlink = head;
		p->llink = head;
	}
	else { //리스트가 비어있지 않은 경우
		p->llink = head->llink;
		p->rlink = head;
		p->llink->rlink = p;
		p->rlink->llink = p;
	}
	return head;
}


void print_list(ListNode* head) { //연결리스트 출력하는 함수
	ListNode* p = head->rlink; //리스트의 처음 원소를 가리키는 주소
	do { //리스트의 마지막 원소 제외하고 출력
		printf(" %d <->", p->data);
		p = p->rlink; //노드 한 칸씩 오른쪽으로 이동
	} while (p != head->llink); //마지막까지 가기 전에 반복문 종료
	printf(" %d \n", p->data); //리스트의 마지막 원소 출력
}

void reverse_print_list(ListNode* head) { //연결리스트 반대로 출력하는 함수
	ListNode* p = head->llink; //리스트의 마지막 원소를 가리키는 주소
	do { //리스트의 첫번째 원소 제외하고 출력
		printf(" %d <->", p->data);
		p = p->llink; //노드 한 칸씩 왼쪽으로 이동
	} while (p != head->rlink);
	printf(" %d \n", p->data); //리스트의 첫번째 원소 출력
}

int main(void) {
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	init(head); //head 노드 초기화
	int num;
	bool tf = true; //반복문 빠져나오기 위한 변수
	printf("Input an integer to add <0 to quit>\n");

	while(tf){
		scanf("%d", &num);
		if (num == 0) tf=false; //입력받은 수가 0일 경우 종료
		else head = insert_last(head, num); //입력받은 수 리스트의 마지막에 삽입
	}
	print_list(head); //리스트 출력
	printf("Print the list in reverse order\n");
	reverse_print_list(head); //리스트 역순 출력
}
