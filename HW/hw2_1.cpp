#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {	//트리 노드 구조체
	int data;
	struct TreeNode* left, * right;
}TreeNode;

int get_largest(TreeNode* root) {	//트리의 최대 key 값 반환
	int root_val, left, right, max=INT_MIN;	//모든 값들은 가장 작게 설정
	if (root != NULL) {
		root_val = root->data;				//현재 루트의 값을 저장
		left = get_largest(root->left);		//현재 루트의 왼쪽 값 저장
		right = get_largest(root->right);	//현재 루트의 오른쪽 값 저장
		if (left > right)					//현재, 왼쪽, 오른쪽 값 중 더 큰 값을 max에 저장
			max = left;
		else
			max = right;
		if (root_val > max)
			max = root_val;
	}
	return max;		//정해진 max 반환
}

int get_smallest(TreeNode* root) {	//트리의 최소 key 값 반환
	int root_val, left, right, min=INT_MAX;	//모든 값들은 가장 크게 설정
	if (root != NULL) {
		root_val = root->data;				//현재 루트의 값을 저장
		left = get_smallest(root->left);	//현재 루트의 왼쪽 값 저장
		right = get_smallest(root->right);	//현재 루트의 오른쪽 값 저장
		if (left < right)					//현재, 왼쪽, 오른쪽 값 중 더 작은 값을 min에 저장
			min = left;
		else
			min = right;
		if (root_val < min)
			min = root_val;
	}
	return min;		//정해진 min 반환
}

int get_sum(TreeNode* root) {		//트리의 모든 key 값의 합계 반환
	if (root==NULL) return 0;	//아무것도 없을 경우에는 0 반환
	else {
		return get_sum(root->left) + get_sum(root->right) + root->data;	//재귀적으로 해결
	}

}

int get_one_node(TreeNode* exp) { //child를 한 개 갖는 노드의 수 반환
	if (exp == NULL) return 0;
	else {
		if (exp->left == NULL || exp->right == NULL)
			if (exp->right == NULL && exp->left == NULL) return 0;		//말단 노드일 경우 0 반환
			else
				return get_one_node(exp->left) + get_one_node(exp->right)+1;	//child가 하나 있을 경우 재귀에다가 1 더해서 반환
		else return get_one_node(exp->left) + get_one_node(exp->right);	//child가 두 개 있는 경우 재귀
	}
}

//첫번째 트리 상태
//TreeNode n0 = { 11, NULL, NULL };
//TreeNode n1 = { 2, &n0, NULL };
//TreeNode n2 = { 5, &n1, NULL };
//TreeNode n3 = { 13, &n2, NULL };
//TreeNode n4 = { 25, &n3, NULL };
//TreeNode n5 = { 8, NULL, NULL };
//TreeNode n6 = { 3, NULL, &n5 };
//TreeNode n7 = { 21, &n4, &n6 };
//TreeNode* exp = &n7;

//두번째 트리 상태
TreeNode n0 = { 10, NULL, NULL };
TreeNode n1 = { 27, &n0, NULL };
TreeNode n2 = { 4, NULL, NULL };
TreeNode n3 = { 15, &n1, &n2 };
TreeNode n4 = { 16, NULL, NULL };
TreeNode n5 = { 25, NULL, NULL };
TreeNode n6 = { 7, &n4, &n5 };
TreeNode n7 = { 55, &n3, &n6 };
TreeNode n8 = { 40, NULL, NULL };
TreeNode n9 = { 36, NULL, &n8 };
TreeNode n10 = { 20, &n7, &n9 };
TreeNode* exp = &n10;


int main(void) {
	printf("\nSum of keys in tree: %d\n", get_sum(exp));
	printf("Num of one child nodes: %d\n", get_one_node(exp));
	printf("Max value: %d\n", get_largest(exp));
	printf("Min value: %d\n", get_smallest(exp));
	return 0;
}
