#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ROWS 50
#define COLS 50

enum tiles {
    ALIVE_CELL = 219,
    DEAD_CELL = 176
};

// From https://stackoverflow.com/questions/2732292/setting-the-cursor-position-in-a-win32-console-application
void gotoxy(int x, int y) { 
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

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
    unsigned char *stringBuffer = (unsigned char *)malloc(COLS * ROWS + ROWS + 1);

    for (int i = 0; i < ROWS; i++) {
        memcpy(stringBuffer + i + i * COLS, generation + i * COLS, COLS);
        stringBuffer[i + COLS + i * COLS] = '\n';
    }

    stringBuffer[COLS * ROWS + ROWS] = '\0';

    gotoxy(0, 0);

    printf("%s", stringBuffer);

    free(stringBuffer);
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

void randomizeGeneration(unsigned char *generation, unsigned char percentage) {
    for (int i = 0; i < COLS * ROWS; i++) {
        srand(i * time(NULL));
        int randomNumber = rand() % 256;
        if (randomNumber < percentage) {
            generation[i] = ALIVE_CELL;
        }
    }
}

int main() {
    system("cls");

    unsigned char *currentGeneration = (unsigned char *)malloc(ROWS * COLS * sizeof(char));
    unsigned char *nextGeneration = (unsigned char *)malloc(ROWS * COLS * sizeof(char));

    resetGeneration(currentGeneration);
    resetGeneration(nextGeneration);

    // currentGeneration[2 * COLS + 3] = ALIVE_CELL;
    // currentGeneration[3 * COLS + 4] = ALIVE_CELL;

    // currentGeneration[4 * COLS + 2] = ALIVE_CELL;
    // currentGeneration[4 * COLS + 3] = ALIVE_CELL;
    // currentGeneration[4 * COLS + 4] = ALIVE_CELL;

    randomizeGeneration(currentGeneration, 128);

    for (int i = 0; i < 1000; i++)
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
