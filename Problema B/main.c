/*
Problema B (Maior subproduto de algarismos)
Laboratórios de Informática II (UMinho 24/25) 
(c) Marcos Bernardo da Silva Lobo <a110959@alunos.uminho.pt>, 2025-03-21

Este programa contém a resolução do Problema B de LI2 (24/25) e as definições explícitas de várias funções definidas em string.h.
*/

#include <stdio.h>

// Funções auxiliares
int toInt (char c) {
    return c - '0';
}

char toChar (int c) { 
    return c + '0';
}

int slen (char str[]) {
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

void srev (char str[]) {
    int i = 0;
    int j = slen(str) - 1; //ignorar o '\0'

    while (i < j) {
        char c = str[i];
        str[i++] = str[j];
        str[j--] = c;
    }
}

void scpy (char dest[], char orig[]) {
    int i, len = slen(orig) + 1; //contar o '\0'

    //NOTA: a utilização de uma string temporária é necessária para evitar sobrescrição da string original
    
    //copiar a string original para a string temporária
    char temp[len];
    for (i = 0; orig[i] != '\0'; i++)
        temp[i] = orig[i];
    temp[i] = '\0';
    
    //copiar a string temporária para a string destino
    for (i = 0; temp[i] != '\0'; i++)
        dest[i] = temp[i];
    dest[i] = '\0';
}

int scmp (char str1[], char str2[]) {
    int len1 = slen(str1), len2 = slen(str2);

    if (len1 > len2) return 1;              //a primeira string é maior
    if (len1 < len2) return -1;             //a segunda string é maior
    for (int i = 0; i < len1; i++) {        //as strings têm o mesmo tamanho:
        if (str1[i] > str2[i]) return 1;        //o valor da primeira string é maior
        if (str1[i] < str2[i]) return -1;       //o valor da segunda string é maior
    }
    return 0;                               //as strings são iguais
}

// Funções de multiplicação de strings
void remZero (char N[]) {
    //contar quantos zeros à esquerda existem
    int i = 0;
    while (N[i] == '0') i++;

    //remover os zeros à esquerda
    if (i > 0) {
        int len = slen(N) + 1; //contar o '\0'
        for (int j = 0; j < len - i; j++) {
            N[j] = N[j + i];
        }
    }
}

void multiplicacao (char N1[], char N2[], char dest[]) {
    int len1 = slen(N1), len2 = slen(N2), len = len1+len2;

    //NOTA: o algoritmo de multiplicação inicia pelas unidades e termina nas dezenas, centenas, etc.
    //      por isso, as strings são invertidas no início (para iniciar os cálculos pelas unidades)
    //      e no fim da função (para o número ser apresentado com as unidades no fim).

    //inverter as strings numéricas 
    srev(N1); srev(N2);

    //inicializar aux (array de inteiros onde se processa a multiplicação) com 0's
    int aux[len];
    for (int i = 0; i < len; i++) aux[i] = 0;

    //algortimo de multiplicação
    for (int i1 = 0; i1 < len1; i1++) {
        for (int i2 = 0; i2 < len2; i2++) {
            int temp = toInt(N1[i1]) * toInt(N2[i2]); //máximo: 9*9 = 81
            aux[i1+i2]   += temp;
            aux[i1+i2+1] += aux[i1+i2] /10; //dezenas
            aux[i1+i2]   =  aux[i1+i2] %10; //unidades
        }
    }

    //copiar aux para a string dest
    int i;
    for (i = 0; i < len; i++) {
        dest[i] = toChar(aux[i]);
    }
    dest[i] = '\0';

    //inverter a string dest
    srev(dest);

    //remover os zeros à esquerda
    remZero(dest);
}

// Funções do Problema B
void subprod (char N[], int S, char dest[]) {
    int len = slen(N) - S;

    dest[0] = '0'; dest[1] = '\0'; //inicializar o resultado com 0

    for (int index = 0; index <= len; index++) {
        //inicializar N1 com o primeiro elemento de N (primeira unidade)
        char N1[1001];
        N1[0] = N[index]; N1[1] = '\0';

        //multiplicar recursivamente pelos elementos seguintes
        for (int i = 1; i < S; i++) {
            char N2[2]; //algarismo a multiplicar
            N2[0] = N[index + i]; N2[1] = '\0';

            multiplicacao(N1, N2, N1);
        }
        
        //comparar o resultado com o valor atual de dest
        if (scmp(N1, dest) > 0) scpy(dest, N1);
    }
}

int main () {
    int C;
    if (scanf("%d", &C) != 1) return 1;

    char res[C][1001]; //array de strings (com slen = 1000) que guarda o resultado de cada caso
    for (int i = 0; i < C; i++) {
        char N[1001]; int S;
        if (scanf(" %s %d", N, &S) != 2) return 1;
        subprod(N, S, res[i]);
    }

    for (int i = 0; i < C; i++) {
        printf("%s", res[i]);
        printf("\n");
    }
    
    return 0;
}