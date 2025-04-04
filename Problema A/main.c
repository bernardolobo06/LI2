//compile with 'gcc -Wall -Wextra -pedantic -O2'

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
            if (I == 0) {
                multiples[i] = F / factors[i];
            }
            else {
                multiples[i] = (F / factors[i]) - ((I - 1) / factors[i]);
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
    if (scanf("%d", &N) != 1 || N < 1 || N > 26) return 1;

    int factors[N];
    char letters[N];
    for (int i = 0; i < N; i++) {
        if (scanf(" %c %d", &letters[i], &factors[i]) != 2 || letters[i] < 'A' || letters[i] > 'Z' || factors[i] < 0 || factors[i] > 1000000000) return 1;
    }

    int I, F;
    if (scanf("%d %d", &I, &F) != 2 || I < 0 || I > 1000000000 || F < 0 || F > 1000000000) return 1;

    mult(N, letters, factors, I, F);

    return 0;    
}