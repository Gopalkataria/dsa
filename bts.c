#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} Node;

Node *create_node(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *insert(Node *root, int data)
{
    if (root == NULL)
    {
        return create_node(data);
    }

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else
    {
        root->right = insert(root->right, data);
    }

    return root;
}

Node *find_min(Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

Node *delete_min(Node *root)
{
    if (root == NULL)
    {
        return root;
    }

    if (root->left == NULL)
    {
        Node *temp = root->right;
        free(root);
        return temp;
    }

    root->left = delete_min(root->left);
    return root;
}

Node *delete(Node *root, int data)
{
    if (root == NULL)
    {
        return root;
    }

    if (data < root->data)
    {
        root->left = delete (root->left, data);
    }
    else if (data > root->data)
    {
        root->right = delete (root->right, data);
    }
    else
    {
        // Node found

        // Case 1: Node has no child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        // Case 2: Node has only one child
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Node has two children
        Node *temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_min(root->right);
    }

    return root;
}

int find_nth_largest(Node *root, int n)
{
    if (root == NULL || n <= 0)
    {
        return -1; // Error, invalid input
    }

    int count = 0;
    int result = -1; // Initialize to invalid value

    // In-order traversal, keeping track of count and updating result
    Node *current = root;
    while (current)
    {
        if (current->right)
        {
            current = current->right;
        }
        else
        {
            count++;
            if (count == n)
            {
                result = current->data;
                break;
            }
            current = current->left;
        }
    }

    return result;
}

// Function to find the nth smallest element in BST
void findNthSmallestUtil(struct node *root, int n, int *count, int *result)
{
    if (root == NULL || *count >= n)
        return;

    findNthSmallestUtil(root->right, n, count, result);

    (*count)++;
    if (*count == n)
    {
        *result = root->data;
        return;
    }

    findNthSmallestUtil(root->left, n, count, result);
}

int findNthSmallest(struct node *root, int n)
{
    int count = 0;
    int result = -1;
    findNthSmallestUtil(root, n, &count, &result);
    return result;
}

int main()
{
    Node *root = NULL;

   
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal of the BST: ");
    inorderTraversal(root);
    printf("\n");

    int nth_largest = 3;
    printf("The %dth largest element in the BST: %d\n", nth_largest, findNthLargest(root, nth_largest));

    int nth_smallest = 2;
    printf("The %dth smallest element in the BST: %d\n", nth_smallest, findNthSmallest(root, nth_smallest));

    int delete_key = 30;
    root = deleteNode(root, delete_key);
    printf("Inorder traversal after deleting %d: ", delete_key);
    inorderTraversal(root);
    printf("\n");

    return 0;
}