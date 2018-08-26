//
// Created by ich on 8/26/18.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "SudokuSolverLeastOptionsTest"

#include <boost/test/unit_test.hpp>
#include <boost/assert.hpp>
#include <exception>
#include <string>
#include <iostream>

#include <SudokuSolverLeastOptions.h>

BOOST_AUTO_TEST_SUITE(SudokuSolverLeastOptionsTest)
    BOOST_AUTO_TEST_CASE(testSolve) {
        SudokuSolverLeastOptions solver;
        std::string testString = "030000000000195000008000060800060000400800001000020000060000280000419005000000070";
        solver.initialize(testString);
        solver.solve();
        std::cout<<solver.getField();
    }
BOOST_AUTO_TEST_SUITE_END()
