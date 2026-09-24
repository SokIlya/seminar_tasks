#include <iostream>
#include <cstdlib>

int main() {
    const int BOARD_SIZE = 15;

    const char MINE = '*';
    const char FREE_CELL = ' ';
    const char UNKNOWN_CELL = '#';

    const float MINE_PROB = 0.3;

    char field_hidden[BOARD_SIZE][BOARD_SIZE];
    char field_hidden_view[BOARD_SIZE][BOARD_SIZE];
    char field[BOARD_SIZE][BOARD_SIZE];


    int center = BOARD_SIZE / 2;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if ((center - 1 <= i && i <= center + 1) &&
                (center - 1 <= j && j <= center + 1)) {
                field[i][j] = FREE_CELL;
                field_hidden[i][j] = FREE_CELL;
            } else {
                field[i][j] = UNKNOWN_CELL;

                if ((float)rand() / RAND_MAX < MINE_PROB) {
                    field_hidden[i][j] = MINE;
                } else {
                    field_hidden[i][j] = FREE_CELL;
                }
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (field_hidden[i][j] == MINE) {
                field_hidden_view[i][j] = MINE;
            } else {
                int mines_count = 0;

                for (int x = i - 1; x <= i + 1; x++) {
                    for (int y = j - 1; y <= j + 1; y++) {
                        if (x >= 0 && x < BOARD_SIZE &&
                            y >= 0 && y < BOARD_SIZE &&
                            field_hidden[x][y] == MINE) {
                            mines_count++;
                        }
                    }
                }

                field_hidden_view[i][j] = '0' + mines_count;
            }
        }
    }

    std::cout << "field\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << field[i][j];
        }
        std::cout << "\n";
    }

    std::cout << "\nfield_hidden\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << field_hidden[i][j];
        }
        std::cout << "\n";
    }

    std::cout << "\nfield_hidden_view\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << field_hidden_view[i][j];
        }
        std::cout << "\n";
    }

    return 0;
}