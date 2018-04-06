#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNodeStruct {
	int data;
	struct TreeNodeStruct **children;
} TreeNode;

typedef struct TreeStruct {
	TreeNode *root;
	int maxNumberOfChildren;
	int numberOfNodes;
	int height;
} Tree;

#pragma region STACK_IMPLEMENTATION

typedef struct StackTreeNodeStruct {
	TreeNode *treeNode;
	struct StackTreeNodeStruct *next;
} StackTreeNode;

StackTreeNode *allocateStackNode() {
	StackTreeNode *node;
	node = malloc(sizeof(StackTreeNode));
	return node;
}

int push(StackTreeNode *stack, TreeNode *elem) {
	StackTreeNode *node;
	node = allocateStackNode();
	if (node == NULL) {
		return 0;
	}
	node->treeNode = elem;
	node->next = stack;
	return 1;
}

TreeNode *pop(StackTreeNode *stack) {
	StackTreeNode *old;
	TreeNode *elem = NULL;
	if (stack != NULL) {
		old = stack;
		stack = stack->next;
		elem = old->treeNode;
		free(old);
	}
	return elem;
}

#pragma endregion

int main() {

	return 0;
}
