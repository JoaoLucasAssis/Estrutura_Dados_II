// https://github.com/JoaoLucasAssis/Estrutura_Dados_II
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

struct Node {
  int key;
  int prior;
  struct Node *left;
  struct Node *right;
};

struct Node *CreateNode(int key) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));

  if (node != NULL) {
    node->key = key;
    node->prior = rand() % 100;
    node->left = NULL;
    node->right = NULL;
  }

  return node;
}

void Return() {printf("Made by github.com/JoaoLucasAssis");}

struct Node *RightRotation(struct Node *node) {
    struct Node *aux = node->left; // aux recebe o nó com maior prioridade
    struct Node *aux2 = aux->right; // aux2 recebe a sub-árvore da direita de aux
    
    aux->right = node;
    node->left = aux2;
    
    return aux;
}

struct Node *LeftRotation(struct Node *node) {
    struct Node *aux = node->right; // aux recebe o nó com maior prioridade
    struct Node *aux2 = aux->left; // aux2 recebe a sub-árvore da esquerda de aux
    
    aux->left = node;
    node->right = aux2;
    
    return aux;
}

struct Node *InsertTreap(struct Node *root, int key) {
  if (root == NULL) {
    return CreateNode(key);
  }

  if (root->key > key) {
    root->left = InsertTreap(root->left, key);
    if (root->left != NULL && root->left->prior > root->prior)
        root = RightRotation(root);
  } else if (root->key < key) {
    root->right = InsertTreap(root->right, key);
    if (root->right != NULL && root->right->prior > root->prior)
        root = LeftRotation(root);
  }

  return root;
}

struct Node *RemoveNode(struct Node *node) {
  struct Node *aux;
  
  if (node->left == NULL)
    aux = node->right;
  else if (node->right == NULL)
    aux = node->left;
  else {
    if (node->left->prior > node->right->prior) {
        node = RightRotation(node);
        node->right = RemoveNode(node->right);
    } else {
        node = LeftRotation(node);
        node->left = RemoveNode(node->left);
    }
    return node;
  }

  free(node);
  return aux;
}

struct Node *RemoveTreap(struct Node *root, int key) {
    if (root == NULL) return root;
    
    if (root->key > key)
        root->left = RemoveTreap(root->left, key);
    else if (root->key < key)
        root->right = RemoveTreap(root->right, key);
    else
        return RemoveNode(root);
    
    return root;
}

void PrintTree(struct Node *node, int lvl) {
    if (node != NULL) {
        for (int i = 0; i < lvl; i++)
            printf("  ");

        printf("%d(%d)\n ", node->key, node->prior);
        PrintTree(node->left, lvl + 1);
        PrintTree(node->right, lvl + 1);
    }
}

int main()
{
    srand(time(NULL));
    
    struct Node *root = NULL;
    
    int v[7] = {30, 9, 45, 27, 3, 18, 35};
    
    for (int i = 0; i < 7; i++) {
        root = InsertTreap(root, v[i]);
    }
    
    PrintTree(root, 0);
    
    printf("\nRemoção do 18\n\n");
    
    root = RemoveTreap(root, 18);
  
    PrintTree(root, 0);

    Return();
}
