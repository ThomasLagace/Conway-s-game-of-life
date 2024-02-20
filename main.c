#include <stdio.h>
#include <stdlib.h>

#define ROWS 8
#define COLS 8

enum tiles {
    ALIVE_CELL = 219,
    DEAD_CELL = 176
};

void resetGeneration(unsigned char *generation) {
    for (int i = 0; i < ROWS * COLS; i++) {
        generation[i] = DEAD_CELL;
    }

    generation[2 * COLS + 3] = ALIVE_CELL;
    generation[3 * COLS + 4] = ALIVE_CELL;

    generation[4 * COLS + 2] = ALIVE_CELL;
    generation[4 * COLS + 3] = ALIVE_CELL;
    generation[4 * COLS + 4] = ALIVE_CELL;
}

void displayGeneration(unsigned char *generation) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf(" (%d, %d): %c", j, i, generation[i * COLS + j]);
        }
        puts("");
    }
}

void swapPointers(void **ptr1, void **ptr2) {
    void *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

unsigned char getAdjacentLiveCells(unsigned char *generation, int x, int y) {
    unsigned char liveCells = 0;
    for (char i = -1; i < 2; i++) {
        for (char j = -1; j < 2; j++) {
            if ((x == 0 && i < 0 || x == COLS && i > 0)
                || (y == 0 && j < 0 || y == ROWS && j > 0)) {
                continue;
            } else if (generation[(y + i) * COLS + (x + j)] == ALIVE_CELL) {
                liveCells++;
            }
        }
    }
    
    return liveCells;
}

void calculateNextGeneration(unsigned char *currentGeneration, unsigned char *nextGeneration) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            unsigned char liveCells = getAdjacentLiveCells(currentGeneration, j, i);
            printf("(%d, %d): %d\n", j, i, liveCells);
            if (liveCells < 2
                || liveCells > 3) {
                nextGeneration[i * COLS + j] = DEAD_CELL;
            } else if (currentGeneration[i * COLS + j] == DEAD_CELL && liveCells == 3) {
                nextGeneration[i * COLS + j] = ALIVE_CELL;
            } else if (currentGeneration[i * COLS + j] == ALIVE_CELL && liveCells == 2
                       || currentGeneration[i * COLS + j] == ALIVE_CELL && liveCells == 3) {
                nextGeneration[i * COLS + j] = ALIVE_CELL;
            }
        }
    }
}

int main() {
    unsigned char *currentGeneration = (unsigned char *)malloc(ROWS * COLS * sizeof(char));
    unsigned char *nextGeneration = (unsigned char *)malloc(ROWS * COLS * sizeof(char));

    resetGeneration(currentGeneration);
    resetGeneration(nextGeneration);

    for (int i = 0; i < 20; i++)
    {
        displayGeneration(currentGeneration);

        calculateNextGeneration(currentGeneration, nextGeneration);

        swapPointers((void **)&currentGeneration, (void **)&nextGeneration);
        
        puts("");
        
        getchar();
    }

    free(currentGeneration);
    free(nextGeneration);

    return 0;
}
