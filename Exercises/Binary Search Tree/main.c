#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

struct Node *CreateNode(int data) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));

  if (node != NULL) {
    node->data = data;
    node->left = NULL;
    node->right = NULL;
  }

  return node;
}

struct Node *InsertBST(struct Node *root, int data) {
  if (root == NULL) {
    return CreateNode(data);
  }

  if (root->data > data)
    root->left = InsertBST(root->left, data);
  else if (root->data < data)
    root->right = InsertBST(root->right, data);

  return root;
}

struct Node *SearchBST(struct Node *root, int data) {
  if (root->data > data)
    return SearchBST(root->left, data);
  else if (root->data < data)
    return SearchBST(root->right, data);
  else {
    printf("\nO nó %d foi encontrado.\n", root->data);
    return root;
  }
}

struct Node *FindBiggestRight(struct Node *node) {
  struct Node *aux = node;

  while (aux->right != NULL) {
    aux = aux->right;
  }

  return aux;
}

struct Node *RemoveBST(struct Node *root, int data) {
  if (root == NULL) return root;
  
  if (root->data > data)
    root->left = RemoveBST(root->left, data);
  else if (root->data < data)
    root->right = RemoveBST(root->right, data);
  else {
    struct Node *aux;
    
    if (root->left == NULL)
      aux = root->right;
    else if (root->right == NULL)
      aux = root->left;
    else {
      aux = FindBiggestRight(root->left);
      struct Node *aux2 = root->left;

      if (aux != aux2) {
        aux2->right = aux->left;
        aux->left = aux2;
      }
      aux->right = root->right;
    }

    free(root);
    return aux;
  }
  
  return root;
}

void PrintBST(struct Node *root, int lvl) {
  if (root != NULL) {
    for (int i = 0; i < lvl; i++)
      printf("  ");

    printf("%d\n", root->data);
    PrintBST(root->left, lvl + 1);
    PrintBST(root->right, lvl + 1);
  }
}

int main(void) {
  struct Node *root = NULL;

  root = InsertBST(root, 2);
  root = InsertBST(root, 1);
  root = InsertBST(root, 4);
  root = InsertBST(root, 3);
  root = InsertBST(root, 5);

  PrintBST(root, 0);

  SearchBST(root, 3);

  root = RemoveBST(root, 2);

  PrintBST(root, 0);

  return 0;
}