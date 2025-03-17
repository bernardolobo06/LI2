#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 8
void bufferO() {
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        printf("Error\n");
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    printf(buffer);
}

void pointersAri() {
    int n[] = {10, 20, 30, 40, 50};
    int *ptr = n;
    for (size_t i = 0; i < sizeof(n) / sizeof(n[0]); i++) {
        printf("Element %zu: %d\n", i, *(ptr + i));
    }
}

char* addressSt() {
    char local[16] = "Stack";
    return local;
}


int arrayR() {
    int array[5];
    int i;
    printf("Initial array:\n");
    for (i = 0; i < 10; i++) {
        array[i] = i * i;
        printf("array[%d] = %d\n", i, array[i]);
    }
}

int main() {
    char *ptr2;

    //ptr2 = 
    //printf("Address: %i\n", *ptr2);

    return 0;
}