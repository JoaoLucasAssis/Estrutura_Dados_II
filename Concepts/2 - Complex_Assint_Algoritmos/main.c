#include<stdio.h>

int eh_primo(int n) {
    if (n <= 1)
        return 0;
    for (int i = 2; i * i <= n; i++) {
        printf("%d %d\n", i, n);
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    printf("%d",eh_primo(7));
    return 0;
}
