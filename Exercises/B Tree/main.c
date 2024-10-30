// https://github.com/JoaoLucasAssis/Estrutura_Dados_II
#include <stdio.h>
#include <stdlib.h>

// Ordem da árvore B
#define MAX_DEGREE 4 

struct Node {
    int isLeaf;
    int numKeys;
    int keys[MAX_DEGREE - 1];
    struct Node *children[MAX_DEGREE];
};

struct Node *CreateNode(int isLeaf) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    for (int i = 0; i < MAX_DEGREE; i++)
        node->children[i] = NULL;
    return node;
}

void SplitChild(struct Node *parent, int index) {
    struct Node *child = parent->children[index];  // Filho cheio que será dividido
    struct Node *node = CreateNode(child->isLeaf);

    for (int i = 0; i < MAX_DEGREE / 2 - 1; i++) {
        node->keys[i] = child->keys[i + MAX_DEGREE / 2]; // Movendo as chaves de 'child' para 'node'
    }
    if (!child->isLeaf) {
        for (int i = 0; i < MAX_DEGREE / 2; i++) {
            node->children[i] = child->children[i + MAX_DEGREE / 2]; // Movendo os filhos de 'child' para 'node'
        }
    }
    child->numKeys = MAX_DEGREE / 2 - 1; // Atualizando o número de filhos de 'child'
    node->numKeys = MAX_DEGREE / 2 - 1; // Atualizando o número de filhos de 'node'

    for (int i = parent->numKeys; i > index; i--) {
        parent->children[i + 1] = parent->children[i]; // Ajustando os filhos do 'parent'
    }
    parent->children[index + 1] = node; // Adicionando o 'node' como filho do 'parent'

    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i]; // Ajustando as chaves do 'parent'
    }
    parent->keys[index] = child->keys[MAX_DEGREE / 2 - 1]; // Adicionando o filho do meio de 'child' no 'parent'
    parent->numKeys++; // Atualizando o número de filhos de 'parent'
}

void InsertNonFull(struct Node *node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) { // Se o nó for uma folha, procura o lugar dele na página e adiciona
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i]; // Reordenando as chaves de 'node' para adicionar a nova chave
            i--;
        }
        node->keys[i + 1] = key; // Adiciona a nova chave
        node->numKeys++; // Atualizando o número de filhos de 'node'
    } else { // Se não for uma folha, 
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->numKeys == MAX_DEGREE - 1) { // Se a página estiver cheia, é feito o split
            SplitChild(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        InsertNonFull(node->children[i], key);
    }
}

struct Node *Insert(struct Node *root, int key) {
    if (root == NULL) {
        root = CreateNode(1);
        root->keys[0] = key;
        root->numKeys = 1;
    } else {
        if (root->numKeys == MAX_DEGREE - 1) {
            struct Node *newRoot = CreateNode(0);
            newRoot->children[0] = root;
            SplitChild(newRoot, 0);
            int i = 0;
            if (key > newRoot->keys[0]) {
                i++;
            }
            InsertNonFull(newRoot->children[i], key);
            root = newRoot;
        } else {
            InsertNonFull(root, key);
        }
    }
    return root;
}

void PrintTree(struct Node *node, int level) {
    if (node != NULL) {
        for (int i = 0; i < level; i++)
            printf("  ");
        for (int i = 0; i < node->numKeys; i++)
            printf("%d ", node->keys[i]);
        printf("\n");

        for (int i = 0; i <= node->numKeys; i++) {
            PrintTree(node->children[i], level + 1);
        }
    }
}

int main() {
    struct Node *root = NULL;

    root = Insert(root, 10);
    root = Insert(root, 20);
    root = Insert(root, 5);
    root = Insert(root, 6);
    root = Insert(root, 12);
    root = Insert(root, 30);
    root = Insert(root, 7);
    root = Insert(root, 17);

    PrintTree(root, 0);

    return 0;
}
// https://github.com/JoaoLucasAssis/Estrutura_Dados_II
