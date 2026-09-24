const int BOARD_SIZE = 15;

const char MINE = '*';
const char FREE_CELL = ' ';
const char UNKNOWN_CELL = '#';

const int VISIBLE_FIELD = 0;
const int HIDDEN_FIELD = 1;
const int HIDDEN_VIEW_FIELD = 2;

class field {
public:
    char cells[BOARD_SIZE][BOARD_SIZE];
    int type;

    bool check_position(int row, int column, field &hidden,
                        field &hidden_view) {
        if (hidden.cells[row][column] == MINE) {
            return false;
        }

        if (cells[row][column] == UNKNOWN_CELL) {
            cells[row][column] = hidden_view.cells[row][column];
        }

        return true;
    }
};
