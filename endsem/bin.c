#include <stdio.h>
#include <stdlib.h>

// Structure definition for the tree node
struct node
{
	struct node *left;
	struct node *right;
	int val;
};

// Function to find a node in the binary tree given its indices
struct node *finder(struct node *head, int *indices, int k)
{
	struct node *ptr = head;
	int i = 0;

	if (head == NULL || head->val != indices[0])
	{
		return NULL;
	}

	while (i < k)
	{
		i++;
		if (ptr->left != NULL && ptr->left->val == indices[i])
		{
			ptr = ptr->left;
		}
		else if (ptr->right != NULL && ptr->right->val == indices[i])
		{
			ptr = ptr->right;
		}
		else
		{
			return NULL;
		}
	}
	return ptr;
}

// Function to create a new tree node
struct node *createNode(int value)
{
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	newNode->val = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// Function to build a mock binary tree
struct node *buildMockTree()
{
	/*
				1
			   / \
			  2   3
			 / \ / \
			4  5 6  7
	*/
	struct node *root = createNode(1);
	root->left = createNode(2);
	root->right = createNode(3);
	root->left->left = createNode(4);
	root->left->right = createNode(5);
	root->right->left = createNode(6);
	root->right->right = createNode(7);
	root->left->right->right = createNode(8);
	return root;
}

// Function to test the finder function
void testFinder()
{
	// Create a mock tree
	struct node *tree = buildMockTree();

	// Test case 1: Searching for a path that exists
	int indices1[] = {1, 2, 5, 8}; // Path: 1 -> 3 -> 7
	struct node *result1 = finder(tree, indices1, 3);
	if (result1 != NULL && result1->val == 8)
	{
		printf("Test case 1: OK\n");
	}
	else
	{
		printf("Test case 1: Error\n");
	}

	// Test case 2: Searching for a path that doesn't exist
	int indices2[] = {1, 3, 8}; // Path: 1 -> 3 -> 8 (8 doesn't exist)
	struct node *result2 = finder(tree, indices2, 2);
	if (result2 == NULL)
	{
		printf("Test case 2: OK\n");
	}
	else
	{
		printf("Test case 2: Error\n");
	}

	// Test case 3: Searching with a NULL tree
	int indices3[] = {1, 3, 7}; // Path: 1 -> 3 -> 7
	struct node *result3 = finder(NULL, indices3, 2);
	if (result3 == NULL)
	{
		printf("Test case 3: OK\n");
	}
	else
	{
		printf("Test case 3: Error\n");
	}

	// Test case 4: Searching with empty indices array
	int indices4[] = {}; // Empty array
	struct node *result4 = finder(tree, indices4, 0);
	if (result4 == NULL)
	{
		printf("Test case 4: OK\n");
	}
	else
	{
		printf("Test case 4: Error\n");
	}
}

// Main function
int main()
{
	// Run the test cases
	testFinder();

	return 0;
}
