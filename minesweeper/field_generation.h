#include <cstdlib>
#include <ctime>

#include "field.h"

const float MINE_PROBABILITY = 0.3;

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
