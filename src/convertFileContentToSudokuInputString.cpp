//
// Created by ich on 9/7/18.
//

#include <fstream>

const std::string convertFileContentToSudokuInputString(const char * filename) {
    std::ifstream fileInput(std::string(filename), std::ios::in);
    std::string numberAsString;
    numberAsString.resize(81);
    int index = 0;
    int readNumber = 0;
    if (fileInput.is_open()) {
        while (fileInput >> readNumber ) {
            if(index >= 81) {
                throw std::out_of_range("amount of numbers in input exceeds 81 (number of fields in a sudoku)");
            }
            numberAsString[index++] = readNumber + '0';
        }
        if (index != 81) {
            throw std::out_of_range("expected 81 numbers in file");
        }

        return numberAsString;
    } else {
        throw std::runtime_error("file '" + std::string(filename) + "' could not be opened");
    }

}
