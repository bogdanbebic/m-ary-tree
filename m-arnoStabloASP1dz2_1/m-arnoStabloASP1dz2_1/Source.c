#include <stdio.h>

typedef struct TreeNodeStruct {
	int data;
	struct TreeNodeStruct **children;
} TreeNode;

typedef struct TreeStruct {
	TreeNode *root;
	int maxNumberOfChildren;
	int height;
} Tree;

int main() {

	return 0;
}
