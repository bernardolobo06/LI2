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