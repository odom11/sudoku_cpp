//
// Created by ich on 8/25/18.
//


#include <SudokuSolver.h>

void SudokuSolver::initialize(const std::string &inputString) {
    checkInputSanity(inputString);
    int index = 0;
    for (char digit : inputString) {
        int row = index / NO_OF_COLS;
        int col = index++ % NO_OF_COLS;
        field.values[row][col] = digit - '0';
    }
}

void SudokuSolver::checkInputSanity(const std::string &input) const {
    if(input.length() != NO_OF_ROWS * NO_OF_COLS) {
        throw std::runtime_error("input string must have length 81");
    }
    if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
        std::string errorstring = "input must be numeric. " + input + " is not";
        throw std::runtime_error(errorstring);
    }
}

SudokuSolver::Field SudokuSolver::getField() const {
    return field;
}

const SudokuSolver::Coordinates SudokuSolver::nextField() const{
    for (int row = 0; row < NO_OF_ROWS; ++row) {
        for (int col = 0; col < NO_OF_COLS; ++col) {
            if (valueAt(row, col) == NOT_SET) {
                return {row, col};
            }
        }
    }
    return INVALID_FIELD;
}

std::set<int> SudokuSolver::valuesInCol(int col) const {
    std::set<int> columnValues;
    for(int row = 0; row < NO_OF_ROWS; ++row) {
        if (valueAt(row, col) != 0)
            columnValues.insert(valueAt(row, col));
    }
    return columnValues;
}

std::set<int> SudokuSolver::valuesInRow(int row) const {
    std::set<int> rowValues;
    for(int col = 0; col < NO_OF_ROWS; ++col) {
        if (valueAt(row, col) != NOT_SET)
            rowValues.insert(valueAt(row, col));
    }
    return rowValues;
}

std::set<int> SudokuSolver::valuesInSubfield(const Coordinates& coordinates) const {
    auto lowerBound = [](int value) { return SUBFIELD_LENGTH * (value / SUBFIELD_LENGTH); };
    auto upperBound = [lowerBound](int value) { return lowerBound(value) + SUBFIELD_LENGTH; };
    std::set<int> fieldValues;
    for (int row = lowerBound(coordinates.row); row < upperBound(coordinates.row); ++row) {
        for (int col = lowerBound(coordinates.col); col < upperBound(coordinates.col); ++col) {
            if (valueAt(row, col ) != NOT_SET)
                fieldValues.insert(valueAt(row, col));
        }
    }
    return fieldValues;
}

int& SudokuSolver::valueAt(int row, int col) {
    return field.values[row][col];
}

const int SudokuSolver::valueAt(int row, int col) const {
    return field.values[row][col];
}

std::set<int> SudokuSolver::optionsAt(const SudokuSolver::Coordinates &coordinates) const {
    auto contains = [] (const std::set<int>& container, int value) {return container.find(value) != container.end();};
    auto rowElements = valuesInRow(coordinates.row);
    auto colElements = valuesInCol(coordinates.col);
    auto fieldElements = valuesInSubfield(coordinates);
    std::set<int> possibleValues;
    for (int candidate = 1; candidate < 10; ++candidate) {
        if(!contains(rowElements, candidate) && !contains(colElements, candidate) && !contains(fieldElements, candidate)) {
            possibleValues.insert(candidate);
        }
    }
    return possibleValues;
}

bool SudokuSolver::solve() {
    const Coordinates next = nextField();
    if (next == INVALID_FIELD)
        return true;
    std::set<int> options = optionsAt(next);
    if (options.size() == 0) {
        return false;
    }

    for (int option : options) {
        valueAt(next.row, next.col) = option;
        bool success = solve();
        if (success) {
            return true;
        }
    }
    valueAt(next.row, next.col) = NOT_SET;
    return false;
}


bool operator==(const SudokuSolver::Coordinates& lhs, const SudokuSolver::Coordinates& rhs) {
    return lhs.row == rhs.row && lhs.col == rhs.col;
}



std::ostream& operator<<(std::ostream& os, const SudokuSolver::Field& field) {
    auto setDelimiter = [](int index) {return ((index + 1) % SudokuSolver::SUBFIELD_LENGTH) == 0;};
    for (int row = 0; row < SudokuSolver::NO_OF_ROWS; ++row)  {
        for (int col = 0; col < SudokuSolver::NO_OF_COLS; ++col) {
            os << field.values[row][col] << " ";
            if (setDelimiter(col)) {
                os << "| ";
            }
        }
        os << std::endl;
//        os << "      |       |       |" << std::endl;
        if (setDelimiter(row)) {
            os << "----------------------|" << std::endl;
        }
    }
    return os;
}
