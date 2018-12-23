#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "SudokuSolverTest"

#include <boost/test/unit_test.hpp>
#include <boost/assert.hpp>
#include <exception>
#include <string>
#include <iostream>

#include <SudokuSolver.h>

inline bool arrayContains(const SudokuSolver::array& array, int upTo, int item);
BOOST_AUTO_TEST_SUITE(SudokuSolverTest)
    BOOST_AUTO_TEST_CASE(testInitializeFailOnTooShortInput) {
        SudokuSolver solver;
        BOOST_CHECK_THROW(solver.initialize("123"), std::exception);

    }

    BOOST_AUTO_TEST_CASE(testInitializeFailOnNonNummericInput) {
        SudokuSolver solver;
        std::string testString = "a30000000000195000008000060800060000400800001000020000060000280000419005000000070";
        BOOST_CHECK_THROW(solver.initialize(testString), std::exception);
    }

    BOOST_AUTO_TEST_CASE(testInitializeSuccess) {
        SudokuSolver solver;
        std::string testString = "030000000000195000008000060800060000400800001000020000060000280000419005000000070";
        solver.initialize(testString);
        auto field = solver.getField();
        BOOST_CHECK_EQUAL(field.values[0][1], 3);
        BOOST_CHECK_EQUAL(field.values[1][3], 1);
        BOOST_CHECK_EQUAL(field.values[3][4], 6);
        BOOST_CHECK_EQUAL(field.values[4][0], 4);
        BOOST_CHECK_EQUAL(field.values[8][7], 7);
    }

    BOOST_AUTO_TEST_CASE(testOptionsAt) {
        SudokuSolver solver;
        std::string testString = "030000000000195000008000060800060000400800001000020000060000280000419005000000070";
        solver.initialize(testString);
        auto field = solver.getField();
        std::cout<<field << std::endl;
        std::pair<SudokuSolver::array, int> optionsAt7x7 = solver.optionsAt({7, 7});
        BOOST_CHECK_EQUAL(optionsAt7x7.second, 1);
        BOOST_ASSERT(arrayContains(optionsAt7x7.first, optionsAt7x7.second, 3));
    }

    BOOST_AUTO_TEST_CASE(testSolve) {
        SudokuSolver solver;
        std::string testString = "030000000000195000008000060800060000400800001000020000060000280000419005000000070";
        solver.initialize(testString);
        solver.solve();
        std::cout<<solver.getField();
    }

    BOOST_AUTO_TEST_CASE(testSolveSolved) {
        SudokuSolver solver;
        //std::string testString = "534678912672195348198342567859761423426853791713924856961537284287419635345286179";
        std::string testString = "534678912672195348198342567859761400400800001000020000060000280000419005000000070";
        solver.initialize(testString);
        std::cout<<solver.getField();
        solver.solve();
        std::cout<<solver.getField();
    }
BOOST_AUTO_TEST_SUITE_END()
