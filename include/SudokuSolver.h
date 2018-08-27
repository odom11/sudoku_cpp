//
// Created by ich on 8/25/18.
//

#ifndef SUDOKU_SUDOKUSOLVER_H
#define SUDOKU_SUDOKUSOLVER_H

#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <set>

/**
 * class representing a sudoku solver.
 */
class SudokuSolver {
public:
    virtual ~SudokuSolver() {};
    using Coordinates = struct {int row; int col;};
    constexpr static Coordinates INVALID_FIELD = {-1, -1};
    const static int NO_OF_ROWS = 9;
    const static int NO_OF_COLS = 9;
    struct Field {
        int values[NO_OF_ROWS][NO_OF_COLS];
    };

    const static int SUBFIELD_LENGTH = 3;
    const static int NOT_SET = 0;

    /**
     * initializes sudoku from digits.
     * @param inputString string with digits. Sudoku is initialized from left to right and top to bottom.
     */
    void initialize(const std::string& inputString);
    /**
     * getter for data.
     * @return data.
     */
    Field getField() const;
    /**
     * returns reference value at given coordinates.
     * @param row row.
     * @param col  col.
     * @return reference to value.
     */
    int& valueAt(int row, int col) ;
    /**
     * returns value at given coordinates.
     * @param row row.
     * @param col col.
     * @return value at a given coordinate.
     */
    const int valueAt(int row, int col) const;
    /**
     * possible values at given field.
     * @param coordinates coordinates.
     * @return set with values.
     */
    std::set<int> optionsAt(const Coordinates& coordinates) const;
    /**
     * solve this f***ing thing.
     * @return true if the method succeeded, else false.
     */
    bool solve();
private:
    std::set<int> valuesInRow(int row) const;
    std::set<int> valuesInCol(int col) const;
    std::set<int> valuesInSubfield(const Coordinates& coordinates) const;
    /**
     * checks if an input string satisfies criteria for setting up a sudoku.
     * @param input inputstring.
     */
    void checkInputSanity(const std::string& input) const;
    /**
     * returns a coordinates of a field that has no value set.
     * @return coordinates of field that has no value set.
     */
    virtual const Coordinates nextField() const;
    Field field;
};

constexpr SudokuSolver::Coordinates SudokuSolver::INVALID_FIELD;
bool operator==(const SudokuSolver::Coordinates& lhs, const SudokuSolver::Coordinates& rhs);
std::ostream& operator<<(std::ostream& os, const SudokuSolver::Field& field);

#endif //SUDOKU_SUDOKUSOLVER_H
