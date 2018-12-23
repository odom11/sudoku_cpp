//
// Created by ich on 8/25/18.
//


#include <SudokuSolver.h>

inline bool arrayContains(const SudokuSolver::array& array, int upTo, int item) {
    auto end = array.begin() + upTo;
    return std::find(array.begin(), end, item) != end;
}

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

SudokuSolver::array SudokuSolver::valuesInCol(int col) const {
    array columnValues;
    for(int row = 0; row < NO_OF_ROWS; ++row) {
        columnValues[row] = valueAt(row, col);
    }
    return columnValues;
}

SudokuSolver::array SudokuSolver::valuesInRow(int row) const {
    array rowValues;
    for(int col = 0; col < NO_OF_ROWS; ++col) {
        rowValues[col] = valueAt(row, col);
    }
    return rowValues;
}

SudokuSolver::array SudokuSolver::valuesInSubfield(const Coordinates& coordinates) const {
    auto lowerBound = [](int value) { return SUBFIELD_LENGTH * (value / SUBFIELD_LENGTH); };
    auto upperBound = [lowerBound](int value) { return lowerBound(value) + SUBFIELD_LENGTH; };
    array fieldValues;
    int index = 0;
    for (int row = lowerBound(coordinates.row); row < upperBound(coordinates.row); ++row) {
        for (int col = lowerBound(coordinates.col); col < upperBound(coordinates.col); ++col) {
            if (valueAt(row, col ) != NOT_SET && !arrayContains(fieldValues, index, valueAt(row, col)))
                fieldValues[index++] = valueAt(row, col);
        }
    }
    std::fill(fieldValues.begin() + index, fieldValues.end(), SudokuSolver::NOT_SET);
    return fieldValues;
}

int& SudokuSolver::valueAt(int row, int col) {
    return field.values[row][col];
}

const int SudokuSolver::valueAt(int row, int col) const {
    return field.values[row][col];
}

std::pair<SudokuSolver::array, int> SudokuSolver::optionsAt(const SudokuSolver::Coordinates &coordinates) const {
    auto rowElements = valuesInRow(coordinates.row);
    auto colElements = valuesInCol(coordinates.col);
    auto fieldElements = valuesInSubfield(coordinates);
    array possibleValues;
    int index = 0;
    for (int candidate = 1; candidate < 10; ++candidate) {
        if(
                !arrayContains(rowElements, MAX_DISTINCT_VALUES, candidate) &&
                !arrayContains(colElements, MAX_DISTINCT_VALUES, candidate) &&
                !arrayContains(fieldElements, MAX_DISTINCT_VALUES, candidate)) {
            possibleValues[index++] = candidate;
        }
    }
    return std::pair<array, int>(possibleValues, index);
}

bool SudokuSolver::solve() {
    const Coordinates next = nextField();
    if (next == INVALID_FIELD)
        return true;
    std::pair<array, int> option = optionsAt(next);
    enum optionMembers {
        values = 0,
        noOfOptions = 1
    };
    if (std::get<noOfOptions>(option) == 0) {
        return false;
    }

    for (int index = 0; index < std::get<noOfOptions>(option); ++index) {
        valueAt(next.row, next.col) = std::get<values>(option)[index];
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
