#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {	//treenode 기본 구조체
	int key;
	struct TreeNode* left, * right;
}TreeNode;

TreeNode* new_node(int item) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));	//새로운 메모리 할당
	node->key = item;										//값 복사
	node->left = node->right = NULL;						//child 노드를 NULL로 초기화
	return node;											//새로 생성된 노드 반환
}

TreeNode* insert_node(TreeNode* node, int key) {	//해당 위치 찾아서 key 값 갖는 노드 insert
	if (node == NULL)	return new_node(key);		//tree가 공백일 경우 insert된 새로운 노드 반환
	if (key < node->key)		//insert할 값이 root의 key 값보다 작을 경우 left subtree를 root로 insert 재귀호출
		node->left = insert_node(node->left, key);
	else if (key > node->key)	//insert할 값이 root의 key 값보다 클 경우 right subtree를 root로 insert 재귀호출
		node->right = insert_node(node->right, key);
	return node;				//변경된 root 포인터 반환
}

void inorder(TreeNode* root) {
	if (root == NULL)	return;		//tree가 empty인 상태면 NULL 반환
	else {
		inorder(root->left);		//left subtree traverse
		printf(" [%d]", root->key);
		inorder(root->right);		//right subtree traverse
	}
}

TreeNode* search(TreeNode* node, int key) {
	if (node == NULL)	return NULL;
	if (node->key == key)
		return node;						//찾는 노드일 경우 반환
	else if (key < node->key)
		return search(node->left, key);		//left subtree 대입해서 다시 search 재귀
	else return search(node->right, key);	//right subtree 대입해서 다시 search 재귀
}

TreeNode* min_value_node(TreeNode* node) {	//가장 왼쪽의 말단 노드 찾기
	TreeNode* current = node;
	while (current->left != NULL)			//NULL이 될 때까지 왼쪽 child로 계속 내려감
		current = current->left;
	return current;
}

TreeNode* max_value_node(TreeNode* node) {	//가장 오른쪽의 말단 노드 찾기
	TreeNode* current = node;
	while (current->right != NULL)
		current = current->right;			//NULL이 될 때까지 오른쪽 child로 계속 내려감
	return current;
}

TreeNode* delete_node(TreeNode* root, int key) {		//key가 저장된 노드 찾아 삭제하고 새로운 root 반환
	if (root == NULL)	return root;
	else if (root->key > key)							//왼쪽 subtree에서 key 값을 찾아 삭제하도록 재귀 호출
		root->left = delete_node(root->left, key);		//새로운 left child로 변경
	else if (root->key < key)							//오른쪽 subtree에서 key 값을 찾아 삭제하도록 재귀 호출
		root->right = delete_node(root->right, key);	//새로운 right child로 변경
	else {											//삭제할 key를 찾았을 경우
		if (root->left == NULL) {					//leaf노드이거나 하나의 child를 갖는 노드일 경우
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		//child가 둘 다 있는 경우
		TreeNode* temp = NULL;
		TreeNode* temp1 = max_value_node(root->left);	//왼쪽 subtree의 최댓값 찾기
		TreeNode* temp2 = min_value_node(root->right);	//오른쪽 subtree의 최소값 찾기
		//뭐 찾았는지 출력
		printf("left의 subtree의 max: %d\nright의 subtree의 min: %d\n", temp1->key, temp2->key);

		if ((key - (temp1->key)) < ((temp2->key) - key)) {	//왼쪽의 최댓값이 원래 값에 더 가까운 경우
			temp = temp1;			//temp에 해당 노드 대입
			printf("original value: %d   new value: %d\n", key, temp->key);
			root->key = temp->key;	//삭제할 위치에 복사
			root->left = delete_node(root->left, temp->key);	//복사된 값을 갖고 있던 노드 삭제
		}
		else {												//오른쪽의 최소값이 원래 값에 더 가까운 경우
			temp = temp2;			//temp에 해당 노드 대입
			printf("original value: %d   new value: %d\n", key, temp->key);
			root->key = temp->key;	//삭제할 위치에 복사
			root->right = delete_node(root->right, temp->key);	//복사된 값을 갖고 있던 노드 삭제
		}
	}
	return root;	//새로운 root 반환
}

int main(void) {
	TreeNode* root = NULL;	//tree에 노드 insert
	root = insert_node(root, 30);
	root = insert_node(root, 20);
	root = insert_node(root, 10);
	root = insert_node(root, 45);
	root = insert_node(root, 50);
	root = insert_node(root, 60);

	printf("이진 탐색 트리 중위 순회 결과\n");
	inorder(root);		//기존 트리에 있던 노드들 중위 순회로 출력

	char choice;
	bool tf = true;		//while문을 tf가 true일 때 동안 반복
	while (tf) {
		printf("\n\n* operation 선택: Insert(I) / Delete(D) / Exit(X) : ");
		scanf(" %c", &choice);	//사용자에게 원하는 계산 입력 받기
		int num;
		switch (choice)
		{
		case 'I':		//insert 선택한 경우
			printf("Insert할 값은? ");
			scanf(" %d", &num);				//insert할 값 입력 받아
			root = insert_node(root, num);	//insert해주고
			inorder(root);					//바뀐 tree 중위 순회 방식으로 출력
			break;
		case 'D':		//delete 선택한 경우
			printf("Delete할 값은? ");
			scanf(" %d", &num);			//delete할 값 입력 받아
			delete_node(root, num);		//delete해주고
			inorder(root);				//바뀐 tree 중위 순회 방식으로 출력
			break;
		default:		//insert와 delete 외에 exit 선택한 경우
			printf("프로그램 종료\n");
			tf = false;	//tf를 false로 변경하여 while 반복문 종료
			break;
		}
	}
	return 0;
}
