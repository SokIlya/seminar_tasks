#include "field.h"

bool field::check_position(int row, int column, field &hidden,
                           field &hidden_view) {
    if (hidden.cells[row][column] == MINE) {
        return false;
    }

    if (cells[row][column] == UNKNOWN_CELL) {
        cells[row][column] = hidden_view.cells[row][column];
    }

    return true;
}
