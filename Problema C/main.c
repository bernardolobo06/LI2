/*
Problema C (Comparação de Grupos)
Laboratórios de Informática II (UMinho 24/25) 
(c) Marcos Bernardo da Silva Lobo <a110959@alunos.uminho.pt>, 2025-03-xx
(c) Maria Inês da Cruz Machado    <a111464@alunos.uminho.pt>, 2025-03-xx
(c) Débora Luana Pinto Caetano    <a112332@alunos.uminho.pt>, 2025-03-xx

Este programa contém a resolução do Problema C de LI2 (24/25).
*/


// -fsanatize=address

#include <stdio.h>
#include <stdlib.h>

typedef struct group {
    int pos[10000];
    int ord[10000];
    int grp[100];
    int rel[10000];
    int val[10000];
    int fst[10000];
} group;