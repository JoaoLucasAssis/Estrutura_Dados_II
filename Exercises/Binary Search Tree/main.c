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
  // Se a raiz for NULL, significa que a posição correta foi encontrada; cria um novo nó
  if (root == NULL) {
    return CreateNode(data);
  }

  // Se o valor a ser inserido for menor que o valor do nó atual, insere na subárvore esquerda
  if (root->data > data)
    root->left = InsertBST(root->left, data);
  // Se o valor a ser inserido for maior que o valor do nó atual, insere na subárvore direita
  else if (root->data < data)
    root->right = InsertBST(root->right, data);

  return root;
}

struct Node *RemoveBST(struct Node *root, int data) {
  // Se o nó raiz for NULL, a árvore está vazia ou o valor não foi encontrado
  if (root == NULL) return root;
  
  // Se o valor a ser removido é menor, vá para a subárvore esquerda
  if (root->data > data)
    root->left = RemoveBST(root->left, data);
  // Se o valor a ser removido é maior, vá para a subárvore direita
  else if (root->data < data)
    root->right = RemoveBST(root->right, data);
  else { 
    // Valor encontrado; precisamos remover o nó

    struct Node *aux;
    
    // Caso 1: O nó tem apenas um filho à direita ou nenhum filho
    if (root->left == NULL)
      aux = root->right;
    // Caso 2: O nó tem apenas um filho à esquerda
    else if (root->right == NULL)
      aux = root->left;
    else {
      // Caso 3: O nó tem dois filhos
      // Encontrar o maior valor na subárvore esquerda (prédecessor)
      aux = FindBiggestRight(root->left);
      struct Node *aux2 = root->left;

      // Se o sucessor não for o filho imediato, ajusta os ponteiros
      if (aux != aux2) {
        aux2->right = aux->left;
        aux->left = aux2;
      }

      // Atribui o filho direito do nó a ser removido ao sucessor
      aux->right = root->right;
    }

    // Libera a memória do nó atual
    free(root);
    // Retorna o novo nó que substituirá o nó removido
    return aux;
  }
  
  // Retorna a raiz atualizada
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
