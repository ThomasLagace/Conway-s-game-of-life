#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3

enum tiles {
    ALIVE_CELL = 219,
    DEAD_CELL = 176
};

void resetGeneration(char *generation) {
    for (int i = 0; i < ROWS * COLS; i++) {
        generation[i] = i;
    }
}

void displayGeneration(char *generation) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d:", generation[i * COLS + j]);
        }
        puts("");
    }
}

void swapPointers(void **ptr1, void **ptr2) {
    void *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void calculateNextGeneration(char *currentGeneration, char *nextGeneration) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            
        }
    }
    puts("\n");
}

int main() {
    char *currentGeneration = (char *)malloc(ROWS * COLS * sizeof(char));
    char *nextGeneration = (char *)malloc(ROWS * COLS * sizeof(char));

    resetGeneration(currentGeneration);

    calculateNextGeneration(currentGeneration, nextGeneration);

    displayGeneration(currentGeneration);

    free(currentGeneration);
    free(nextGeneration);

    return 0;
}
