#include <stdio.h>
#include <stdlib.h>

#define ROWS 50
#define COLS 50

enum tiles {
    ALIVE_CELL = 219,
    DEAD_CELL = 176
};

unsigned char getAdjacentLiveCells(unsigned char *generation, int x, int y) {
    unsigned char liveCells = 0;
    for (char i = -1; i < 2; i++) {
        for (char j = -1; j < 2; j++) {
            if ((x == 0 && j < 0 || x == COLS - 1 && j > 0)
                || (y == 0 && i < 0 || y == ROWS - 1 && i > 0)
                || (i == 0 && j == 0)
                || (generation[(i + y) * COLS + (j + x)] != ALIVE_CELL)) {
                continue;
            }
            liveCells++;
        }
    }
    
    return liveCells;
}

void resetGeneration(unsigned char *generation) {
    for (int i = 0; i < ROWS * COLS; i++) {
        generation[i] = DEAD_CELL;
    }
}

void displayGeneration(unsigned char *generation) {
    system("cls");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", generation[i * COLS + j]);
        }
        puts("");
    }
}

void swapPointers(void **ptr1, void **ptr2) {
    void *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void calculateNextGeneration(unsigned char *currentGeneration, unsigned char *nextGeneration) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            unsigned char liveCells = getAdjacentLiveCells(currentGeneration, j, i);
            if (currentGeneration[i * COLS + j] == ALIVE_CELL) {
                if (liveCells < 2) {
                    nextGeneration[i * COLS + j] = DEAD_CELL;
                } else if (liveCells == 2 || liveCells == 3) {
                    nextGeneration[i * COLS + j] = ALIVE_CELL;
                } else if (liveCells > 3) {
                    nextGeneration[i * COLS + j] = DEAD_CELL;
                }
            } else if (currentGeneration[i * COLS + j] == DEAD_CELL) {
                if (liveCells == 3) {
                    nextGeneration[i * COLS + j] = ALIVE_CELL;
                }
            }
        }
    }
}

int main() {
    unsigned char *currentGeneration = (unsigned char *)malloc(ROWS * COLS * sizeof(char));
    unsigned char *nextGeneration = (unsigned char *)malloc(ROWS * COLS * sizeof(char));

    resetGeneration(currentGeneration);
    resetGeneration(nextGeneration);

    currentGeneration[2 * COLS + 3] = ALIVE_CELL;
    currentGeneration[3 * COLS + 4] = ALIVE_CELL;

    currentGeneration[4 * COLS + 2] = ALIVE_CELL;
    currentGeneration[4 * COLS + 3] = ALIVE_CELL;
    currentGeneration[4 * COLS + 4] = ALIVE_CELL;

    for (int i = 0; i < 50; i++)
    {
        displayGeneration(currentGeneration);

        calculateNextGeneration(currentGeneration, nextGeneration);

        swapPointers((void **)&currentGeneration, (void **)&nextGeneration);
        
        resetGeneration(nextGeneration);

        puts("");
        
        getchar();
    }

    free(currentGeneration);
    free(nextGeneration);

    return 0;
}
