#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};

int getHeight(struct Node *node) {
    if (node == NULL)
        return -1;
    return node->height;
}

int BalanceFactor(struct Node *node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

int Max(int n1, int n2) {
    return (n1 > n2) ? n1 : n2;
}

struct Node *LeftRotation(struct Node *node) {
    struct Node *aux = node->left;
    node->left = aux->right;
    aux->right = node;

    node->height = Max(getHeight(node->left), getHeight(node->right)) + 1;
    aux->height = Max(getHeight(aux->left), getHeight(aux->right)) + 1;

    return aux;
}

struct Node *RightRotation(struct Node *node) {
    struct Node *aux = node->right;
    node->right = aux->left;
    aux->left = node;

    node->height = Max(getHeight(node->left), getHeight(node->right)) + 1;
    aux->height = Max(getHeight(aux->left), getHeight(aux->right)) + 1;

    return aux;
}

struct Node *CreateNode(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));

    if (node != NULL) {
        node->data = data;
        node->height = 0;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

// Função para imprimir a árvore
void printTree(struct Node *node, int lvl) {
    if (node != NULL) {
        for (int i = 0; i < lvl; i++)
            printf("  ");

        printf("%d\n", node->data);
        printTree(node->left, lvl + 1);
        printTree(node->right, lvl + 1);
    }
}

struct Node *InsertAVL(struct Node *root, int data) {
    // Step 1 - Inserção de árvore BB
    if (root == NULL)
        return CreateNode(data);

    if (data < root->data)
        root->left = InsertAVL(root->left, data);
    else if (data > root->data)
        root->right = InsertAVL(root->right, data);

    // Step 2 - Balanceamento a cada inserção
    root->height = Max(getHeight(root->left), getHeight(root->right)) + 1;
    int bf = BalanceFactor(root);

    if (bf > 1) {
        if (data < root->left->data)
            return LeftRotation(root);
        else {
            root->left = RightRotation(root->left);
            return LeftRotation(root);
        }
    } else if (bf < -1) {
        if (data > root->right->data)
            return RightRotation(root);
        else {
            root->right = LeftRotation(root->right);
            return RightRotation(root);
        }
    }

    return root;
}

int main() {
    struct Node *root = NULL;

    int v[7] = {30, 9, 45, 27, 3, 18, 35};
    
    for (int i = 0; i < 7; i++) {
        root = InsertAVL(root, v[i]);
    }

    printTree(root, 0);
    return 0;
}