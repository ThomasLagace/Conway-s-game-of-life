#include <stdio.h>
#include <stdlib.h>

#define ROWS 8
#define COLS 16

enum tiles {
    ALIVE_CELL = 219,
    DEAD_CELL = 32
};

void resetGeneration(char *generation) {
    for (int i = 0; i < ROWS * COLS; i++) {
        generation[i] = ALIVE_CELL;
    }

    generation[2 * ROWS + 1] = 1;
}

void displayGeneration(char *generation) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%p: %c", generation + (i*COLS + j), generation[i * COLS + j]);
        }
        puts("");
    }
}

void swapPointers(char **ptr1, char **ptr2) {
    char *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int main() {
    char *currentGeneration = (char *)malloc(ROWS * COLS * sizeof(char));
    char *nextGeneration = (char *)malloc(ROWS * COLS * sizeof(char));

    resetGeneration(currentGeneration);

    printf("current: %p\nnext: %p\n\n", currentGeneration, nextGeneration);

    char *temp = currentGeneration;
    currentGeneration = nextGeneration;
    nextGeneration = temp;

    printf("current: %p\nnext: %p\n\n", currentGeneration, nextGeneration);

    swapPointers(&currentGeneration, &nextGeneration);

    printf("current: %p\nnext: %p\n", currentGeneration, nextGeneration);
    
    // displayGeneration(currentGeneration);

    free(currentGeneration);
    free(nextGeneration);

    return 0;
}
