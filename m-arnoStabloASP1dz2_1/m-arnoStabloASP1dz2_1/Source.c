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

#pragma region INT_READING_FUNCTIONS
#define MAX_LINE 100

int isCorrectIntInput(char *s) {
	int i;
	if (s[0] == '-') i = 1;
	else i = 0;
	for (; s[i] != '\0'; i++) {
		if (s[i] > '9' || s[i] < '0') return 0;
	}
	return 1;
}

int strToInt(char *s) {
	int i;
	int returnValue = 0;
	int isNegative = 0;
	if (s[0] == '-') {
		i = 1;
		isNegative = 1;
	}
	else i = 0;
	for (; s[i] != '\0'; i++) {
		returnValue = returnValue * 10 + (int)(s[i] - '0');
	}
	if (isNegative) returnValue = -returnValue;
	return returnValue;
}

int readInt() {
	int num;
	char s[MAX_LINE];
	int flag = 1;
	while (flag) {
		scanf_s("%s", s, MAX_LINE);
		if (isCorrectIntInput(s)) {
			num = strToInt(s);
			flag = 0;
		}
		else printf("Incorrect input, you must input an integer\n");
	}
	return num;
}
#pragma endregion

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

TreeNode *allocateNewNode(int degreeOfTree) {
	TreeNode *temporary;
	temporary = malloc(sizeof(TreeNode));
	if (temporary != NULL) {
		temporary->children = malloc(degreeOfTree * sizeof(TreeNode));
		if (temporary->children == NULL) {
			free(temporary);
			temporary = NULL;
		}
	}
	return temporary;
}

void newNodeInit(TreeNode *node, int degreeOfTree) {
	int i;
	if (node != NULL) {
		if (node->children != NULL) {
			for (i = 0; i < degreeOfTree; i++) {
				node->children[i] = NULL;
			}
		}
	}
	return;
}

void createTree(Tree *tree) {
	printf("Input degree of tree: ");
	tree->maxNumberOfChildren = readInt();
	/*
	*	TODO:
	*	Implement root allocation
	*/
	return;
}

int getHeightOfTree(TreeNode *root) {
	TreeNode *current = root;
	int height = 0;
	while (current != NULL) {
		height++;
		current = current->children[0];
	}
	return height;
}

void printMenu() {
	printf("1. Create tree of degree m\n");
	printf("2. Insert new node to tree\n");
	printf("3. Output preorder traversal of tree\n");
	printf("4. Calculate height of tree\n");
	printf("5. Delete tree\n");
	printf("0. Exit program\n");
	printf("Enter menu action as integer:\n");
	return;
}

int main() {
	Tree tree;
	int menuOption;

	tree.root = NULL;
	tree.numberOfNodes = 0;
	tree.maxNumberOfChildren = 0;
	tree.height = 0;

	while (1) {
		printMenu();
		menuOption = readInt();
		switch (menuOption) {
		/*
		*	TODO:
		*	Implement all menu options
		*	Implement all menu options functions
		*	Implement allocation check and deallocation
		*/
		case 0:	// Exit program
			/* TODO: deallocation */
			exit(0);
		default:
			break;
		}
		printf("\n");
	}

	return 0;
}
