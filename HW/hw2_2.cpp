#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 15

typedef struct TreeNode {	//treenode 기본 구조체
	char fruit[MAX_SIZE];
	struct TreeNode* left, * right;
}TreeNode;

TreeNode* new_node(char* item) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));	//새로운 메모리 할당
	strcpy(node->fruit, item);										//값 복사
	node->left = node->right = NULL;						//child 노드를 NULL로 초기화
	return node;											//새로 생성된 노드 반환
}

TreeNode* insert_node(TreeNode* node, char* item) {	//해당 위치 찾아서 key 값 갖는 노드 insert
	if (node == NULL)	return new_node(item);		//tree가 공백일 경우 insert된 새로운 노드 반환
	if(strcmp(item, node->fruit)<0)	//insert할 값이 root의 key 값보다 작을 경우 left subtree를 root로 insert 재귀호출
		node->left = insert_node(node->left, item);
	else			//insert할 값이 root의 fruit보다 클 경우 right subtree를 root로 insert 재귀호출
		node->right = insert_node(node->right, item);
	return node;				//변경된 root 포인터 반환
}

TreeNode* init_fruits(TreeNode* root) {	//트리 초기화
	char fruit[MAX_SIZE];
	strcpy(fruit, "apple");
	root = insert_node(root, fruit);
	strcpy(fruit, "banana");
	root = insert_node(root, fruit);
	strcpy(fruit, "blueberry");
	root = insert_node(root, fruit);
	strcpy(fruit, "kiwi");
	root = insert_node(root, fruit);
	strcpy(fruit, "orange");
	root = insert_node(root, fruit);
	strcpy(fruit, "pear");
	root = insert_node(root, fruit);
	return root;
}

void inorder(TreeNode* root) {
	if (root == NULL)	return;		//tree가 empty인 상태면 NULL 반환
	else {
		inorder(root->left);		//left subtree traverse
		printf("%s\n", root->fruit);
		inorder(root->right);		//right subtree traverse
	}
}

TreeNode* search(TreeNode* node, char* item) {
	if (node == NULL)	return NULL;
	if (strcmp(node->fruit, item) == 0)
		return node;						//찾는 노드일 경우 반환
	else if (strcmp(item, node->fruit) < 0)
		return search(node->left, item);		//left subtree 대입해서 다시 search 재귀
	else return search(node->right, item);	//right subtree 대입해서 다시 search 재귀
}

TreeNode* min_value_node(TreeNode* node) {	//가장 왼쪽의 말단 노드 찾기
	TreeNode* current = node;
	while (current->left != NULL)			//NULL이 될 때까지 왼쪽 child로 계속 내려감
		current = current->left;
	return current;
}

TreeNode* delete_node(TreeNode* root, char* item) {		//item이 저장된 노드 찾아 삭제하고 새로운 root 반환
	if (root == NULL)	return root;
	else if (strcmp(root->fruit, item) > 0)							//왼쪽 subtree에서 item 값을 찾아 삭제하도록 재귀 호출
		root->left = delete_node(root->left, item);		//새로운 left child로 변경
	else if (strcmp(root->fruit, item) < 0)							//오른쪽 subtree에서 item 값을 찾아 삭제하도록 재귀 호출
		root->right = delete_node(root->right, item);	//새로운 right child로 변경
	else {											//삭제할 item을 찾았을 경우
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
		TreeNode* temp = min_value_node(root->right);	//child가 둘 다 있는 경우 가장 가까운 값 갖는 노드 찾기
		strcpy(root->fruit, temp->fruit);				//가장 가까운 값을 삭제할 위치에 복사
		root->right = delete_node(root->right, temp->fruit);	//복사된 값을 갖고 있던 노드 삭제
	}
	return root;	//새로운 root 반환
}

int main(void) {
	TreeNode* root = NULL;	//tree에 노드 insert
	root = init_fruits(root);

	int choice;
	bool tf = true;		//while문을 tf가 true일 때 동안 반복
	while (tf) {
		printf("\n* Choose operation<1.insert  2. delete  3. search  4. print  5. exit>: ");
		scanf("%d", &choice);	//사용자에게 원하는 계산 입력 받기
		char input[MAX_SIZE];
		switch (choice)
		{
		case 1:		//insert 선택한 경우
			printf("Enter a word: ");
			scanf(" %s", input);				//insert할 값 입력 받아
			root = insert_node(root, input);	//insert해주고
			break;
		case 2:		//delete 선택한 경우
			printf("Enter a word to delete: ");
			scanf(" %s", input);			//delete할 값 입력 받아
			delete_node(root, input);		//delete해주고
			break;
		case 3:		//search 선택한 경우
			printf("Enter a word: ");
			scanf(" %s", input);
			if (search(root, input) == NULL)	//search 함수 반환 값에 따라 적절히 출력
				printf("%s is not found\n", input);
			else
				printf("%s is found\n", input);
			break;
		case 4:		//print 선택한 경우
			inorder(root);
			break;
		case 5:		//exit 선택한 경우
			printf("Program finished\n");
			tf = false;	//tf를 false로 변경하여 while 반복문 종료
			break;
		default:	//1~5 외의 숫자 입력했을 경우 반복문 다시 수행
			printf("Wrong input\n");
			break;
		}
	}
	return 0;
}
