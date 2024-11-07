// https://github.com/JoaoLucasAssis/Estrutura_Dados_II
#include <stdio.h>
#include <stdlib.h>

// Ordem da arvore B
#define MAX_DEGREE 4
#define MIN_DEGREE 2

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
	struct Node *child = parent->children[index];  // Filho cheio que serC! dividido
	struct Node *node = CreateNode(child->isLeaf);

	for (int i = 0; i < MAX_DEGREE / 2 - 1; i++) {
		node->keys[i] = child->keys[i + MAX_DEGREE / 2]; // Movendo as chaves de 'child' para 'node'
	}
	if (!child->isLeaf) {
		for (int i = 0; i < MAX_DEGREE / 2; i++) {
			node->children[i] = child->children[i + MAX_DEGREE / 2]; // Movendo os filhos de 'child' para 'node'
		}
	}
	child->numKeys = MAX_DEGREE / 2 - 1; // Atualizando o nC:mero de filhos de 'child'
	node->numKeys = MAX_DEGREE / 2 - 1; // Atualizando o nC:mero de filhos de 'node'

	for (int i = parent->numKeys; i > index; i--) {
		parent->children[i + 1] = parent->children[i]; // Ajustando os filhos do 'parent'
	}
	parent->children[index + 1] = node; // Adicionando o 'node' como filho do 'parent'

	for (int i = parent->numKeys - 1; i >= index; i--) {
		parent->keys[i + 1] = parent->keys[i]; // Ajustando as chaves do 'parent'
	}
	parent->keys[index] = child->keys[MAX_DEGREE / 2 - 1]; // Adicionando o filho do meio de 'child' no 'parent'
	parent->numKeys++; // Atualizando o nC:mero de filhos de 'parent'
}

void InsertNonFull(struct Node *node, int key) {
	int i = node->numKeys - 1;

	if (node->isLeaf) { // Se o nC3 for uma folha, procura o lugar dele na pC!gina e adiciona
		while (i >= 0 && key < node->keys[i]) {
			node->keys[i + 1] = node->keys[i]; // Reordenando as chaves de 'node' para adicionar a nova chave
			i--;
		}
		node->keys[i + 1] = key; // Adiciona a nova chave
		node->numKeys++; // Atualizando o nC:mero de filhos de 'node'
	} else { // Se nC#o for uma folha,
		while (i >= 0 && key < node->keys[i]) {
			i--;
		}
		i++;
		if (node->children[i]->numKeys == MAX_DEGREE - 1) { // Se a pC!gina estiver cheia, C) feito o split
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

void borrowFromPrev(struct Node *node, int idx) {
    struct Node* child = node->children[idx];
    struct Node* sibling = node->children[idx - 1];

    for (int i = child->numKeys - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }
    if (!child->isLeaf) {
        for (int i = child->numKeys; i >= 0; i--) {
            child->children[i + 1] = child->children[i];
        }
    }

    child->keys[0] = node->keys[idx - 1];
    if (!node->isLeaf) {
        child->children[0] = sibling->children[sibling->numKeys];
    }

    node->keys[idx - 1] = sibling->keys[sibling->numKeys - 1];
    sibling->numKeys--;
    child->numKeys++;
}

void borrowFromNext(struct Node *node, int idx) {
    struct Node* child = node->children[idx];
    struct Node* sibling = node->children[idx + 1];

    child->keys[child->numKeys] = node->keys[idx];
    if (!child->isLeaf) {
        child->children[child->numKeys + 1] = sibling->children[0];
    }

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->numKeys; i++) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->numKeys; i++) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    child->numKeys++;
    sibling->numKeys--;
}

void Merge(struct Node *node, int idx) {
	struct Node* child = node->children[idx];
	struct Node* sibling = node->children[idx + 1];

	child->keys[MIN_DEGREE - 1] = node->keys[idx];
	for (int i = 0; i < sibling->numKeys; i++) {
		child->keys[i + MIN_DEGREE] = sibling->keys[i];
	}

	if (!child->isLeaf) {
		for (int i = 0; i <= sibling->numKeys; i++) {
			child->children[i + MIN_DEGREE] = sibling->children[i];
		}
	}

	for (int i = idx + 1; i < node->numKeys; i++) {
		node->keys[i - 1] = node->keys[i];
	}

	for (int i = idx + 2; i <= node->numKeys; i++) {
		node->children[i - 1] = node->children[i];
	}

	child->numKeys += sibling->numKeys + 1;
	node->numKeys--;
	free(sibling);
}

void Fill(struct Node *node, int idx) {
	// Verifica se o filho C  esquerda pode emprestar uma chave
	if (idx != 0 && node->children[idx - 1]->numKeys >= MIN_DEGREE) {
		borrowFromPrev(node, idx); // Empresta uma chave do irmC#o C  esquerda para o "node->children[idx]"
	} else if (idx != node->numKeys && node->children[idx + 1]->numKeys >= MIN_DEGREE) { // Verifica se o filho C  esquerda pode emprestar uma chave
		borrowFromNext(node, idx); // Empresta uma chave do irmC#o C  direita para o "node->children[idx]"
	} else {
		// Se não for possível emprestar uma chave de nenhum irmão,
		// então o filho com menos chaves precisa ser fundido com um dos irmãos
		if (idx != node->numKeys) {
			Merge(node, idx);
		} else {
			Merge(node, idx - 1);
		}
	}
}

int getPred(struct Node *node, int idx) {
	struct Node *current = node->children[idx];
	while (!current->isLeaf) {
		current = current->children[current->numKeys];
	}
	return current->keys[current->numKeys - 1];
}

int getSucc(struct Node *node, int idx) {
	struct Node *current = node->children[idx + 1];
	while (!current->isLeaf) {
		current = current->children[0];
	}
	return current->keys[0];
}

void RemoveLeaf(struct Node *node, int idx) {
	// Desloca todas as chaves C  direita da posiC'C#o da chave removida
	for (int i = idx + 1; i < node->numKeys; i++) {
		node->keys[i - 1] = node->keys[i];
	}
	node->numKeys--;
}

void removeNonLeaf(struct Node *node, int idx) {
	int key = node->keys[idx];

	// Verifica se o filho da esquerda possui chaves suficientes
	if (node->children[idx]->numKeys >= MIN_DEGREE) {
		int pred = getPred(node, idx);
		node->keys[idx] = pred;
		Remove(node->children[idx], pred);
	} else if (node->children[idx + 1]->numKeys >= MIN_DEGREE) { // Verifica se o filho da direita possui chaves suficientes
		int succ = getSucc(node, idx);
		node->keys[idx] = succ;
		Remove(node->children[idx + 1], succ);
	} else {
		Merge(node, idx);
		Remove(node->children[idx], key);
	}
}

void Remove(struct Node *root, int key) {
	if (root == NULL) return;

	int idx = 0;
	// Determina em qual intervalo de chaves a chave a ser removida estC!
	while (idx < root->numKeys && root->keys[idx] < key) {
		idx++;
	}

	// Verifica se a chave foi encontrada no nC3 atual
	if (idx < root->numKeys && root->keys[idx] == key) {
		if (root->isLeaf) {
			RemoveLeaf(root, idx);
		} else {
			removeNonLeaf(root, idx);
		}
	} else {
		if (root->isLeaf) {
			printf("Chave %d nC#o encontrada\n", key);
			return;
		}

		int flag = ((idx == root->numKeys) ? 1 : 0);
		if (root->children[idx]->numKeys < MIN_DEGREE) {
			Fill(root, idx);
		}

		if (flag && idx > root->numKeys) {
			Remove(root->children[idx - 1], key);
		} else {
			Remove(root->children[idx], key);
		}
	}
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
	
	printf("\nRemovendo a chave 6...\n");
    Remove(root, 6);
    PrintTree(root, 0);

	return 0;
}
// https://github.com/JoaoLucasAssis/Estrutura_Dados_II
