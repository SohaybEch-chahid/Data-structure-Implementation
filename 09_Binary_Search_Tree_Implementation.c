#include <stdio.h>
#include <stdlib.h>

// ================== STRUCT ==================
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// ================== CREATE NODE ==================
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// ================== INSERT ==================
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// ================== SEARCH ==================
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// ================== FIND MIN ==================
struct Node* findMin(struct Node* root) {
    if (root == NULL)
        return NULL;

    if (root->left == NULL)
        return root;

    return findMin(root->left);
}

// ================== DELETE ==================
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // One child
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // Two children
        else {
            struct Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    return root;
}

// ================== TRAVERSALS ==================
void inorder(struct Node* root) {
    if (root == NULL) return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct Node* root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node* root) {
    if (root == NULL) return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// ================== HEIGHT ==================
int height(struct Node* root) {
    if (root == NULL)
        return 0; // -1 for how many edges

    int left = height(root->left);
    int right = height(root->right);

    return (left > right ? left : right) + 1;
}

// ================== COUNT NODES ==================
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ================== MAIN ==================
int main() {
    struct Node* root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    printf("Inorder: ");
    inorder(root);

    printf("\nPreorder: ");
    preorder(root);

    printf("\nPostorder: ");
    postorder(root);

    int key = 40;
    if (search(root, key))
        printf("\n%d found", key);
    else
        printf("\n%d not found", key);

    printf("\nHeight: %d", height(root));
    printf("\nTotal Nodes: %d", countNodes(root));

    root = deleteNode(root, 50);

    printf("\nAfter deletion (Inorder): ");
    inorder(root);
    printf ("\n");

    return 0;
}
