#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {	//트리 노드 구조체
	int data;
	struct TreeNode* left, * right;
}TreeNode;

int get_node_count(TreeNode* exp) {	//트리 안에 몇개의 노드가 들어가있는지 반환
	if (exp == NULL) return 0;
	else
		return get_node_count(exp->left) + get_node_count(exp->right) + 1;
}

int get_leaf_count(TreeNode* exp) { //트리 안에 몇개의 leaf가 들어가있는지 반환
	if (exp == NULL) return 0;
	else {
		if (exp->left == NULL && exp->right == NULL) return 1;				//leaf 노드인 경우
		else return get_leaf_count(exp->left) + get_leaf_count(exp->right);	//child가 있는 경우
	}
}

int get_height(TreeNode* exp) {		//트리의 높이 반환
	if (exp == NULL) return 0;
	else {
		int l_height = get_height(exp->left);
		int r_height = get_height(exp->right);
		if (l_height >= r_height) return l_height + 1;	//왼쪽과 오른쪽 중에 더 큰 값에
		else return r_height + 1;						//노드 자기 자신까지 더해서 반환
	}
}

bool check_balance(TreeNode* exp) {	//balanced tree인지 확인하는 함수
	if (exp == NULL)	return true;
	else {
		int num = get_height(exp->right) - get_height(exp->left);
		if (num > 1 || num < -1) {	//만약 양쪽 subtree의 높이 차가 1 초과인 경우에는
			return false;			//false 반환
		}
		else return check_balance(exp->right) & check_balance(exp->left);	//양쪽 노드 and 연산해서 return 재귀
	}
}

void inorder(TreeNode* root) {		//inorder 방식으로 트리 노드들 출력
	if (root == NULL)	return;		//empty 상태라면 NULL 반환
	else {
		inorder(root->left);		//left subtree traverse
		printf(" [%d]", root->data);
		inorder(root->right);		//right subtree traverse
	}
}

void print_large(TreeNode* root, int key) {	//주어진 값보다 큰 노드만 출력
	if (root == NULL)	return;				//empty 상태라면 NULL 반환
	else {
		print_large(root->left, key);		//left subtree traverse
		if(root->data>key)	printf(" [%d]", root->data);	//더 큰 경우에만 출력
		print_large(root->right, key);		//right subtree traverse
	}
}

//첫번째 트리 상태
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, NULL, NULL };
TreeNode n3 = { 15, &n1, &n2 };
TreeNode n4 = { 16, NULL, NULL };
TreeNode n5 = { 25, NULL, NULL };
TreeNode n6 = { 7, &n4, &n5 };
TreeNode n7 = { 30, &n3, &n6 };
TreeNode* exp = &n7;

//두번째 트리 상태
//TreeNode n1 = { 1, NULL, NULL };
//TreeNode n2 = { 4, NULL, NULL };
//TreeNode n3 = { 15, &n1, &n2 };
//TreeNode n7 = { 30, &n3, NULL };
//TreeNode* exp = &n7;

int main(void) {
	inorder(exp);	//지금까지 저장된 트리 출력
	printf("\nNumber of nodes in tree: %d\n", get_node_count(exp));
	printf("Height of the tree: %d\n", get_height(exp));
	printf("Number of leafs in tree: %d\n", get_leaf_count(exp));
	printf("Balanced tree? ");
	if (check_balance(exp)) printf("Yes\n");
	else printf("No\n");
	printf("Input a number to check: ");
	int num;
	scanf("%d", &num);	//더 큰 숫자만 출력하도록 값 입력 받기
	printf("numbers greater than %d: ", num);
	print_large(exp, num);
	return 0;
}
