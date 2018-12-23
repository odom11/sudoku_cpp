//
// Created by ich on 8/26/18.
//

#include <SudokuSolverLeastOptions.h>

const SudokuSolver::Coordinates SudokuSolverLeastOptions::nextField() const {
    int minSize = NO_OF_ROWS;
    Coordinates current = INVALID_FIELD;
    for (int row = 0; row < NO_OF_ROWS; ++row) {
        for (int col = 0; col < NO_OF_COLS; ++col) {
            if (valueAt(row, col) == NOT_SET) {
                int noOfCurrentOptions = optionsAt({row, col}).second;
                if (noOfCurrentOptions < minSize) {
                    minSize = noOfCurrentOptions;
                    current = {row, col};
                    if (minSize == 0) {
                        return current;
                    }
                }
            }
        }
    }
    return current;
}

