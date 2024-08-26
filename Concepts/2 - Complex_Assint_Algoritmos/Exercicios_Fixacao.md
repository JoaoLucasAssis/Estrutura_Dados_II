## Exercício 1: Soma de Elementos
Dado o seguinte algoritmo, determine a complexidade em termos de Big O:
```c
int soma(int vetor[], int n) {
    int soma = 0;
    for (int i = 0; i < n; i++) {
        soma += vetor[i];
    }
    return soma;
}
```
Qual é a complexidade desse algoritmo?

## Exercício 2: Multiplicação de Matrizes
Considere o algoritmo abaixo para multiplicar duas matrizes:
```c
void multiplica_matrizes(int A[][n], int B[][n], int C[][n], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
```
Qual é a complexidade desse algoritmo em termos de n?

## Exercício 3: Busca Binária
Analise a complexidade do seguinte algoritmo de busca binária:
```c
int busca_binaria(int vetor[], int n, int x) {
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (vetor[meio] == x)
            return meio;
        if (vetor[meio] < x)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}
```
Qual é a complexidade do algoritmo de busca binária?

## Exercício 4: Verificação de Número Primo
Dado o algoritmo abaixo que verifica se um número é primo, determine a complexidade:
```c
int eh_primo(int n) {
    if (n <= 1)
        return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}
```
Qual é a complexidade do algoritmo para verificar se um número é primo?

## Exercício 5: Ordenação por Inserção
Analise a complexidade do algoritmo de ordenação por inserção abaixo:
```c
void insertion_sort(int vetor[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}
```
Qual é a complexidade do pior caso para o algoritmo de ordenação por inserção?

## Exercício 6: Fibonacci Recursivo
Considere o seguinte algoritmo recursivo para calcular o n-ésimo número de Fibonacci:
```c
int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
```
Qual é a complexidade do algoritmo recursivo para calcular o n-ésimo número de Fibonacci?

## Exercício 7: Soma Recursiva dos Números de 1 a N
Analise a complexidade do algoritmo recursivo abaixo:
```c
int soma_recursiva(int n) {
    if (n == 1)
        return 1;
    return n + soma_recursiva(n - 1);
}
```
Qual é a complexidade do algoritmo para somar recursivamente os números de 1 a N?

## Exercício 8: Quick Sort
Dado o seguinte algoritmo de Quick Sort, determine sua complexidade no melhor, pior e caso médio:
```c
void quick_sort(int vetor[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particiona(vetor, baixo, alto);
        quick_sort(vetor, baixo, pi - 1);
        quick_sort(vetor, pi + 1, alto);
    }
}
```
Qual é a complexidade do Quick Sort nos três casos (melhor, pior e caso médio)?

## Exercício 9: Contagem de Dígitos
Analise a complexidade do seguinte algoritmo que conta o número de dígitos de um número inteiro:
```c
int conta_digitos(int n) {
    int contagem = 0;
    while (n != 0) {
        n = n / 10;
        contagem++;
    }
    return contagem;
}
```
Qual é a complexidade desse algoritmo para contar o número de dígitos?

## Exercício 10: Merge Sort
Considere o seguinte algoritmo de Merge Sort:
```c
void merge_sort(int vetor[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(vetor, l, m);
        merge_sort(vetor, m + 1, r);
        merge(vetor, l, m, r);
    }
}
```
Qual é a complexidade do algoritmo de Merge Sort?
