#include <iostream>

#include "field_generation.h"

bool has_open_neighbor(field &visible, int row, int column) {
    return (row > 0 &&
            visible.cells[row - 1][column] != UNKNOWN_CELL) ||
           (row < BOARD_SIZE - 1 &&
            visible.cells[row + 1][column] != UNKNOWN_CELL) ||
           (column > 0 &&
            visible.cells[row][column - 1] != UNKNOWN_CELL) ||
           (column < BOARD_SIZE - 1 &&
            visible.cells[row][column + 1] != UNKNOWN_CELL);
}

void print_field(field &visible) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << visible.cells[i][j];
        }
        std::cout << "\n";
    }
}

int main() {
    field visible;
    field hidden;
    field hidden_view;

    visible.type = VISIBLE_FIELD;
    hidden.type = HIDDEN_FIELD;
    hidden_view.type = HIDDEN_VIEW_FIELD;

    generate_fields(visible, hidden, hidden_view);

    std::cout << "Input format: row column\n";
    std::cout << "Values: 0 to " << BOARD_SIZE - 1 << "\n\n";

    while (true) {
        print_field(visible);
        std::cout << "Valid cells:";

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (visible.cells[i][j] == UNKNOWN_CELL &&
                    has_open_neighbor(visible, i, j)) {
                    std::cout << " (" << i << " " << j << ")";
                }
            }
        }

        int row;
        int column;

        std::cout << "\nEnter cell: ";
        std::cin >> row >> column;

        if (row < 0 || row >= BOARD_SIZE ||
            column < 0 || column >= BOARD_SIZE ||
            visible.cells[row][column] != UNKNOWN_CELL ||
            !has_open_neighbor(visible, row, column)) {
            std::cout << "Invalid input.\n\n";
            continue;
        }

        bool result =
            visible.check_position(row, column, hidden, hidden_view);

        if (result == false) {
            visible.cells[row][column] = MINE;
            print_field(visible);
            std::cout << "Mine check: " << result << "\n";
            std::cout << "You lost.\n";
            break;
        }

        bool safe_move_exists = false;

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (visible.cells[i][j] == UNKNOWN_CELL &&
                    hidden.cells[i][j] == FREE_CELL &&
                    has_open_neighbor(visible, i, j)) {
                    safe_move_exists = true;
                }
            }
        }

        if (safe_move_exists == false) {
            print_field(visible);
            std::cout << "You won.\n";
            break;
        }

        std::cout << "\n";
    }

    return 0;
}
