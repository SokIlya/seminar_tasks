#include <iostream>

#include "field_generation.h"

int main() {
    field visible;
    field hidden;
    field hidden_view;

    visible.type = VISIBLE_FIELD;
    hidden.type = HIDDEN_FIELD;
    hidden_view.type = HIDDEN_VIEW_FIELD;

    generate_fields(visible, hidden, hidden_view);

    std::cout << "field\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << visible.cells[i][j];
        }
        std::cout << "\n";
    }

    std::cout << "\nfield_hidden\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << hidden.cells[i][j];
        }
        std::cout << "\n";
    }

    std::cout << "\nfield_hidden_view\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << hidden_view.cells[i][j];
        }
        std::cout << "\n";
    }

    int center = BOARD_SIZE / 2;

    int move_rows[16] = {
        center - 1, center - 2, center - 2, center - 2,
        center - 2, center - 2, center - 1, center,
        center + 1, center + 2, center + 2, center + 2,
        center + 2, center + 2, center + 1, center
    };

    int move_columns[16] = {
        center - 2, center - 2, center - 1, center,
        center + 1, center + 2, center + 2, center + 2,
        center + 2, center + 2, center + 1, center,
        center - 1, center - 2, center - 2, center - 2
    };

    int opened_cells = 0;

    for (int i = 0; i < 16; i++) {
        bool result = visible.check_position(
            move_rows[i], move_columns[i], hidden, hidden_view);

        if (result == false) {
            std::cout << "\nmine_result: " << result << "\n";
            break;
        }

        opened_cells++;
    }

    std::cout << "opened_cells: " << opened_cells << "\n";
    std::cout << "field_after_moves\n";

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << visible.cells[i][j];
        }
        std::cout << "\n";
    }

    return 0;
}
