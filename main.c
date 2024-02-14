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

int main() {
    char *currentGeneration = (char *)malloc(ROWS * COLS * sizeof(char));
    char *nextGeneration = (char *)malloc(ROWS * COLS * sizeof(char));

    resetGeneration(currentGeneration);

    
    displayGeneration(currentGeneration);

    free(currentGeneration);
    free(nextGeneration);

    return 0;
}
