//compile with 'gcc -Wall -Wextra -pedantic -O2 -fsanitize=address -lm -o main main.c'

/*
Problema C (Comparação de Grupos)
Laboratórios de Informática II (UMinho 24/25) 
(c) Marcos Bernardo da Silva Lobo <a110959@alunos.uminho.pt>, 2025-03-xx

Este programa contém a resolução do Problema C de LI2 (24/25).
*/

#include <stdio.h>
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
int partition (Data *lines, int N, int pivot) {
    int i = 0, j = 0, r = 0;
    Data aux[N];
    for (i = 0; i < N; i++) {
        if (pivot > lines[i].value || (pivot == lines[i].value && lines[i].group < lines[N].group)) {
            aux[j++] = lines[i];
            r++;
        }
    }
    for (i = 0; i < N; i++) {
        if (pivot < lines[i].value || (pivot == lines[i].value && lines[i].group >= lines[N].group)) {
            aux[j++] = lines[i];
        }
    }
    for (i = 0; i < N; i++) {
        lines[i] = aux[i];
    }
    return r;
}

void swap(Data *lines, int i, int j) {
    Data temp = lines[i];
    lines[i].value = lines[j].value;
    lines[i].group = lines[j].group;
    lines[j].value = temp.value;
    lines[j].group = temp.group;
}

void quicksort (Data *lines, int N) {
    int p;
    if (N > 1) {
        p = partition(lines, N - 1, lines[N - 1].value);
        swap(lines, p, N - 1);
        quicksort(lines, p);
        quicksort(lines + p + 1, N - p - 1);
    }
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
void print_table (Table *t, int cont, Data lines[]) {
    quicksort (lines, cont);
    //ordena os valores de 'lines' com 'cont' elementos de tamanho 'sizeof(Data)' usando a função 'compare'
    
    for (int i = 0; i < cont; i++) {
        t -> pos[i] = i;              //posição no array
        t -> ord[i] = i + 1;          //ordem
        t -> val[i] = lines[i].value; //valor
        t -> grp[i] = lines[i].group; //grupo
    }
    
    //passa uma vez por cada valor
    for (int i = 0; i < cont; i++) {
        int first = -1, last = -1;
        for (int j = 0; j < cont; j++) { //segunda passagem para verificar todos os valores j superiores i
            if (t -> val[j] == t -> val[i]) {
                if (first == -1) first = j; //índice do primeiro valor igual
                last = j; //índice do último valor igual
            }
        }
        t -> fst[i] = first;
        t -> rel[i] = (++first + ++last) / 2.0; //incrementar o índice = ordem
    }
    
    printf(" Pos  Ord  Grp     OrdRel  Val  Prm\n");
    for (int i = 0; i < cont; i++) {
        printf("%4d %4d %4d %10.1f %4d %4d\n", 
        t -> pos[i], t -> ord[i], t -> grp[i], t -> rel[i], t -> val[i], t -> fst[i]);
    }
}

void print1 (int G, int count[], double sum[], double total_sum, int total_count) {
    printf("\n  Grp MediaOrdem\n");
    for (int g = 1; g <= G; g++) {
        if (count[g] > 0) {
            printf(" %4d %10.1f\n", g, sum[g] / count[g]);
        }
    }
    printf("Todos %10.1f\n", total_sum / total_count);
}

// Cálculo e impressão das médias por grupo
void print_group_avg(Table *t, int cont, int G) {
    double sum[101] = {0}; 
    int count[101] = {0}; 
    double total_sum = 0;
    int total_count = 0;
    
    for (int i = 0; i < cont; i++) {
        sum[t->grp[i]] += t->rel[i];
        count[t->grp[i]]++;
        total_sum += t->rel[i];
        total_count++;
    }
    
    print1 (G, count, sum, total_sum, total_count);

    double media_total = total_sum / total_count;

    // Cálculo de S e X
    double S = 0;
    for (int g = 1; g <= G; g++) {
        if (count[g] > 0) {
            double media_g = sum[g] / count[g];
            S += count[g] * pow(media_g - media_total, 2);
        }
    }
    double X = ((total_count - 1.0) / total_count) * (12 * S / (total_count * total_count - 1));
    double ref = valor_referencia(G);
    
    // Impressão dos resultados
    printf("\nCalc: %.2f\n", X);
    printf(" Ref: %.2f\n", ref);
    printf("%s\n", (X >= ref) ? "Sim" : "Nao");
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
            index++;
        }
    }
    cont = index;

    print_table(&table, cont, lines);
    print_group_avg(&table, cont, G);
    
    return 0;
}
