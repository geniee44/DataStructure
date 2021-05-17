#include <stdio.h>
#include <malloc.h>
#define MAX_LENGTH 100 //최대 길이 지정

typedef int element;
typedef struct ListNode { //이중연결 노드 구조
	element data;
	struct ListNode* llink; //왼쪽 링크
	struct ListNode* rlink; //오른쪽 링크
}ListNode;

void init(ListNode* phead) { //이중연결리스트 초기화
	phead->rlink = phead;
	phead->llink = phead;
}

ListNode* insert(ListNode* head, element val) { //새로운 노드를 리스트의 첫번째에 저장하는 함수
	ListNode* p = (ListNode*)malloc(sizeof(ListNode)); //새로운 노드 생성
	p->data = val; //데이터 대입
	if (head == NULL) { //리스트가 비어있는 경우
		head = p;
		p->rlink = head;
		p->llink = head;
	}
	else { //리스트가 비어있지 않은 경우
		p->rlink = head->rlink;
		head->rlink->llink = p;
		p->llink = head;
		head->rlink = p;
	}
	return head;
}


void print_list(ListNode* head) { //연결리스트 출력하는 함수
	ListNode* p = NULL;
	printf("\n<List>\n");
	for (p = head->rlink; p != head; p = p->rlink) //head부터 링크로 연결된 노드의 data 전부 출력
		printf("%3d ", p->data);
}

void SnD_list(ListNode* head, int num) {
	ListNode* p = NULL;
	bool found = false; //찾은걸 확인하기 위한 변수
	for (p = head->rlink; p != head; p = p->rlink) {
		if (p->data == num) {
			found = true;
			ListNode* removed = p; //노드 지우기 위해 removed 새로 생성
			removed->llink->rlink = removed->rlink; //지우려는 값의 왼쪽 노드와 오른쪽 노드를 서로 링크
			removed->rlink->llink = removed->llink;
			free(removed); //removed 반환
			break;
		}
	}
	if (found)	printf("%d is found and deleted", num);
	else printf("%d is not in the list", num);
	print_list(head); //변경된 리스트 출력
}

int main(void) {
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	init(head); //head 노드 초기화
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
	print_list(head); //리스트 출력
	printf("\nInput a number to search and delete: ");
	scanf("%d", &num); //어떤 값 지울 것인지 입력 받기
	SnD_list(head, num); //지워야하는 값 찾아서 지우기
}
