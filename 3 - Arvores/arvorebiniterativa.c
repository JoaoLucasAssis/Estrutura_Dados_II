#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída
#include <stdlib.h>  // Inclui a biblioteca padrão de alocação de memória

// Estrutura de um nó da árvore binária
typedef struct NoArvore {
    int dado;            // Valor armazenado no nó
    struct NoArvore* esquerda;  // Ponteiro para o filho à esquerda
    struct NoArvore* direita;   // Ponteiro para o filho à direita
} NoArvore;

// Estrutura para a pilha usada nas travessias iterativas
typedef struct Pilha {
    NoArvore* no;       // Ponteiro para um nó da árvore
    struct Pilha* topo;   // Ponteiro para o próximo elemento da pilha
} Pilha;

// Função para criar um novo nó
NoArvore* criarNo(int dado) {
    NoArvore* novoNo = (NoArvore*)malloc(sizeof(NoArvore));  // Aloca memória para um novo nó
    if (novoNo == NULL) {  // Verifica se a alocação foi bem-sucedida
        printf("Erro: Falha na alocação de memória.\n");
        return NULL;  // Retorna NULL em caso de falha
    }
    novoNo->dado = dado;        // Atribui o valor ao novo nó
    novoNo->esquerda = NULL;    // Inicializa o ponteiro esquerdo como NULL
    novoNo->direita = NULL;     // Inicializa o ponteiro direito como NULL
    return novoNo;  // Retorna o ponteiro para o novo nó
}

// Função para inserir elementos na árvore balanceada a partir de um vetor ordenado
NoArvore* inserirElementos(int vetor[], int inicio, int fim) {
    if (inicio > fim)  // Caso base: se a sublista é inválida, retorna NULL
        return NULL;

    int meio = (inicio + fim) / 2;           // Calcula o índice do meio do vetor
    NoArvore* novoNo = criarNo(vetor[meio]); // Cria um nó com o valor do meio

    // Insere recursivamente os elementos na subárvore esquerda
    novoNo->esquerda = inserirElementos(vetor, inicio, meio - 1);
    
    // Insere recursivamente os elementos na subárvore direita
    novoNo->direita = inserirElementos(vetor, meio + 1, fim);
    
    return novoNo;  // Retorna o ponteiro para o nó criado
}

// Função para buscar um elemento na árvore
NoArvore* buscarElemento(NoArvore* raiz, int dado) {
    if (raiz == NULL || raiz->dado == dado) {
        // Retorna a raiz se a árvore estiver vazia ou se encontrar o valor
        return raiz;
    }

    if (dado < raiz->dado) {  // Se o valor buscado for menor, busca na subárvore esquerda
        return buscarElemento(raiz->esquerda, dado);
    } else {  // Caso contrário, busca na subárvore direita
        return buscarElemento(raiz->direita, dado);
    }
}

// Função para encontrar o menor valor em uma subárvore
struct NoArvore *encontrarMinimo(struct NoArvore *raiz)
{
    struct NoArvore *atual = raiz;
    // Itera até encontrar o nó mais à esquerda (menor valor)
    while (atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }
    return atual;  // Retorna o nó com o menor valor
}

// Função para excluir um nó da árvore
struct NoArvore *excluir(struct NoArvore *raiz, int dado)
{
    if (raiz == NULL)  // Se a árvore estiver vazia, retorna NULL
    {
        return raiz;
    }

    if (dado < raiz->dado)  // Se o valor for menor, exclui na subárvore esquerda
    {
        raiz->esquerda = excluir(raiz->esquerda, dado);
    }
    else if (dado > raiz->dado)  // Se o valor for maior, exclui na subárvore direita
    {
        raiz->direita = excluir(raiz->direita, dado);
    }
    else  // Se o nó a ser excluído for encontrado
    {
        // Caso 1: Nó folha ou nó com apenas um filho
        if (raiz->esquerda == NULL)
        {
            struct NoArvore *temp = raiz->direita;  // Armazena o filho direito
            free(raiz);  // Libera a memória do nó atual
            return temp;  // Retorna o filho direito
        }
        else if (raiz->direita == NULL)
        {
            struct NoArvore *temp = raiz->esquerda;  // Armazena o filho esquerdo
            free(raiz);  // Libera a memória do nó atual
            return temp;  // Retorna o filho esquerdo
        }

        // Caso 2: Nó com dois filhos, encontra o sucessor in-order (menor valor na subárvore direita)
        struct NoArvore *temp = encontrarMinimo(raiz->direita);  // Encontra o menor valor na subárvore direita
        raiz->dado = temp->dado;  // Substitui o valor do nó a ser excluído pelo sucessor
        raiz->direita = excluir(raiz->direita, temp->dado);  // Exclui o sucessor in-order
    }
    return raiz;  // Retorna a nova raiz da subárvore
}

// Função para push um nó
void push(Pilha** topo, NoArvore* no) {
    Pilha* novaPilha = (Pilha*)malloc(sizeof(Pilha));  // Aloca memória para um novo elemento da pilha
    novaPilha->no = no;  // Atribui o nó ao elemento da pilha
    novaPilha->topo = *topo;  // Ajusta o ponteiro próximo para o antigo topo
    *topo = novaPilha;  // Atualiza o topo da pilha
}

// Função para pop um nó
NoArvore* pop(Pilha** topo) {
    if (*topo == NULL) {  // Verifica se a pilha está vazia
        return NULL;
    }
    Pilha* temp = *topo;        // Armazena o topo atual temporariamente
    *topo = (*topo)->topo;       // Atualiza o topo para o próximo elemento
    NoArvore* desempilhado = temp->no;  // Armazena o nó do elemento desempilhado
    free(temp);  // Libera a memória do elemento desempilhado
    return desempilhado;  // Retorna o nó desempilhado
}

// Travessia Pré-Ordem Recursiva
void preOrdemRec(NoArvore* raiz) {
    if (raiz != NULL) {  // Se o nó não é nulo
        printf("%d ", raiz->dado);  // Imprime o valor do nó
        preOrdemRec(raiz->esquerda);  // Visita recursivamente a subárvore esquerda
        preOrdemRec(raiz->direita);   // Visita recursivamente a subárvore direita
    }
}

// Travessia Em Ordem Recursiva
void emOrdemRec(NoArvore* raiz) {
    if (raiz != NULL) {  // Se o nó não é nulo
        emOrdemRec(raiz->esquerda);  // Visita recursivamente a subárvore esquerda
        printf("%d ", raiz->dado);  // Imprime o valor do nó
        emOrdemRec(raiz->direita);   // Visita recursivamente a subárvore direita
    }
}

// Travessia Pós-Ordem Recursiva
void posOrdemRec(NoArvore* raiz) {
    if (raiz != NULL) {  // Se o nó não é nulo
        posOrdemRec(raiz->esquerda);  // Visita recursivamente a subárvore esquerda
        posOrdemRec(raiz->direita);   // Visita recursivamente a subárvore direita
        printf("%d ", raiz->dado);   // Imprime o valor do nó
    }
}

// Travessia Pré-Ordem Iterativa
void preOrdemIt(NoArvore* raiz) {
    if (raiz == NULL) return;  // Se a árvore estiver vazia, retorna
    
    Pilha* pilha = NULL;  // Inicializa uma pilha vazia
    push(&pilha, raiz);  // Empilha o nó raiz
    
    while (pilha != NULL) {  // Enquanto a pilha não estiver vazia
        NoArvore* atual = pop(&pilha);  // Desempilha o nó do topo
        printf("%d ", atual->dado);      // Imprime o valor do nó
        
        // Empilha o nó direito se ele existir
        if (atual->direita != NULL) {
            push(&pilha, atual->direita);
        }
        // Empilha o nó esquerdo se ele existir
        if (atual->esquerda != NULL) {
            push(&pilha, atual->esquerda);
        }
    }
}

// Travessia Em Ordem Iterativa
void emOrdemIt(NoArvore* raiz) {
    Pilha* pilha = NULL;  // Inicializa uma pilha vazia
    NoArvore* atual = raiz;  // Começa pelo nó raiz
    
    while (atual != NULL || pilha != NULL) {  // Enquanto houver nós a processar
        // Vai até o nó mais à esquerda da subárvore
        while (atual != NULL) {
            push(&pilha, atual);
            atual = atual->esquerda;
        }
        
        // Processa o nó no topo da pilha
        atual = pop(&pilha);
        printf("%d ", atual->dado);
        
        // Move-se para a subárvore direita
        atual = atual->direita;
    }
}

// Travessia Pós-Ordem Iterativa
void posOrdemIt(NoArvore* raiz) {
    if (raiz == NULL) return;  // Se a árvore estiver vazia, retorna
    
    Pilha* pilha1 = NULL;  // Inicializa a primeira pilha
    Pilha* pilha2 = NULL;  // Inicializa a segunda pilha
    push(&pilha1, raiz);  // Empilha a raiz na primeira pilha
    
    // Processa todos os nós
    while (pilha1 != NULL) {
        NoArvore* atual = pop(&pilha1);  // Desempilha o nó do topo da primeira pilha
        push(&pilha2, atual);  // Empilha o nó na segunda pilha
        
        // Empilha os filhos esquerdo e direito na primeira pilha
        if (atual->esquerda != NULL) {
            push(&pilha1, atual->esquerda);
        }
        if (atual->direita != NULL) {
            push(&pilha1, atual->direita);
        }
    }
    
    // Imprime os nós na ordem da segunda pilha
    while (pilha2 != NULL) {
        NoArvore* atual = pop(&pilha2);
        printf("%d ", atual->dado);
    }
}

// Função principal para testar o código
int main() {
    int vetor[] = {1, 2, 3, 4, 5, 6, 7};  // Vetor ordenado de entrada
    int n = sizeof(vetor) / sizeof(vetor[0]);  // Calcula o tamanho do vetor
    
    // Cria uma árvore balanceada a partir do vetor ordenado
    NoArvore* raiz = inserirElementos(vetor, 0, n - 1);
    
    // Testa as funções de travessia recursiva
    printf("Travessia Pré-Ordem Recursiva: ");
    preOrdemRec(raiz);
    printf("\n");
    
    printf("Travessia Em Ordem Recursiva: ");
    emOrdemRec(raiz);
    printf("\n");
    
    printf("Travessia Pós-Ordem Recursiva: ");
    posOrdemRec(raiz);
    printf("\n");
    
    // Testa as funções de travessia iterativa
    printf("Travessia Pré-Ordem Iterativa: ");
    preOrdemIt(raiz);
    printf("\n");
    
    printf("Travessia Em Ordem Iterativa: ");
    emOrdemIt(raiz);
    printf("\n");
    
    printf("Travessia Pós-Ordem Iterativa: ");
    posOrdemIt(raiz);
    printf("\n");

    return 0;  // Finaliza o programa
}
