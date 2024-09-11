#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};

int GetHeight(struct Node *node) {
    if (node == NULL)
        return -1;
    return node->height;
}

int BalanceFactor(struct Node *node) {
    if (node == NULL)
        return 0;
    return GetHeight(node->left) - GetHeight(node->right);
}

int Max(int n1, int n2) {
    return (n1 > n2) ? n1 : n2;
}

struct Node *LeftRotation(struct Node *node) {
    struct Node *aux = node->left;
    node->left = aux->right;
    aux->right = node;

    node->height = Max(GetHeight(node->left), GetHeight(node->right)) + 1;
    aux->height = Max(GetHeight(aux->left), GetHeight(aux->right)) + 1;

    return aux;
}

struct Node *RightRotation(struct Node *node) {
    struct Node *aux = node->right;
    node->right = aux->left;
    aux->left = node;

    node->height = Max(GetHeight(node->left), GetHeight(node->right)) + 1;
    aux->height = Max(GetHeight(aux->left), GetHeight(aux->right)) + 1;

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

void PrintTree(struct Node *node, int lvl) {
    if (node != NULL) {
        for (int i = 0; i < lvl; i++)
            printf("  ");

        printf("%d\n", node->data);
        PrintTree(node->left, lvl + 1);
        PrintTree(node->right, lvl + 1);
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
  root->height = Max(GetHeight(root->left), GetHeight(root->right)) + 1;
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

struct Node *FindBiggestRight(struct Node *node) {
  struct Node *aux = node;

  while (aux->right != NULL) {
    aux = aux->right;
  }

  return aux;
}

struct Node *RemoveNode(struct Node *node) {
  struct Node *aux;
  
  if (node->left == NULL)
    aux = node->right;
  else if (node->right == NULL)
    aux = node->left;
  else {
    aux = FindBiggestRight(node->left);
    struct Node *aux2 = node->left;

    if (aux != aux2) {
      aux2->right = aux->left;
      aux->left = aux2;
    }
    aux->right = node->right;
  }

  free(node);
  return aux;
}

struct Node *RemoveAVL(struct Node *root, int data) {
  // Step 1 - Remoção de árvore BB
  if (root == NULL) return root;
  
  if (root->data > data)
    root->left = RemoveAVL(root->left, data);
  else if (root->data < data)
    root->right = RemoveAVL(root->right, data);
  else
    return RemoveNode(root);
    
  // Step 2 - Balanceamento a cada inserção
  root->height = Max(GetHeight(root->left), GetHeight(root->right)) + 1;
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

  PrintTree(root, 0);
  
  root = RemoveAVL(root, 3);
  root = RemoveAVL(root, 9);
  root = RemoveAVL(root, 18);
  
  PrintTree(root, 0);
  
  return 0;
}
