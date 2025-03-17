#include <stdio.h>

int toInt (char c) {
    return c - '0';
}

int slen (char s[]) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

void copy(int acc[], int max[]) {
    int bool = 0;
    int j = 0;

    while (j < 1000 && bool == 0) {
        if (acc[j] > max[j]) {
            bool = 1;
        } 
        else if (acc[j] < max[j]) {
            return;
        }
        j++;
    }

    if (bool) {
        j = 0;
        while (j < 1000) {
            max[j] = acc[j];
            j++;
        }
    }
}

void convert (int max[], char prods[]) {
    int start = 0;
    while (start < 999 && max[start] == 0) start++;

    int j = 0;
    for (int i = start; i < 1000; i++) {
        prods[j++] = max[i] + '0';
    }
    prods[j] = '\0';
}

void subproduto(char N[], int S, char prods[]) {
    int len = slen(N);
    int max[1000];
    int acc[1000];

    for (int i = 0; i < 1000; i++) {
        max[i] = 0;
        acc[i] = 0;
    }

    for (int i = 0; i <= len - S; i++) {
        for (int j = 0; j < 1000; j++) acc[j] = 0;
        acc[999] = 1;

        for (int j = 0; j < S; j++) {
            int digit = toInt(N[i + j]);
            
            for (int k = len - 1; k > 0; k--) {
                acc[k] *= digit;
                acc[k - 1] += acc[k] / 10; //dezenas
                acc[k] %= 10; //unidades
            }
        }

        copy(acc, max);
    }

    convert (max, prods);
}

int main() {
    char N[1001];
    int C, S;

    if (scanf("%d", &C) != 1) return 1;
    char prods[1001];

    for (int i = 0; i < C; i++) {
        if (scanf(" %s %d", N, &S) != 2) return 1;
        subproduto(N, S, prods);
    }

    for (int i = 0; i < C; i++) {
        printf("%s\n", prods);
    }

    return 0;
}