#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct {
	int key;
}element;

typedef struct {	//heap의 기본 구조
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

HeapType* create() {	//동적 메모리 할당
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {	//heapsize를 0으로 초기화
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item) {	//max heap에서 새로운 노드를 추가
	int i;
	i = ++(h->heap_size);		//heap의 최대 크기 증가 후 말단에 새로운 노드 넣는다고 가정
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {	//트리 위로 올라가면서 부모 노드 key와 비교
		h->heap[i] = h->heap[i / 2];						//새 노드의 key 값보다 작은 경우 부모 노드 아래로 내림
		i /= 2;												//인덱스를 부모 위치로 이동
	}
	h->heap[i] = item;										//최종적으로 결정된 위치에 새 노드 insert
}

int find_index(HeapType* h, element item) {
	for (int i = 1; i <= h->heap_size; i++) {	//heap의 처음부터 끝까지 돌면서 같은 key 갖는 i 반환
		if (h->heap[i].key == item.key)
			return i;
	}
	return 0;	//없을 경우 0 반환
}

bool same_value(HeapType* h, int value) {
	element e;
	e.key = value;	//element에 비교할 값 대입
	return find_index(h, e) != 0;	//find 실행해서 0 나오면 같은 값 없는 경우
}

element delete_item(HeapType* h, element del) {		//max heap에서 선택한 노드 삭제
	int i = find_index(h, del);

	int parent = i, child = i*2;				//i의 자식 노드부터 i 노드와 비교
	element item = h->heap[i];				//삭제 후 반환할 노드
	element temp = h->heap[h->heap_size--];	//말단 노드를 temp에 대입하여 후에 위로 이동
	while (child <= h->heap_size) {			//말단까지 내려가면서 자식노드 key 값과 temp의 key 값 비교
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))	//sibling이 있을 때 둘 중 큰 값 찾기
			child++;						//sibling이 비교 대상 노드가 됨
		if (temp.key >= h->heap[child].key)	break;	//신규 노드의 key 값이 자식보다 더 클 경우 위치 확정되어 반복 종료
		h->heap[parent] = h->heap[child];	//자식 노드 key가 더 크면 부모 노드에 자식 노드 복사
		parent = child;						//parent의 인덱스를 child의 인덱스로 변경
		child *= 2;							//child의 인덱스는 그 아래 child로 변경
	}
	h->heap[parent] = temp;					//최종 확정된 위치에 신규 노드를 insert
	return item;
}

void print_heap(HeapType* h) {	//heap 프린트
	for (int i = 1; i <= h->heap_size; i++) { //최상단부터 말단까지 반복하여 print
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}

int main(void) {
	bool tf = true;
	char choice;
	HeapType* heap = create();	//max heap 동적 메모리 할당
	init(heap);	//초기화

	while (tf) {
		printf("* Input Operation I(Insert) D(Delete) X(Exit): ");
		scanf(" %c", &choice);	//어떤 operation 선택했는지 입력 받기
		switch (choice) {
		case 'I':	//Insert 선택했을 경우
			int insert;
			element e;
			printf("Input value to insert: ");
			scanf("%d", &insert);
			if (same_value(heap, insert))
				printf("same value exists\n");
			else {
				e.key = insert;	//새로운 element 생성해서 입력값 넣기
				insert_max_heap(heap, e);
			}
			break;
		case 'D':	//delete 선택했을 경우
			int del;
			element d;
			printf("Input value to insert: ");
			scanf("%d", &del);	//삭제 원하는 값 입력 받아서 element에 대입
			d.key = del;
			delete_item(heap, d);	//delete 실행
			break;
		case 'P':
			print_heap(heap);
			break;
		default:	//위의 경우와 다른 입력값이면 tf false로 바꾸고 반복문 종료
			tf = false;
			break;
		}
	}
	free(heap);
	return 0;
}
