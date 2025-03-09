//compile with 'gcc -Wall -Wextra -pedantic -O2'

//NOTA: FALTA CRIAR RESTRIÇÕES: SÓ LETRAS MAIÚSCULAS, N [1, 26], factors|I|F [0, 10^9] 

#include <stdio.h>

void sort (int N, char letters[], int multiples[]) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {

            if (letters[i] > letters[j]) {
                char temp_let = letters[i];
                letters[i] = letters[j];
                letters[j] = temp_let;

                int temp_mult = multiples[i];
                multiples[i] = multiples[j];
                multiples[j] = temp_mult;
            }
        }
    }
}

void mult(int N, char letters[], int factors[], int I, int F) {
    int multiples[N];

    if (I > F) {
        for (int i = 0; i < N; i++) {
            multiples[i] = 0;
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            multiples[i] = 0;
            for (int j = I; j <= F; j++) {
                if (j % factors[i] == 0) {
                    multiples[i]++;
                }
            }
        }
    }

    sort(N, letters, multiples);

    for (int i = 0; i < N; i++) {
        printf("%c %d\n", letters[i], multiples[i]);
    }
}

int main () {
    int N;
    scanf("%d", &N);

    int factors[N];
    char letters[N];
    for (int i = 0; i < N; i++) {
        scanf(" %c %d", &letters[i], &factors[i]);
    }

    int I, F;
    scanf("%d %d", &I, &F);

    mult(N, letters, factors, I, F);

    return 0;    
}