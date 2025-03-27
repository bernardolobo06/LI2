/*
Problema C (Comparação de Grupos)
Laboratórios de Informática II (UMinho 24/25) 
(c) Marcos Bernardo da Silva Lobo <a110959@alunos.uminho.pt>, 2025-03-xx

Este programa contém a resolução do Problema C de LI2 (24/25).
*/

//compile with 'gcc -Wall -Wextra -pedantic -O2 -fsanitize=address -o main main.c'

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Data {
    int value;
    int index;
    int group;
} Data;

// máximo de grupos  100
// máximo de valores 100
typedef struct Table {
    int pos[100 * 100];
    int ord[100 * 100];
    int grp[100 * 100];
    int val[100 * 100];
    int fst[100 * 100];
    double rel[100 * 100];
} Table;

//auxiliar functions
int compare (Data *a, Data *b) {
    Data *a1 = a;
    Data *b1 = b;
    if (a1 -> value == b1 -> value) {
        return a1 -> group - b1 -> group;
    }
    return a1 -> value - b1 -> value;
}

double valor_referencia (int num_grupos) {
    double p = 0.95;
    double df = num_grupos - 1;
    double a = (p < 0.5) ?  sqrt(-2.0 * log(p)) : sqrt(-2.0 * log(1.0 - p));
    double poly = 2.515517 + 0.802853 * a + 0.010328 * a * a;
    double q = 1.0 + 1.432788 * a + 0.189269 * a * a + 0.001308 * a * a * a;
    double z = (p < 0.5) ? -(a - poly / q) : (a - poly / q);
    double x = df * pow(1.0 - 2.0 / (9.0 * df) + z * sqrt(2.0 / (9.0 * df)), 3.0);
    return x;
}

//main functions
void process (Table *t, int cont, Data lines[]) {
    qsort (lines, cont, sizeof(Data), compare);
    //ordena os valores de 'lines' com 'cont' elementos de tamanho 'sizeof(Data)' usando a função 'compare'
    
    for (int i = 0; i < cont; i++) {
        t -> pos[i] = i;              //posição no array
        t -> ord[i] = i + 1;          //ordem
        t -> val[i] = lines[i].value; //valor
        t -> grp[i] = lines[i].group; //grupo
    }
    
    for (int i = 0; i < cont; i++) {
        int first = -1, last = -1;
        for (int j = 0; j < cont; j++) {
            if (t -> val[j] == t -> val[i]) {
                if (first == -1) first = j;
                last = j;
            }
        }
        t -> fst[i] = first;
        t -> rel[i] = (++first + ++last) / 2.0; //incrementar o índice = ordem
    }
}

void print (Table *t, int cont) {
    printf(" Pos  Ord  Grp     OrdRel  Val  Prm\n");
    for (int i = 0; i < cont; i++) {
        printf("%4d %4d %4d %10.1f %4d %4d\n", 
        t -> pos[i], t -> ord[i], t -> grp[i], t -> rel[i], t -> val[i], t -> fst[i]);
    }
}

int main () {
    Table table;
    Data lines[100 * 100];
    int cont, G, N, value, index = 0;
    
    if (scanf("%d", &G) != 1) return 1;
    for (int g = 0; g < G; g++) {
        if (scanf("%d", &N) != 1) return 1;
        for (int i = 0; i < N; i++) {
            if (scanf("%d", &value) != 1) return 1;
            lines[index].value = value;
            lines[index].index = index;
            lines[index].group = g + 1;
            table.grp[index] = g + 1;
            index++;
        }
    }
    cont = index;

    process (&table, cont, lines);
    print (&table, cont);
    
    return 0;
}