#include <cstdlib>
#include <ctime>

#include "field_generation.h"

const float MINE_PROBABILITY = 0.3;

void find_connected_cells(field &hidden,
                          bool connected[BOARD_SIZE][BOARD_SIZE],
                          int center) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            connected[i][j] = false;
        }
    }

    connected[center][center] = true;

    for (int step = 0; step < BOARD_SIZE * BOARD_SIZE; step++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (hidden.cells[i][j] == FREE_CELL) {
                    if (i > 0 && connected[i - 1][j]) {
                        connected[i][j] = true;
                    }
                    if (i < BOARD_SIZE - 1 && connected[i + 1][j]) {
                        connected[i][j] = true;
                    }
                    if (j > 0 && connected[i][j - 1]) {
                        connected[i][j] = true;
                    }
                    if (j < BOARD_SIZE - 1 && connected[i][j + 1]) {
                        connected[i][j] = true;
                    }
                }
            }
        }
    }
}

void generate_fields(field &visible, field &hidden, field &hidden_view) {
    srand(time(0));

    int center = BOARD_SIZE / 2;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((center - 1 <= i && i <= center + 1) &&
                (center - 1 <= j && j <= center + 1)) {
                visible.cells[i][j] = FREE_CELL;
                hidden.cells[i][j] = FREE_CELL;
            } else {
                visible.cells[i][j] = UNKNOWN_CELL;

                if ((center - 2 <= i && i <= center + 2) &&
                    (center - 2 <= j && j <= center + 2)) {
                    hidden.cells[i][j] = FREE_CELL;
                } else if ((float)rand() / RAND_MAX < MINE_PROBABILITY) {
                    hidden.cells[i][j] = MINE;
                } else {
                    hidden.cells[i][j] = FREE_CELL;
                }
            }
        }
    }

    while (true) {
        bool connected[BOARD_SIZE][BOARD_SIZE];
        find_connected_cells(hidden, connected, center);

        int closed_row = -1;
        int closed_column = -1;

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (closed_row == -1 &&
                    hidden.cells[i][j] == FREE_CELL &&
                    connected[i][j] == false) {
                    closed_row = i;
                    closed_column = j;
                }
            }
        }

        if (closed_row == -1) {
            break;
        }

        while (closed_row != center) {
            hidden.cells[closed_row][closed_column] = FREE_CELL;

            if (closed_row < center) {
                closed_row++;
            } else {
                closed_row--;
            }
        }

        while (closed_column != center) {
            hidden.cells[closed_row][closed_column] = FREE_CELL;

            if (closed_column < center) {
                closed_column++;
            } else {
                closed_column--;
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (hidden.cells[i][j] == MINE) {
                hidden_view.cells[i][j] = MINE;
            } else {
                int mines_count = 0;

                for (int x = i - 1; x <= i + 1; x++) {
                    for (int y = j - 1; y <= j + 1; y++) {
                        if (x >= 0 && x < BOARD_SIZE &&
                            y >= 0 && y < BOARD_SIZE &&
                            hidden.cells[x][y] == MINE) {
                            mines_count++;
                        }
                    }
                }

                if (mines_count == 0) {
                    hidden_view.cells[i][j] = FREE_CELL;
                } else {
                    hidden_view.cells[i][j] = '0' + mines_count;
                }
            }
        }
    }
}
