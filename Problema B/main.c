#include <stdio.h>
#include <string.h>

int toInt (char c) {
    return c - '0';
}

char toChar (int c) {
    return c + '0';
}

void reverse (char* str) {
    int i = 0;
    int j = strlen(str) - 1;

    while (i < j) {
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
        i++;
        j--;
    }
}

void rem (char N[]) {
    //contar quantos zeros à esquerda existem
    int k = 0;
    while (N[k] == '0') k++;

    //remover os zeros à esquerda
    if (k > 0) {
        int len = strlen(N) + 1; // +1 para o '\0'
        for (int i = 0; i < len - k; i++) {
            N[i] = N[i + k];
        }
    }
}

void multiplicacao (char n1[], char n2[], char res[]) {
    int len1 = strlen(n1), len2 = strlen(n2), len = len1+len2;
    //inverter as strings numéricas
    reverse(n1); reverse(n2);

    //inicializar aux com {0, 0, 0, ...}
    int aux[len];
    for (int i = 0; i < len; i++) aux[i] = 0;

    //calcular a multiplicação
    for (int i1 = 0; i1 < len1; i1++) {
        for (int i2 = 0; i2 < len2; i2++) {
            int temp = toInt(n1[i1]) * toInt(n2[i2]);
            aux[i1+i2]   += temp;
            aux[i1+i2+1] += aux[i1+i2] /10;
            aux[i1+i2]   =  aux[i1+i2] %10;
        }
    }

    //converter aux numa string em res
    int i;
    for (i = 0; i < len; i++) {
        res[i] = toChar(aux[i]);
    }
    res[i] = '\0';

    //inverter res (para o número ser apresentado no formato correto)
    reverse(res);

    //remover os zeros à esquerda
    rem(res);
}

int compare (char n1[], char n2[]) {
    int len1 = strlen(n1), len2 = strlen(n2);
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    for (int i = 0; i < len1; i++) {
        if (n1[i] > n2[i]) return 1;
        if (n1[i] < n2[i]) return -1;
    }
    return 0;
}

void subprod (char N[], int S, char res[]) {
    char prod[1001]; int len = strlen(N) - S;

    for (int index = 0; index <= len; index++) {
        // Inicializar res com o primeiro elemento de N
        res[0] = N[index];
        res[1] = '\0';

        // Multiplicar recursivamente pelos próximos elementos
        for (int i = 1; i < S; i++) {
            char aux[2];
            aux[0] = N[index + i];
            aux[1] = '\0';
            multiplicacao(res, aux, res);
            if (strlen(res) > strlen(prod)) strcpy(prod, res);
            else if (strlen(res) == strlen(prod)) {
                if (compare(res, prod) > 0) strcpy(prod, res);
            }
        }
    }

    strcpy(res, prod);
}

int main () {
    int C;
    if (scanf("%d", &C) != 1) return 1;

    for (int i = 0; i < C; i++) {
        char N[1001], res[1001]; int S;
        if (scanf(" %s %d", N, &S) != 2) return 1;
        subprod(N, S, res);
       
        for (int j = 0; res[j] != '\0'; j++) {
            printf("%c", res[j]);
        }
        printf("\n");
    }
    
    return 0;
}