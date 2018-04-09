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

typedef struct StackTreeNodeStruct {
	TreeNode *treeNode;
	struct StackTreeNodeStruct *next;
} StackTreeNode;

#pragma region STACK_FUNCTIONS_IMPLEMENTATION

int isEmptyStack(StackTreeNode **stack) {
	return (*stack == NULL);
}

StackTreeNode *allocateStackNode() {
	StackTreeNode *node;
	node = malloc(sizeof(StackTreeNode));
	return node;
}

int push(StackTreeNode **stack, TreeNode *elem) {
	StackTreeNode *node;
	node = allocateStackNode();
	if (node == NULL) {
		return 0;
	}
	node->treeNode = elem;
	node->next = *stack;
	*stack = node;
	return 1;
}

TreeNode *pop(StackTreeNode **stack) {
	StackTreeNode *old;
	TreeNode *elem = NULL;
	if (!isEmptyStack(stack)) {
		old = *stack;
		*stack = (*stack)->next;
		elem = old->treeNode;
		free(old);
	}
	return elem;
}

#pragma endregion

#pragma region TREE_NODE_ALLOCATION_FUNCTIONS

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

#pragma endregion

void createTree(Tree *tree) {
	printf("Input degree of tree: ");
	tree->maxNumberOfChildren = readInt();
	tree->root = allocateNewNode(tree->maxNumberOfChildren);
	newNodeInit(tree->root, tree->maxNumberOfChildren);
	printf("Input value for the root node: ");
	tree->root->data = readInt();
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

/*
*	TODO:
*	Check if preorder traversal works
*	This probably works
*/
void preorderTraverseTree(TreeNode *root, int degreeOfTree, void(*processNode)(TreeNode *)) {
	StackTreeNode *stack = NULL;
	TreeNode *current, *next;
	int i;
	int flag;
	flag = push(&stack, root);
	while (!isEmptyStack(&stack)) {
		current = pop(&stack);
		while (current != NULL) {
			for (i = degreeOfTree - 1; i > 0; i--) {
				if (current->children[i] != NULL) {
					flag = push(&stack, current->children[i]);
				}
			}
			next = current->children[0];
			processNode(current);
			current = next;
		}
	}
	return;
}

void outputTreeNode(TreeNode *node) {
	printf("%d ", node->data);
	return;
}

void outputTreePreodrer(TreeNode *root, int degreeOfTree) {
	printf("Preorder traversal of tree:\n");
	preorderTraverseTree(root, degreeOfTree, outputTreeNode);
	printf("\n");
	return;
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
		case 1:
			/* TODO: if tree exists, deallocation */
			createTree(&tree);
			break;
		case 2:
			/* TODO: implement */
			break;
		case 3:	// Outputs preorder traversal of tree
			outputTreePreodrer(tree.root, tree.maxNumberOfChildren);
			break;
		case 4:	// Outputs height of tree
			printf("Tree height: %d\n", getHeightOfTree(tree.root));
			break;
		case 5:
			/* TODO: implement */
			break;
		case 0:	// Exit program
			/* TODO: deallocation */
			free(tree.root);
			exit(0);
		default:
			break;
		}
		printf("\n");
	}

	return 0;
}
