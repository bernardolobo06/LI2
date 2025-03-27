/*
Problema C (Comparação de Grupos)
Laboratórios de Informática II (UMinho 24/25) 
(c) Marcos Bernardo da Silva Lobo <a110959@alunos.uminho.pt>, 2025-03-xx

Este programa contém a resolução do Problema C de LI2 (24/25).
*/

//compile with 'gcc -Wall -Wextra -pedantic -O2 -fsanitize=address -o main main.c'

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
    int group;
} Data;

// máximo de grupos  100
// máximo de valores 100
typedef struct {
    int pos[100 * 100];
    int ord[100 * 100];
    int grp[100 * 100];
    int val[100 * 100];
    int fst[100 * 100];
    double rel[100 * 100];
} Table;

int compare(const void *a, const void *b) {
    Data *ea = (Data*)a;
    Data *eb = (Data*)b;
    if (ea->value == eb->value) {
        return ea->group - eb->group;
    }
    return ea->value - eb->value;
}

void process_data(Table *t, int total_values, Data lines[100 * 100]) {
    qsort(lines, total_values, sizeof(Data), compare);
    
    for (int i = 0; i < total_values; i++) {
        t->pos[i] = i;
        t->ord[i] = i + 1;
        t->val[i] = lines[i].value;
        t->grp[i] = lines[i].group;
    }
    
    for (int i = 0; i < total_values; i++) {
        int first = -1, last = -1;
        for (int j = 0; j < total_values; j++) {
            if (t->val[j] == t->val[i]) {
                if (first == -1) first = j;
                last = j;
            }
        }
        t->fst[i] = first;
        t->rel[i] = (first+1 + last+1) / 2.0; //+1 é a ordem. fisrt e last são a pos do array
    }
}

void print_table(Table *t, int total_values) {
    printf(" Pos  Ord  Grp     OrdRel  Val  Prm\n");
    for (int i = 0; i < total_values; i++) {
        printf("%4d %4d %4d %10.1f %4d %4d\n", t->pos[i], t->ord[i], t->grp[i], t->rel[i], t->val[i], t->fst[i]);
    }
}

int main() {
    Table t;
    Data lines[100 * 100]; // ↓
    int total_values, G, N, value, index = 0;
    
    if (scanf("%d", &G) != 1) return 1;
    for (int g = 0; g < G; g++) {
        if (scanf("%d", &N) != 1) return 1;
        for (int i = 0; i < N; i++) {
            if (scanf("%d", &value) != 1) return 1;
            lines[index].value = value;
            lines[index].index = index;
            lines[index].group = g + 1;
            t.grp[index] = g + 1;
            index++;
        }
    }
    total_values = index;

    process_data(&t, total_values, lines);
    print_table(&t, total_values);
    
    return 0;
}
    
// 1. Ordenar os valores mantendo o rastreamento dos grupos
// 2. Calcular as colunas necessárias
// 3. Imprimir a tabela formatada
// 4. Calcular médias e estatísticas
// 5. Comparar X com o valor de referência