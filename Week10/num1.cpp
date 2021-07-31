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

void insert_min_heap(HeapType* h, element item) {	//min heap에서 새로운 노드 추가
	int i;
	i = ++(h->heap_size);							//heap의 최대 크기 증가 후 말단에서 새로운 노드 넣는다고 가정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {	//트리 위로 올라가면서 부모 노드의 key와 비교
		h->heap[i] = h->heap[i / 2];						//새 노드의 key 값보다 큰 경우 부모 노드 아래로 내림
		i /= 2;												//인덱스를 부모 위치로 이동
	}
	h->heap[i] = item;										//최종적으로 결정된 위치에 새 노드 insert
}

element delete_max_heap(HeapType* h) {		//max heap에서 최상단 노드 삭제
	int parent = 1, child = 2;				//두번째 노드부터 root 노드와 비교
	element item = h->heap[1];				//삭제 후 반환할 노드
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

element delete_min_heap(HeapType* h) {		//min heap에서 최상단 노드 삭제
	int parent = 1, child = 2;				//두번째 노드부터 root 노드와 비교
	element item = h->heap[1];				//삭제 후 반환할 노드
	element temp = h->heap[h->heap_size--];	//말단 노드를 temp에 대입하여 후에 위로 이동
	while (child <= h->heap_size) {			//말단까지 내려가면서 자식노드 key 값과 temp의 key 값 비교
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))	//sibling이 있을 때 둘 중 작은 값 찾기
			child++;						//sibling이 비교 대상 노드가 됨
		if (temp.key <= h->heap[child].key)	break;	//신규 노드의 key 값이 자식보다 더 작을 경우 위치 확정되어 반복 종료
		h->heap[parent] = h->heap[child];	//자식 노드 key가 더 작으면 부모 노드에 자식 노드 복사
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
	HeapType* max_heap = create();	//max heap 동적 메모리 할당
	HeapType* min_heap = create();	//min heap 동적 메모리 할당
	init(max_heap);	//초기화
	init(min_heap);

	while (tf) {
		printf("* Input Operation I(Insert) D(Delete) X(Exit): ");
		scanf(" %c", &choice);	//어떤 operation 선택했는지 입력 받기
		switch (choice) {
		case 'I':	//Insert 선택했을 경우
			int insert;
			element e;
			printf("Input value to insert: ");
			scanf(" %d", &insert);
			e.key = insert;	//새로운 element 생성해서 입력값 넣기
			insert_max_heap(max_heap, e);
			insert_min_heap(min_heap, e);
			break;
		case 'D':	//delete 선택했을 경우
			delete_max_heap(max_heap);
			delete_min_heap(min_heap);
			break;
		default:	//위의 경우와 다른 입력값이면 tf false로 바꾸고 반복문 종료
			tf = false;
			break;
		}
		if (tf) {	//반복문 나가는 경우 아닐 때만 print 실행
			printf("<Max Heap>\n");
			print_heap(max_heap);
			printf("<Min Heap>\n");
			print_heap(min_heap);
		}
	}
	free(max_heap);
	free(min_heap);

	return 0;
}
