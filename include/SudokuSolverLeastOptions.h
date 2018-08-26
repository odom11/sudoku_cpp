//
// Created by ich on 8/26/18.
//

#ifndef SUDOKU_SUDOKUSOLVERLEASTOPTIONS_H
#define SUDOKU_SUDOKUSOLVERLEASTOPTIONS_H

#include <SudokuSolver.h>

class SudokuSolverLeastOptions : public SudokuSolver {
private :
    const Coordinates nextField() const override;
};

#endif //SUDOKU_SUDOKUSOLVERLEASTOPTIONS_H
